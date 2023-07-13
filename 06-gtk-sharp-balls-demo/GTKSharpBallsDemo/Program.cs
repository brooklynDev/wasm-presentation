using System.Runtime.InteropServices;
using Gtk;
using Cairo;
using GLib;
using Wasmtime;
using DateTime = System.DateTime;
using Task = System.Threading.Tasks.Task;

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public struct Ball
{
    public float x;
    public float y;
    public float radius;
    public float dx;
    public float dy;
    public int red;
    public int green;
    public int blue;
}

public class GTKSharpBallsDemo
{
    private static DrawingArea _drawingArea;
    private static ImageSurface _offscreenSurface;
    private static Context _offscreenContext;
    private static Instance _instance;

    static void Main()
    {
        using var engine = new Engine();
        using var module = Module.FromFile(engine, "main.wasm");

        using var linker = new Linker(engine);
        using var store = new Store(engine);

        linker.DefineFunction("env", "platform_draw_ball", (int x) => DrawBall(x));

        _instance = linker.Instantiate(store, module);
        var draw = _instance.GetAction("draw");
        var update = _instance.GetAction("update");
        var addBalls = _instance.GetAction<float, float>("add_balls");

        Gtk.Application.Init();

        var win = new Window("GTK WASM Balls");
        win.DeleteEvent += delegate { Gtk.Application.Quit(); };

        _drawingArea = new DrawingArea();
        _drawingArea.Drawn += DrawnHandler;
        _drawingArea.SizeAllocated += DrawingAreaSizeAllocated;
        win.ButtonPressEvent += (o, e) => addBalls((float) e.Event.X, (float) e.Event.Y);

        win.Add(_drawingArea);
        win.ShowAll();

        Task.Run(async () =>
        {
            while (true)
            {
                await Task.Delay(30);
                _offscreenContext.Save();
                _offscreenContext.SetSourceRGB(44 / 255.0, 62 / 255.0, 80 / 255.0);
                _offscreenContext.Paint();
                _offscreenContext.Restore();
                update();
                draw();
                _drawingArea.QueueDraw();
            }
        });

        Gtk.Application.Run();
    }

    static void DrawingAreaSizeAllocated(object o, SizeAllocatedArgs args)
    {
        var width = args.Allocation.Width;
        var height = args.Allocation.Height;

        if (_offscreenSurface != null && _offscreenSurface.Width == width && _offscreenSurface.Height == height)
            return;

        _offscreenSurface?.Dispose();
        _offscreenContext?.Dispose();

        _offscreenSurface = new ImageSurface(Format.ARGB32, width, height);
        _offscreenContext = new Context(_offscreenSurface);

        var init = _instance.GetAction<int, int, int>("init");
       

        init((int) DateTime.Now.Ticks, width, height);
    }

    static void DrawBall(int ballPtr)
    {
        var wasmMemory = _instance.GetMemory("memory");
        var memorySpan = wasmMemory.GetSpan<byte>(ballPtr);

        var ball = MemoryMarshal.Read<Ball>(memorySpan);
        
        _offscreenContext.Arc(ball.x, ball.y, ball.radius, 0, 2 * Math.PI);
        _offscreenContext.SetSourceRGB(ball.red / 255.0, ball.green / 255.0, ball.blue / 255.0);
        _offscreenContext.Fill();
    }
    
    static void DrawnHandler(object o, DrawnArgs args)
    {
        using var cr = Gdk.CairoHelper.Create(_drawingArea.GdkWindow);
        cr.SetSourceSurface(_offscreenSurface, 0, 0);
        cr.Paint();
    }
}
