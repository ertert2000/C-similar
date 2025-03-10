using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Threading;
using Tesseract;

namespace OCRGUI 
{
    class OCRMonitor 
    {
        private readonly Rectangle captureArea;
        private readonly TesseractEngine tesseractEngine;
        private readonly int captureInterval;

        public event Action<string>? OnTextRecognized;

        public OCRMonitor(Rectangle area, string tessDataPath, int interval = 500)
        {
            captureArea = area;
            captureInterval = interval;
            tesseractEngine = new TesseractEngine(tessDataPath, "eng", EngineMode.Default);
        }

        public void StartCapture()
        {
            Thread captureThread = new Thread(CaptureAndRecognize);
            captureThread.IsBackground = true;
            captureThread.Start();
        }

        private void CaptureAndRecognize()
        {
            while (true)
            {
                try
                {
                    Bitmap screenshot = CaptureScreen();

                    string recognizedText = RecognizeText(screenshot);

                    OnTextRecognized?.Invoke(recognizedText);
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"Capture/recognition error: {ex.Message}");
                }

                Thread.Sleep(captureInterval);
            }
        }

        private Bitmap CaptureScreen()
        {
            Bitmap screenshot = new Bitmap(captureArea.Width, captureArea.Height);
            using (Graphics g = Graphics.FromImage(screenshot))
            {
                g.CopyFromScreen(captureArea.Location, Point.Empty, captureArea.Size);
            }
            return screenshot;
        }

        private string RecognizeText(Bitmap screenshot)
        {
            using (var pix = Pix.LoadFromMemory(BitmapToByteArray(screenshot)))
            {
                using (var page = tesseractEngine.Process(pix))
                {
                    return page.GetText();
                }
            }
        }

        private byte[] BitmapToByteArray(Bitmap bitmap)
        {
            using (var ms = new System.IO.MemoryStream())
            {
                bitmap.Save(ms, System.Drawing.Imaging.ImageFormat.Bmp);
                return ms.ToArray();
            }
        }

        public void StopCapture()
        {
            tesseractEngine.Dispose();
        }




    }
}
