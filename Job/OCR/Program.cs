using System;
using System.Drawing;
using System.Drawing.Printing;
using System.Threading;
using OCR;

class Program
{
    static void Main()
    {
        Rectangle captureArea = new Rectangle(100, 100, 200, 50); // Область экрана для мониторинга
        string tessDataPath = @"D:\tesseract\tessdata"; // Укажи путь к папке с Tesseract

        OCRMonitor monitor = new OCRMonitor(captureArea, tessDataPath);
        monitor.OnTextRecognized += PrintExtractedText;

        Console.WriteLine("Программа запущена. Нажмите Ctrl+C для выхода.");

        // Обработчик выхода (Ctrl+C)
        Console.CancelKeyPress += (sender, e) =>
        {
            e.Cancel = true; // Блокируем мгновенный выход
            Console.WriteLine("Завершение работы...");
            monitor.StopCapture();
            Environment.Exit(0);
        };

        monitor.StartCapture();

        // Программа работает бесконечно, ожидая команду выхода
        while (true)
        {
            Thread.Sleep(1000);
        }
    }

    static void PrintExtractedText(string extractedText)
    {
        Console.WriteLine($"Обнаружен новый текст: {extractedText}");

        PrintDocument printDoc = new PrintDocument();
        printDoc.PrinterSettings.PrinterName = "Xprinter XP-365B";
        printDoc.PrintPage += (sender, e) => PrintText(sender, e, extractedText);

        try
        {
            printDoc.Print();
            Console.WriteLine("Печать завершена!");
        }
        catch (Exception ex)
        {
            Console.WriteLine("Ошибка при печати: " + ex.Message);
        }
    }

    static void PrintText(object sender, PrintPageEventArgs e, string text)
    {
        Font font = new Font("Courier New", 12);
        e.Graphics.DrawString(text, font, Brushes.Black, 10, 10);
    }
}
