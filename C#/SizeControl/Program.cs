using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

class Program
{
    static List<FileInfo> allFiles = new List<FileInfo>();

    static void Main(string[] args)
    {
        Console.Write("Введите путь к директории: ");
        string rootPath = Console.ReadLine();

        TraverseDirectories(rootPath);

        // Сортируем файлы по размеру
        var sortedFiles = allFiles.OrderByDescending(f => f.Length).ToList();

        // Записываем результаты в файл
        string outputPath = "output.txt";
        using (StreamWriter writer = new StreamWriter(outputPath))
        {
            writer.WriteLine("Все найденные файлы (отсортированы по размеру):");
            foreach (var file in sortedFiles)
            {
                writer.WriteLine($"Файл: {file.FullName}, Размер: {FormatBytes(file.Length)}");
            }
        }

        Console.WriteLine($"Обход завершен. Результаты записаны в файл {outputPath}");
        Console.WriteLine("Нажмите Enter для выхода...");
        Console.ReadLine();
    }

    static void TraverseDirectories(string rootPath)
    {
        try
        {
            // Изменение здесь — проверка на существование файла перед добавлением его в список
            var files = Directory.GetFiles(rootPath)
                                 .Select(f => new FileInfo(f))
                                 .Where(f => f.Exists) // Проверка, существует ли файл
                                 .ToList();

            // Добавляем файлы в общий список
            allFiles.AddRange(files);

            var directories = Directory.GetDirectories(rootPath);
            foreach (var directory in directories)
            {
                TraverseDirectories(directory);
            }
        }
        catch (UnauthorizedAccessException)
        {
            Console.WriteLine($"Нет доступа к папке: {rootPath}");
        }
        catch (DirectoryNotFoundException)
        {
            Console.WriteLine($"Не найдена папка: {rootPath}");
        }
        catch (FileNotFoundException ex)
        {
            Console.WriteLine($"Файл не найден: {ex.FileName}");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при обработке папки {rootPath}: {ex.Message}");
        }
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
