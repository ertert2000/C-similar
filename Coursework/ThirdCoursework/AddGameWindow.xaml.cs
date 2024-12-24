using System;
using System.Collections.Generic;
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

namespace lib3_1
{
    /// <summary>
    /// Логика взаимодействия для AddGameWindow.xaml
    /// </summary>
    public partial class AddGameWindow : Window
    {
        private readonly MainWindow _mainWindow;
        public AddGameWindow(MainWindow mainWindow)
        {
            InitializeComponent();
            _mainWindow = mainWindow;
        }

        private void AddGameButtonClick(object sender, RoutedEventArgs e)
        {
            // Создаем новую игру
            var newGame = new FootbalGames
            {
                HomeTeam = HomeTeamTextBox.Text,
                AwayTeam = AwayTeamTextBox.Text,
                GameDate = GameDatePicker.SelectedDate ?? DateTime.Now,
                IsPlayed = IsPlayedCheckBox.IsChecked ?? false
            };

            // Добавляем в базу данных
            DatabaseHelper.AddGameToDatabase(newGame);

            // Перезагружаем данные игр
            _mainWindow.LoadGames();

            // Закрываем окно
            Close();
        }
    }
}
