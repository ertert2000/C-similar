using Newtonsoft.Json;
using NLog;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Documents;
using System.Windows.Forms;
using System.Xml.Serialization;

namespace lib3_1
{
    public partial class MainWindow
    {
        private static Logger logger = LogManager.GetCurrentClassLogger();

        private string patchToSave = "save.json";
        private void WindowClose(object sender, EventArgs e) => saveData();

        private void saveData()
        {
            try
            {
                List<FootballPlayers> list = fotbal.ItemsSource as List<FootballPlayers>; 
                string jsonString = JsonConvert.SerializeObject(list);
                if (string.IsNullOrEmpty(jsonString))
                    throw new SerializationException("Failed to save data");

                File.WriteAllText(patchToSave, jsonString);
                logger.Info("Данные успешно сохранены в файл {0}", patchToSave);
            }
            catch (SerializationException ex)
            {
                logger.Error(ex, "Ошибка сериализации при сохранении данных");
                MessageBox.Show(ex.Message, "Serialization error");
            }
            catch (Exception ex)
            {
                logger.Error(ex, "Ошибка при сохранении данных");
                MessageBox.Show(ex.Message, "Error");
            }
        }

        public void saveData(string patchToSave)
        {
            try
            {
                List<FootballPlayers> list = fotbal.ItemsSource as List<FootballPlayers>;
                string jsonString = JsonConvert.SerializeObject(list);
                if (string.IsNullOrEmpty(jsonString))
                    throw new SerializationException("Failed to save data");

                File.WriteAllText(patchToSave, jsonString);
                logger.Info("Данные успешно сохранены в файл {0}", patchToSave);
            }
            catch (SerializationException ex)
            {
                logger.Error(ex, "Ошибка сериализации при сохранении данных");
                MessageBox.Show(ex.Message, "Serialization error");
            }
            catch (Exception ex)
            {
                logger.Error(ex, "Ошибка при сохранении данных");
                MessageBox.Show(ex.Message, "Error");
            }
        }

        private void loadData(string patchSave)
        {
            try
            {
                if (!File.Exists(patchSave))
                    return;

                string jsonString = File.ReadAllText(patchSave);
                List<FootballPlayers> loadData = JsonConvert.DeserializeObject<List<FootballPlayers>>(jsonString);
                if (string.IsNullOrEmpty(jsonString))
                    throw new SerializationException("Failed to load data");

                fotbal.ItemsSource = loadData;
                logger.Info("Данные успешно загружены из файла {0}", patchSave);
            }
            catch (SerializationException ex)
            {
                logger.Error(ex, "Ошибка сериализации при загрузке данных");
                MessageBox.Show(ex.Message, "Serialization error");
            }
            catch (Exception ex)
            {
                logger.Error(ex, "Ошибка при загрузке данных");
                MessageBox.Show(ex.Message, "Error");
            }
        }



        public List<FootballPlayers> DeserializeCsv(string filePath)
        {
            var playersList = new List<FootballPlayers>();

            using (var reader = new StreamReader(filePath))
            {
                string line;
                reader.ReadLine();

                while ((line = reader.ReadLine()) != null)
                {
                    var values = line.Split(',');
                    if (values.Length == 6)
                    {
                        var player = new FootballPlayers
                        (
                            values[1],
                            values[2],
                            values[3],
                            int.Parse(values[0]),
                            (int)decimal.Parse(values[4]),
                            bool.Parse(values[5])
                        );
                        playersList.Add(player);
                    }
                }
            }

            logger.Info("Данные успешно десериализованы из CSV файла {0}", filePath);
            return playersList;
        }

        public List<FootballPlayers> DeserializeTxt(string filePath)
        {
            var playersList = new List<FootballPlayers>();

            using (var reader = new StreamReader(filePath))
            {
                string line;
                reader.ReadLine();

                while ((line = reader.ReadLine()) != null)
                {
                    var values = line.Split('|').Select(v => v.Trim()).ToArray();

                    if (values.Length == 6)
                    {
                        try
                        {
                            var player = new FootballPlayers
                            (
                                values[1],
                                values[2],
                                values[3],
                                int.Parse(values[0]),
                                decimal.ToInt32(decimal.Parse(values[4])),
                                bool.Parse(values[5])
                            );
                            playersList.Add(player);
                        }
                        catch (FormatException ex)
                        {
                            logger.Error(ex, "Ошибка формата данных в TXT файле");
                            MessageBox.Show($"Ошибка формата данных: {ex.Message}");
                        }
                        catch (Exception ex)
                        {
                            logger.Error(ex, "Ошибка при обработке TXT файла");
                            MessageBox.Show($"Ошибка: {ex.Message}");
                        }
                    }
                }
            }

            logger.Info("Данные успешно десериализованы из TXT файла {0}", filePath);
            return playersList;
        }

        public void serializationXML(string filePath)
        {
            try
            {
                List<FootballPlayers> footballPlayers = fotbal.ItemsSource as List<FootballPlayers>;

                XmlSerializer xmlSerializer = new XmlSerializer(typeof(List<FootballPlayers>));

                using (FileStream file = new FileStream(filePath, FileMode.OpenOrCreate))
                {
                    xmlSerializer.Serialize(file, footballPlayers);
                }

                logger.Info("Данные успешно сериализованы в XML файл {0}", filePath);
            }
            catch (Exception ex)
            {
                logger.Error(ex, "Ошибка при сериализации в XML файл");
                MessageBox.Show(ex.Message, "Error");
            }
        }

        public void deserializeXML(string filePath)
        {
            try
            {
                XmlSerializer xmlSerializer = new XmlSerializer(typeof(List<FootballPlayers>));

                using (FileStream file = new FileStream(filePath, FileMode.OpenOrCreate))
                {
                    List<FootballPlayers> footballPlayers = xmlSerializer.Deserialize(file) as List<FootballPlayers>;

                    fotbal.ItemsSource = footballPlayers;
                }

                logger.Info("Данные успешно десериализованы из XML файла {0}", filePath);
            }
            catch (Exception ex)
            {
                logger.Error(ex, "Ошибка при десериализации из XML файла");
                MessageBox.Show(ex.Message, "Error");
            }
        }

    }
}
