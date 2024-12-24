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
using System.Windows.Media.Animation;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using SQLitePCL;

namespace lib3_1
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        
        public MainWindow()
        {
            InitializeComponent();

            Batteries.Init();
            //serialization
            DatabaseHelper.InitializeDatabase();

            loadData(patchToSave);
            
            this.Closed += WindowClose;
        }

        public void LoadGames()
        {
            var games = DatabaseHelper.GetAllGamesFromDatabase();
            gamesDataGrid.ItemsSource = games;
        }

        private void ShowSttingsPanelClick(object sender, RoutedEventArgs e)
        {

            ThicknessAnimation marginAnimation = new ThicknessAnimation();
            marginAnimation.From = new Thickness(-1000, 0, 0, 0);
            marginAnimation.To = new Thickness(0, 0, 0, 0);
            marginAnimation.Duration = TimeSpan.FromSeconds(0.2);

            SettingsPanel.BeginAnimation(MarginProperty, marginAnimation);
            SettingsPanel.HorizontalAlignment = HorizontalAlignment.Stretch;
        }

        private void ClosePanel_Click(object sender, RoutedEventArgs e)
        {
            ThicknessAnimation marginAnimation = new ThicknessAnimation();
            marginAnimation.From = new Thickness(0, 0, 0, 0);
            marginAnimation.To = new Thickness(-1000, 0, 0, 0);
            marginAnimation.Duration = TimeSpan.FromSeconds(0.4);

            SettingsPanel.BeginAnimation(MarginProperty, marginAnimation);
            SettingsPanel.HorizontalAlignment = HorizontalAlignment.Left;
        }

        private void MainButton_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
