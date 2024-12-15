using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace lib3_1
{
    public partial class MainWindow
    {
        private void buttonRemoveClick(object sender, RoutedEventArgs e) => FootballPlayers.deletePlaers(fotbal);

        private void fotbalKeyDelete(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Delete)
                FootballPlayers.deletePlaers(fotbal);
        }

        private void DeleteMenuItemClick(object sender, RoutedEventArgs e) => FootballPlayers.deletePlaers(fotbal);

        private void CellEditEndingClick(object sender, DataGridCellEditEndingEventArgs e)
        {
            var editElement = e.EditingElement as TextBox;
            if (editElement != null)
                MessageBox.Show($"New meaning: {editElement.Text}");

        }

        private void AddPlayerClick(object sender, RoutedEventArgs e)
        {
            AddPlayerWindow addPlayer = new AddPlayerWindow(this);
            addPlayer.Show();
        }

        private void fotbalSelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (fotbal.SelectedItem is FootballPlayers selectedPlayers)
            {
                nameTextBlock.Text = "Name: " + selectedPlayers.name;
                firstNameTextBlock.Text = "First name: " + selectedPlayers.firstName;
                positionTextBlock.Text = "Position: " + selectedPlayers.position;
                priceTextBlock.Text = "Price: " + selectedPlayers.price.ToString();
            }
        }
    }
}
