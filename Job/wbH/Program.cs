using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Diagnostics.Tracing.Session;
using System.Diagnostics;


namespace wbH
{
    class Program
    {
        static void Main()
        {
            [DllImport("kernel32.dll")]
            static extern IntPtr OpenProcess(int dwDesiredAccess, bool bInheritHandle, int dwProcessId);

            [DllImport("kernel32.dll")]
            static extern bool ReadProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, byte[] lpBuffer, int dwSize, out int lpNumberOfBytesRead);

            static void Main()
            {
                int pid = 1234; // ID процесса (узнать через Task Manager)
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



















            //string path = @"D:\WB_PVZ\data\flutter_assets\assets\sounds\cells"; // Укажи свою директорию
            //using (FileSystemWatcher watcher = new FileSystemWatcher())
            //{
            //    watcher.Path = path;
            //    watcher.NotifyFilter = NotifyFilters.FileName | NotifyFilters.LastWrite | NotifyFilters.Size;
            //    watcher.Filter = "*.*";
            //    watcher.EnableRaisingEvents = true;

            //    watcher.Changed += (s, e) => Console.WriteLine($"Изменён: {e.FullPath}");
            //    watcher.Created += (s, e) => Console.WriteLine($"Создан: {e.FullPath}");
            //    watcher.Deleted += (s, e) => Console.WriteLine($"Удалён: {e.FullPath}");
            //    watcher.Renamed += (s, e) => Console.WriteLine($"Переименован: {e.OldFullPath} -> {e.FullPath}");

            //    Console.WriteLine("Отслеживание изменений... Нажмите Enter для выхода.");
            //    Console.ReadLine();
            //}
        }
    }
}
