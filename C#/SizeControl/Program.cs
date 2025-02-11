using System;
using System.IO;

class Program
{
    static void Main(string[] args)
    {
        string rootPath = @"F:\";
        TraverseDirectories(rootPath);
    }

    static void TraverseDirectories(string rootPath)
    {
        try
        {
            var directories = Directory.GetDirectories(rootPath);

            foreach (var directory in directories)
            {
                long size = GetDirectorySize(directory);
                Console.WriteLine($"Папка: {directory}, Размер: {FormatBytes(size)}");

                TraverseDirectories(directory);
            }
        }
        catch (UnauthorizedAccessException)
        {
            Console.WriteLine($"Нет доступа к папке: {rootPath}");
        }
    }

    static long GetDirectorySize(string directoryPath)
    {
        long totalSize = 0;

        try
        {
            var files = Directory.GetFiles(directoryPath);
            foreach (var file in files)
            {
                FileInfo fileInfo = new FileInfo(file);
                totalSize += fileInfo.Length;
            }

            var subdirectories = Directory.GetDirectories(directoryPath);
            foreach (var subdirectory in subdirectories)
            {
                totalSize += GetDirectorySize(subdirectory);
            }
        }
        catch (UnauthorizedAccessException)
        {
            Console.WriteLine($"Нет доступа к файлам в папке: {directoryPath}");
        }

        return totalSize;
    }

    static string FormatBytes(long bytes)
    {
        string[] sizes = { "B", "KB", "MB", "GB", "TB" };
        int order = 0;

        while (bytes >= 1024 && order < sizes.Length - 1)
        {
            order++;
            bytes = bytes / 1024;
        }

        return $"{bytes:0.##} {sizes[order]}";
    }
}
