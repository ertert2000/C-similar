using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace lib3_1
{
    public partial class MainWindow
    {
        private void SaveAsButtonClick(object sender, RoutedEventArgs e)
        {
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
