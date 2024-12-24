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

        public FootballPlayers() {}

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
            try
            {
                var selectedPlaers = fotbal.SelectedItem as FootballPlayers;

                if (selectedPlaers == null)
                    throw new PlayerNotFoundException();

                List<FootballPlayers> newPlayers = fotbal.ItemsSource as List<FootballPlayers>;

                if (newPlayers != null)
                {
                    newPlayers.Remove(selectedPlaers);

                    fotbal.ItemsSource = null;
                    fotbal.ItemsSource = newPlayers;
                }
                else
                    throw new Exception("Failed to retrieve the list of players.");
            }
            catch (PlayerNotFoundException ex)
            {
                MessageBox.Show(ex.Message, "Error");
            }
            catch (Exception ex)
            {
                MessageBox.Show($"An unexpected error occurred: {ex.Message}", "Error");
            }
        }

        public static void addPlaers(AddPlayerWindow AddPlayerWindow, MainWindow MainWindow)
        {
            try
            {
                List<FootballPlayers> newPlayers = MainWindow.fotbal.ItemsSource as List<FootballPlayers>;
                if (newPlayers == null)
                    newPlayers = new List<FootballPlayers>();

                if (AddPlayerWindow.NameTextBox.Text.Equals("") || AddPlayerWindow.FirstNameTextBox.Text.Equals("") || AddPlayerWindow.PositionTextBox.Text.Equals("") || AddPlayerWindow.PriceTextBox.Text.Equals(""))
                    throw new PlayerNotFoundException("Text fields are not filled");

                newPlayers.Add(new FootballPlayers(AddPlayerWindow.NameTextBox.Text,
                                    AddPlayerWindow.FirstNameTextBox.Text,
                                    AddPlayerWindow.PositionTextBox.Text, 
                                    1,
                                    Convert.ToInt32(AddPlayerWindow.PriceTextBox.Text),
                                    AddPlayerWindow.MainOrSpare.IsChecked ?? false));

                MainWindow.fotbal.ItemsSource = null;
                MainWindow.fotbal.ItemsSource = newPlayers;
                DatabaseHelper.AddPlayerToDatabase(new FootballPlayers(AddPlayerWindow.NameTextBox.Text,
                                    AddPlayerWindow.FirstNameTextBox.Text,
                                    AddPlayerWindow.PositionTextBox.Text,
                                    1,
                                    Convert.ToInt32(AddPlayerWindow.PriceTextBox.Text),
                                    AddPlayerWindow.MainOrSpare.IsChecked ?? false));
            }
            catch (PlayerNotFoundException ex)
            {
                MessageBox.Show(ex.Message, "Error");
            }
            catch (Exception ex)
            {
                MessageBox.Show($"An unexpected error occurred: {ex.Message}", "Error");
            }
        }
    }
}
