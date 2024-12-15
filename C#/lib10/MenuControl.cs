using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Threading;

namespace lib3_1
{
    public partial class MainWindow
    {
        private void SaveAsButtonClick(object sender, RoutedEventArgs e)
        {
            ReportGenerator reportGenerator = new ReportGenerator(fotbal);

            ManualResetEvent dataLoadedEvent = new ManualResetEvent(false);
            ManualResetEvent xmlProcessedEvent = new ManualResetEvent(false);

            Thread loadXmlThread = new Thread(() =>
            {
                try
                {
                    reportGenerator.ExportDataGridToPdf("sa.pdf");
                    dataLoadedEvent.Set();
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"Ошибка при загрузке данных: {ex.Message}");
                }
            });

            Thread editAndSaveXmlThread = new Thread(() =>
            {
                dataLoadedEvent.WaitOne();

                try
                {
                    reportGenerator.ExportToHtml("as.html");
                    xmlProcessedEvent.Set();
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"Ошибка при редактировании данных: {ex.Message}");
                }
            });

            Thread generateHtmlReportThread = new Thread(() =>
            {
                xmlProcessedEvent.WaitOne();

                try
                {
                    saveData();
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"Ошибка при создании отчета: {ex.Message}");
                }
            });

            loadXmlThread.Start();
            editAndSaveXmlThread.Start();
            generateHtmlReportThread.Start();


            SaveSelectedWindow saveSelectedWindow = new SaveSelectedWindow(this);
            saveSelectedWindow.Show();
        }


        private void OpenButtonClick(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog
            {
                Filter = "CSV Files (*.csv)|*.csv|Text Files (*.txt)|*.txt|Json Files (*.json)|*.json|Xml Files (*.xml)|*.xml",
                Title = "Выберите файл"
            };

            if (openFileDialog.ShowDialog() == true)
            {
                string selectedFilePath = openFileDialog.FileName;
                string format = "";
                if (System.IO.Path.GetExtension(selectedFilePath).ToLower() == ".csv")
                    format = "CSV";
                else if(System.IO.Path.GetExtension(selectedFilePath).ToLower() == ".txt")
                    format = "TXT";
                else if(System.IO.Path.GetExtension(selectedFilePath).ToLower() == ".json")
                    format = "JSON";
                else if (System.IO.Path.GetExtension(selectedFilePath).ToLower() == ".xml")
                    format = "XML";
                else
                    MessageBox.Show("sd");

                List<FootballPlayers> players = null;
                if (format == "CSV")
                    players = DeserializeCsv(selectedFilePath);
                else if (format == "TXT")
                    players = DeserializeTxt(selectedFilePath);
                else if (format == "JSON")
                    loadData(selectedFilePath);
                else if(format == "XML")
                    deserializeXML(selectedFilePath);


                if (players != null)
                {
                    fotbal.ItemsSource = players;
                }
            }
        }
    }
}
