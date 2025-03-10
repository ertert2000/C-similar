using System;
using System.Diagnostics;
using System.Runtime.InteropServices;

class Program
{
    [DllImport("kernel32.dll")]
    static extern IntPtr OpenProcess(int dwDesiredAccess, bool bInheritHandle, int dwProcessId);

    [DllImport("kernel32.dll")]
    static extern bool ReadProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, byte[] lpBuffer, int dwSize, out int lpNumberOfBytesRead);

    static void Main()
    {
        int pid = 34524; // ID процесса (узнать через Task Manager)
        IntPtr hProcess = OpenProcess(0x0010, false, pid); // PROCESS_VM_READ

        if (hProcess == IntPtr.Zero)
        {
            Console.WriteLine("Ошибка открытия процесса");
            return;
        }

        IntPtr baseAddress = (IntPtr)0x7FF600000000; // Пример адреса
        byte[] buffer = new byte[1024]; // Читаем 1 KB
        int bytesRead;

        if (ReadProcessMemory(hProcess, baseAddress, buffer, buffer.Length, out bytesRead))
        {
            Console.WriteLine($"Прочитано {bytesRead} байт:");
            Console.WriteLine(BitConverter.ToString(buffer));
        }
        else
        {
            Console.WriteLine("Ошибка чтения памяти");
        }
    }
}

