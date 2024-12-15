using lib3_1;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.Windows.Controls;

namespace UnitTestProject1
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void Constructor_ShouldInitializeProperties()
        {
            string name = "Smith";
            string firstName = "John";
            string position = "Forward";
            int id = 1;
            int price = 1000;
            bool mainOrSpare = true;

            var player = new FootballPlayers(name, firstName, position, id, price, mainOrSpare);

            Assert.AreEqual(name, player.name);
            Assert.AreEqual(firstName, player.firstName);
            Assert.AreEqual(position, player.position);
            Assert.AreEqual(id, player.id);
            Assert.AreEqual(price, player.price);
            Assert.AreEqual(mainOrSpare, player.mainOrSpare);
        }

        [TestMethod]
        public void DeletePlayers_ShouldRemoveSelectedPlayer()
        {
            var dataGrid = new DataGrid();
            var players = new List<FootballPlayers>
            {
                new FootballPlayers("Smith", "John", "Forward", 1, 1000, true),
                new FootballPlayers("Doe", "Jane", "Defender", 2, 1200, false)
            };

            dataGrid.ItemsSource = players;
            dataGrid.SelectedItem = players[0];

            FootballPlayers.deletePlaers(dataGrid);

            var remainingPlayers = dataGrid.ItemsSource as List<FootballPlayers>;
            Assert.IsNotNull(remainingPlayers);
            Assert.AreEqual(1, remainingPlayers.Count);
            Assert.AreEqual("Doe", remainingPlayers[0].name);
        }

        [TestMethod]
        public void AddPlayers_ShouldAddPlayerToList()
        {
            var mainWindow = new MainWindow();
            var addPlayerWindow = new AddPlayerWindow(mainWindow)
            {
                NameTextBox = new TextBox { Text = "Ronaldo" },
                FirstNameTextBox = new TextBox { Text = "Cristiano" },
                PositionTextBox = new TextBox { Text = "Forward" },
                PriceTextBox = new TextBox { Text = "2000" },
                MainOrSpare = new CheckBox { IsChecked = true }
            };

            mainWindow.fotbal.ItemsSource = new List<FootballPlayers>();

            FootballPlayers.addPlaers(addPlayerWindow, mainWindow);

            var players = mainWindow.fotbal.ItemsSource as List<FootballPlayers>;
            Assert.IsNotNull(players);
            Assert.AreEqual(1, players.Count);
            Assert.AreEqual("Ronaldo", players[0].name);
            Assert.AreEqual(2000, players[0].price);
        }
    }
}
