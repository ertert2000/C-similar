﻿using System;
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
using System.Windows.Shapes;

namespace lib3_1
{
    /// <summary>
    /// Логика взаимодействия для AddPlayerWindow.xaml
    /// </summary>
    public partial class AddPlayerWindow : Window
    {
        public MainWindow MainWindow;

        public AddPlayerWindow(MainWindow MainWindow)
        {
            InitializeComponent();
            this.MainWindow = MainWindow;
        }

        public void CheckBoxChecked(object sender, RoutedEventArgs e) => MainOrSpare.Content = "Main";

        public void CheckBoxUnchecked(object sender, RoutedEventArgs e) => MainOrSpare.Content = "Spare";

        public void buttonOKClicl(object sender, RoutedEventArgs e) 
        { 
            FootballPlayers.addPlaers(this, MainWindow); 

            this.Close();
        }

    }
}