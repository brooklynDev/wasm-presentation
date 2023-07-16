using System.IO;
using System.Runtime.InteropServices.JavaScript;
using MsgKit;

public partial class MyClass
{
    public static void Main()
    {
        
    }
    
    [JSExport]
    internal static byte[] DownloadMsg(string subject, string to, string cc, string body)
    {
        using var email = new Email(
            new Sender(to, to), subject);
        email.Recipients.AddTo(to);
        email.Recipients.AddCc(cc);
        email.BodyText = body;
        using var memoryStream = new MemoryStream();
        email.Save(memoryStream);
        return memoryStream.ToArray();
    }
}

