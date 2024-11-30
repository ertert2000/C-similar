using Microsoft.Win32;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Data;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Xml.Serialization;

namespace lib3_1
{
    /// <summary>
    /// Логика взаимодействия для SaveSelectedWindow.xaml
    /// </summary>
    public partial class SaveSelectedWindow : Window
    {
        private MainWindow MainWindow; 
        private RenderTargetBitmap _prerenderedImage;
        private bool fladWindwoState = false;

        public SaveSelectedWindow(MainWindow MainWindow)
        {
            InitializeComponent();
            this.MainWindow = MainWindow;
        }

        private void PrerenderTableImage(string format)
        {
            int width = (int)(600 / 1.3);
            int height = (int)(800 / 1.3);
            _prerenderedImage = new RenderTargetBitmap(width, height, 96, 96, PixelFormats.Pbgra32);

            DrawingVisual visual = new DrawingVisual();
            using (DrawingContext dc = visual.RenderOpen())
            {
                dc.DrawRectangle(Brushes.White, null, new Rect(0, 0, width, height));

                double yOffset = 10;
                string headerText = "";

                if (format == "CSV")
                {
                    headerText = "Id,Имя,Фамилия,Позиция,Price,Main";
                    FormattedText formattedHeader = new FormattedText(
                        headerText,
                        System.Globalization.CultureInfo.InvariantCulture,
                        FlowDirection.LeftToRight,
                        new Typeface("Consolas"),
                        16,
                        Brushes.Black,
                        96);
                    dc.DrawText(formattedHeader, new Point(10, yOffset));
                    yOffset += 24;
                }
                else if (format == "TXT")
                {
                    headerText = "Id | Имя | Фамилия | Позиция | Price | Main";
                    FormattedText formattedHeader = new FormattedText(
                        headerText,
                        System.Globalization.CultureInfo.InvariantCulture,
                        FlowDirection.LeftToRight,
                        new Typeface("Consolas"),
                        16,
                        Brushes.Black,
                        96);
                    dc.DrawText(formattedHeader, new Point(10, yOffset));
                    yOffset += 24;
                }
                else if (format == "JSON")
                {
                    headerText = "JSON Representation";
                    FormattedText formattedHeader = new FormattedText(
                        headerText,
                        System.Globalization.CultureInfo.InvariantCulture,
                        FlowDirection.LeftToRight,
                        new Typeface("Consolas"),
                        16,
                        Brushes.Black,
                        96);
                    dc.DrawText(formattedHeader, new Point(10, yOffset));
                    yOffset += 24;

                    if (MainWindow.fotbal.ItemsSource is List<FootballPlayers> list)
                    {
                        string jsonString = JsonConvert.SerializeObject(list, Formatting.Indented);
                        var lines = jsonString.Split(new[] { Environment.NewLine }, StringSplitOptions.None);

                        foreach (var line in lines)
                        {
                            FormattedText formattedText = new FormattedText(
                                line,
                                System.Globalization.CultureInfo.InvariantCulture,
                                FlowDirection.LeftToRight,
                                new Typeface("Consolas"),
                                16,
                                Brushes.Black,
                                96);

                            dc.DrawText(formattedText, new Point(10, yOffset));
                            yOffset += 24;
                        }
                    }
                }
                else if (format == "XML")
                {
                    FormattedText formattedHeader = new FormattedText(
                        "",
                        System.Globalization.CultureInfo.InvariantCulture,
                        FlowDirection.LeftToRight,
                        new Typeface("Consolas"),
                        16,
                        Brushes.Black,
                        96);
                    dc.DrawText(formattedHeader, new Point(10, yOffset));
                    yOffset += 24;

                    if (MainWindow.fotbal.ItemsSource is List<FootballPlayers> list)
                    {
                        // Сериализация данных в XML-строку
                        XmlSerializer serializer = new XmlSerializer(typeof(List<FootballPlayers>));
                        StringWriter stringWriter = new StringWriter();
                        serializer.Serialize(stringWriter, list);
                        string xmlString = stringWriter.ToString();

                        // Разбиваем XML-строку на строки для отображения
                        var lines = xmlString.Split(new[] { Environment.NewLine }, StringSplitOptions.None);

                        foreach (var line in lines)
                        {
                            FormattedText formattedText = new FormattedText(
                                line,
                                System.Globalization.CultureInfo.InvariantCulture,
                                FlowDirection.LeftToRight,
                                new Typeface("Consolas"),
                                16,
                                Brushes.Black,
                                96);

                            dc.DrawText(formattedText, new Point(10, yOffset));
                            yOffset += 24;
                        }
                    }
                }

                foreach (var item in MainWindow.fotbal.Items)
                {
                    if (item is FootballPlayers data)
                    {
                        string rowText;
                        if (format == "CSV")
                            rowText = $"{data.id},{data.name},{data.firstName},{data.position},{data.price},{data.mainOrSpare}";
                        else if(format == "TXT")
                            rowText = $"{data.id} | {data.name} | {data.firstName} | {data.position} | {data.price} | {data.mainOrSpare}";
                        else
                            break;

                        FormattedText formattedText = new FormattedText(
                            rowText,
                            System.Globalization.CultureInfo.InvariantCulture,
                            FlowDirection.LeftToRight,
                            new Typeface("Consolas"),
                            16,
                            Brushes.Black,
                            96);

                        dc.DrawText(formattedText, new Point(10, yOffset));
                        yOffset += 24;
                    }
                }
                
            }

            _prerenderedImage.Render(visual);
            fileImage.Source = _prerenderedImage;
        }

        private void SaveToCsv(string filePath)
        {
            using (StreamWriter writer = new StreamWriter(filePath))
            {
                writer.WriteLine("Id | Имя | Фамилия | Позиция | Price | Main");
                foreach (var item in MainWindow.fotbal.Items)
                {
                    if (item is FootballPlayers data)
                    {
                        string line = $"{data.id},{data.name},{data.firstName},{data.position},{data.price},{data.mainOrSpare}";
                        writer.WriteLine(line);
                    }
                }
            }
        }

        private void SaveToTxt(string filePath)
        {
            using (StreamWriter writer = new StreamWriter(filePath))
            {
                writer.WriteLine("Id,Имя,Фамилия,Позиция,Price,Main");
                foreach (var item in MainWindow.fotbal.Items)
                {
                    if (item is FootballPlayers data)
                    {
                        string line = $"{data.id} | {data.name} | {data.firstName} | {data.position} | {data.price} | {data.mainOrSpare}";
                        writer.WriteLine(line);
                    }
                }
            }
        }

        private void SaveImage(string filePath)
        {
            using (FileStream stream = new FileStream(filePath, FileMode.Create))
            {
                BitmapEncoder encoder = new PngBitmapEncoder();
                encoder.Frames.Add(BitmapFrame.Create(_prerenderedImage));
                encoder.Save(stream);
            }
        }

        private void PrerenderButton_Click(object sender, RoutedEventArgs e)
        {
            if (formatComboBox.SelectedItem is ComboBoxItem selectedItem)
            {
                string format = selectedItem.Content.ToString();
                PrerenderTableImage(format);
            }
        }

        private void SaveButton_Click(object sender, RoutedEventArgs e)
        {
            if (formatComboBox.SelectedItem is ComboBoxItem selectedItem)
            {
                string format = selectedItem.Content.ToString();
                SaveFileDialog saveFileDialog = new SaveFileDialog();

                switch (format)
                {
                    case "CSV":
                        saveFileDialog.FileName = "output.csv";
                        saveFileDialog.DefaultExt = ".csv";
                        saveFileDialog.Filter = "CSV Files (*.csv)|*.csv";
                        break;
                    case "TXT":
                        saveFileDialog.FileName = "output.txt";
                        saveFileDialog.DefaultExt = ".txt";
                        saveFileDialog.Filter = "Text Files (*.txt)|*.txt";
                        break;
                    case "JSON":
                        saveFileDialog.FileName = "output.json";
                        saveFileDialog.DefaultExt = ".json";
                        saveFileDialog.Filter = "Text Files (*.json)|*.json";
                        break;
                    case "XML":
                        saveFileDialog.FileName = "output.xml";
                        saveFileDialog.DefaultExt = ".xml";
                        saveFileDialog.Filter = "Text Files (*.xml)|*.xml";
                        break;
                    case "Изображение":
                        saveFileDialog.FileName = "output.png";
                        saveFileDialog.DefaultExt = ".png";
                        saveFileDialog.Filter = "Image Files (*.png)|*.png|JPEG Files (*.jpg)|*.jpg";
                        break;
                }

                if (saveFileDialog.ShowDialog() == true)
                {
                    switch (format)
                    {
                        case "CSV":
                            SaveToCsv(saveFileDialog.FileName);
                            break;
                        case "TXT":
                            SaveToTxt(saveFileDialog.FileName);
                            break;
                        case "JSON":
                            MainWindow.saveData(saveFileDialog.FileName);
                            break;
                        case "XML":
                            MainWindow.serializationXML(saveFileDialog.FileName);
                            break;
                        case "Изображение":
                            SaveImage(saveFileDialog.FileName);
                            break;
                    }

                    MessageBox.Show("Файл успешно сохранен!");
                }

                Close();
            }
            else
            {
                MessageBox.Show("Пожалуйста, выберите формат для сохранения.");
            }
        }

        private void ComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBoxItem selectedItem = formatComboBox.SelectedItem as ComboBoxItem;

            if (selectedItem != null)
                PrerenderTableImage(selectedItem.Content.ToString());
        }

        private void closeButtonClick(object sender, RoutedEventArgs e) => Close();

        private void buttonFullSreanClick(object sender, RoutedEventArgs e) => this.WindowState = WindowState.Minimized;

        private void hideButtonClick(object sender, RoutedEventArgs e)
        {
            if (!fladWindwoState)
            {
                this.WindowState = WindowState.Maximized;
                fladWindwoState = true;
            }
            else
            {
                this.WindowState = WindowState.Normal;
                fladWindwoState = false;
            }

        }
    }
}
