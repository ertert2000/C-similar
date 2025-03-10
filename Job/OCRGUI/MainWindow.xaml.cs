using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Drawing;
using System.Drawing.Printing;
using Tesseract;


namespace OCRGUI;

/// <summary>
/// Interaction logic for MainWindow.xaml
/// </summary>
public partial class MainWindow : Window
{
    private OCRMonitor OCRMonitor;
    bool flag = false;

    public MainWindow()
    {
        InitializeComponent();

        System.Drawing.Rectangle captureArea = new System.Drawing.Rectangle(290, 385, 137, 70);
        string tessDataPath = @"D:\tesseract\tessdata";

        OCRMonitor = new OCRMonitor(captureArea, tessDataPath, 250);
    }

    private void OcrCapture_OnTextRecognized(string text)
    {
        Dispatcher.Invoke(() => {
            recognizedTextTextBox.Text = text;
        });
    }

    protected override void OnClosed(EventArgs e)
    {
        base.OnClosed(e);
        OCRMonitor.StopCapture();
    }

    private void startStopButtonClick(object sender, RoutedEventArgs e)
    {
        if (flag)
        {

            OCRMonitor.OnTextRecognized += OcrCapture_OnTextRecognized;
            OCRMonitor.StartCapture();
            flag = false;
        }
        else
        {
            flag = true;
            OCRMonitor.StopCapture();
        }

    }

    //private void PrintButton_Click(object sender, RoutedEventArgs e)
    //{
    //    string img = "D:\\work\\Commercial-work\\WB\\dataSet\\images\\003.png";

    //    using (var engine = new TesseractEngine(@"D:\tesseract\tessdata", "eng", EngineMode.Default))
    //    {
    //        using (var im = Pix.LoadFromFile(img))
    //        {
    //            using (var page = engine.Process(im))
    //            {

    //                string extractedText = page.GetText();

    //                textBox.Text = extractedText;

    //                PrintDocument printDoc = new PrintDocument();
    //                printDoc.PrinterSettings.PrinterName = "Xprinter XP-365B";

    //                printDoc.PrintPage += (sender, e) => PrintText(sender, e, extractedText);

    //                try
    //                {
    //                    printDoc.Print();
    //                    statusLabel.Content = "The seal is completed successfully!";
    //                }
    //                catch (Exception ex)
    //                {
    //                    statusLabel.Content = "Printing error:" + ex.Message;
    //                }
    //            }
    //        }
    //    }
    //}

    //private void PrintText(object sender, PrintPageEventArgs e, string text)
    //{
    //    Font font = new Font("Courier New", 30);
    //    e.Graphics.DrawString(text, font, System.Drawing.Brushes.Black, 10, 10);
    //}
}