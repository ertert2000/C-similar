using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;

namespace lib2
{
    public class ControlButtonsViewModel : INotifyPropertyChanged
    {
        public ICommand closeButton { get; }
        public ICommand hideButton { get; }
        public ICommand fullScreanButton { get; }


        private Window _window;
        private bool flagFullScrean = false;

        public ControlButtonsViewModel(Window window)
        {
            _window = window;
            closeButton = new RelayCommandControl(o => _window.Close());
            hideButton = new RelayCommandControl(o => _window.WindowState = WindowState.Minimized);
            fullScreanButton = new RelayCommandControl(o => FullScrean());
        }

        private void FullScrean()
        {
            if(flagFullScrean == false)
            {
                _window.WindowState = WindowState.Maximized;
                flagFullScrean = true;
            }
            else
            {
                _window.WindowState = WindowState.Normal;
                flagFullScrean = false;
            }
        }


        public event PropertyChangedEventHandler PropertyChanged;
    }
}
