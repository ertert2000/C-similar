using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Documents;
using System.Windows.Forms;

namespace lib3_1
{
    public partial class MainWindow
    {
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
            }
            catch (SerializationException ex)
            {
                MessageBox.Show(ex.Message, "Serialization error");
            }
            catch (Exception ex)
            {
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
            }
            catch (SerializationException ex)
            {
                MessageBox.Show(ex.Message, "Serialization error");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error");
            }
        }
    }
}
