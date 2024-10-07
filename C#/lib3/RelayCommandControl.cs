using System;
using System.Windows.Input;

namespace lib2
{
    public class RelayCommandControl : ICommand
    {
        private readonly Action<object> execute;
        private readonly Action _execute;
        private readonly Func<object, bool> canExecute;
        private readonly Func<bool> _canExecute;

        public RelayCommandControl(Action<object> execute, Func<object, bool> canExecute = null)
        {
            this.execute = execute;
            this.canExecute = canExecute;
        }

        public RelayCommandControl(Action execute, Func<bool> canExecute = null)
        {
            this._execute = execute;
            this._canExecute = canExecute;
        }

        public event EventHandler CanExecuteChanged
        {
            add { CommandManager.RequerySuggested += value; }
            remove { CommandManager.RequerySuggested -= value; }
        }

        public bool CanExecute(object parameter) => canExecute == null || canExecute(parameter);

        public void Execute(object parameter) => execute(parameter);
    }
}
