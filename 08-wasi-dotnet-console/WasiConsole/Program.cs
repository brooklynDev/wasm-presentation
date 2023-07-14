namespace WasiConsole;
using System.Runtime.InteropServices;

public class Program
{
    public static void Main()
    {
       Console.WriteLine($"Running on: {RuntimeInformation.OSArchitecture}"); 
    }
}