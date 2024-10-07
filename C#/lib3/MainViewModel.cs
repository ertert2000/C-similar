using MvvmHelpers;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace lib2
{
    public class MainViewModel : BaseViewModel
    {
        public TableViewModel TableViewModel { get; set; }
        public ControlButtonsViewModel ControlButtonsViewModel { get; set; }

        public MainViewModel(Window mainWindow)
        {
            TableViewModel = new TableViewModel();
            ControlButtonsViewModel = new ControlButtonsViewModel(mainWindow);
        }
    }
}
