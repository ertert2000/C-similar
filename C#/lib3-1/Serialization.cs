using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Documents;

namespace lib3_1
{
    public partial class MainWindow
    {
        private string patchToSave = "save.json";
        private void WindowClose(object sender, EventArgs e) => saveData();

        private void saveData()
        {
            List<FootballPlayers> list = fotbal.ItemsSource as List<FootballPlayers>; 
            string jsonString = JsonConvert.SerializeObject(list);
            File.WriteAllText(patchToSave, jsonString);
        }

        private void loadData(string patchSave)
        {
            if (!File.Exists(patchSave))
                return;

            string jsonString = File.ReadAllText(patchSave);
            List<FootballPlayers> loadData = JsonConvert.DeserializeObject<List<FootballPlayers>>(jsonString);
            fotbal.ItemsSource = loadData;
        }
    }
}
