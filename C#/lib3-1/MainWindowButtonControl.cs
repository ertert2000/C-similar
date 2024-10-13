using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace lib3_1
{
    public partial class MainWindow
    {
        private bool fladWindwoState = false;


        private void closeButtonClick(object sender, RoutedEventArgs e) => Close();

        private void buttonFullSreanClick(object sender, RoutedEventArgs e) => this.WindowState = WindowState.Minimized;

        private void hideButtonClick(object sender, RoutedEventArgs e)
        {
            if (!fladWindwoState)
            {
                this.WindowState = WindowState.Maximized;
                fladWindwoState = true;
            }
            else
            {
                this.WindowState = WindowState.Normal;
                fladWindwoState = false;
            }

        }
    }
}
