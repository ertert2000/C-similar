using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace lib3_1
{
    public class FootballPlayers
    {
        public int id {  get; set; }
        public int price { get; set; }
        public string name { get; set; }
        public string firstName { get; set; }
        public string position { get; set; }
        public bool mainOrSpare { get; set; }


        public FootballPlayers(string name, string firstName, string position, int id, int price, bool mainOrSpare)
        {
            this.name = name;
            this.position = position;
            this.firstName = firstName;
            this.id = id;
            this.price = price;
            this.mainOrSpare = mainOrSpare;
        }

        public static void deletePlaers(DataGrid fotbal)
        {
            var selectedPlaers = fotbal.SelectedItem as FootballPlayers;

            if (selectedPlaers != null)
            {
                List<FootballPlayers> newPlayers = fotbal.ItemsSource as List<FootballPlayers>;

                if (newPlayers != null)
                {
                    newPlayers.Remove(selectedPlaers);

                    fotbal.ItemsSource = null;
                    fotbal.ItemsSource = newPlayers;
                }
            }
            else
            {
                MessageBox.Show("Idi nakchuy");
            }
        }

        public static void addPlaers(AddPlayerWindow AddPlayerWindow, MainWindow MainWindow)
        {
            List<FootballPlayers> newPlayers = MainWindow.fotbal.ItemsSource as List<FootballPlayers>;
            if (newPlayers == null)
                newPlayers = new List<FootballPlayers>();

            newPlayers.Add(new FootballPlayers(AddPlayerWindow.NameTextBox.Text,
                                AddPlayerWindow.FirstNameTextBox.Text,
                                AddPlayerWindow.PositionTextBox.Text, 
                                1,
                                Convert.ToInt32(AddPlayerWindow.PriceTextBox.Text),
                                AddPlayerWindow.MainOrSpare.IsChecked ?? false));

            MainWindow.fotbal.ItemsSource = null;
            MainWindow.fotbal.ItemsSource = newPlayers;
        }
    }
}
