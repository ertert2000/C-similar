using MvvmHelpers;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace lib2
{
    public class TableViewModel : BaseViewModel
    {
        public ObservableCollection<FootballPlayer> FootballPlayers { get; set; }
        public ObservableCollection<string> PositionsList { get; set; }

        public FootballPlayer _selectedEmployee;
        public FootballPlayer SelectedEmployee
        {
            get { return _selectedEmployee; }
            set
            {
                _selectedEmployee = value;
                OnPropertyChanged(nameof(SelectedEmployee));
            }
        }

        public ICommand AddEmployeeCommand { get; set; }
        public ICommand RemoveEmployeeCommand { get; set; }

        public TableViewModel()
        {
            FootballPlayers = new ObservableCollection<FootballPlayer>
            {
            new FootballPlayer ("Иван", "524", "Программист"),
            new FootballPlayer ("Не Иван", "524", "Программист"),
            };

            PositionsList = new ObservableCollection<string>
            {
            "Программист",
            "Менеджер",
            "Тренер"
            };

            AddEmployeeCommand = new RelayCommandControl(AddEmployee);
            RemoveEmployeeCommand = new RelayCommandControl(RemoveEmployee, CanRemoveEmployee);
        }

        private void AddEmployee()
        {
            FootballPlayers.Add(new FootballPlayer("Иван", "524", "Программист"));
        }

        private bool CanRemoveEmployee()
        {
            return SelectedEmployee != null;
        }

        private void RemoveEmployee()
        {
            if (SelectedEmployee != null)
            {
                FootballPlayers.Remove(SelectedEmployee);
            }
        }


    }
}
