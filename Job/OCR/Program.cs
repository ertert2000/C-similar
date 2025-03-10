using System;
using System.Drawing;
using System.Drawing.Printing;
using System.IO;
using Tesseract;

class Program
{
    static void Main()
    {
        string img = "D:\\work\\Commercial-work\\WB\\dataSet\\images\\003.png";

        using (var engine = new TesseractEngine(@"D:\tesseract\tessdata", "eng", EngineMode.Default))
        {
            using (var im = Pix.LoadFromFile(img))
            {
                using (var page = engine.Process(im))
                {
                    string extractedText = page.GetText();

                    PrintDocument printDoc = new PrintDocument();
                    printDoc.PrinterSettings.PrinterName = "Xprinter XP-365B";

                    printDoc.PrintPage += (sender, e) => PrintText(sender, e, extractedText);

                    try
                    {
                        // Печать
                        printDoc.Print();
                        Console.WriteLine("Печать завершена на Windows!");
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine("Ошибка при печати: " + ex.Message);
                    }


                }
            }
        }
    }

    static void PrintText(object sender, PrintPageEventArgs e, string text)
    {
        Font font = new Font("Courier New", 12);
        e.Graphics.DrawString(text, font, Brushes.Black, 10, 10);
    }
}
