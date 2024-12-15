using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows;
using Ookii.Dialogs.Wpf;

namespace lib3_1
{
    public partial class MainWindow
    {
        private void FolderBrowserDialogClick(object sender, RoutedEventArgs e)
        {
            using (var folderDialog = new FolderBrowserDialog())
            {
                var dialog = new VistaFolderBrowserDialog();
                if (dialog.ShowDialog() == true)
                {
                    string selectedFolderPath = dialog.SelectedPath;
                }
            }
        }
    }
}
