using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections.ObjectModel;
using System.Windows.Input;
using MvvmHelpers;

namespace lib2
{
    public class FootballPlayer : BaseViewModel
    {
        public string name;
        public string firstName;
        public string position;
        public bool _isSelected;



        public FootballPlayer(string name, string firstName, string position)
        {
            this.name = name;
            this.firstName = firstName;
            this.position = position;
        }

        public string Name
        {
            get { return name; }
            set { name = value; }
        }

        public string FirstName
        {
            get { return firstName; }
            set { firstName = value; }
        }

        public string Position
        {
            get { return position; }
            set { position = value; }
        }


        public bool IsSelected
        {
            get { return _isSelected; }
            set
            {
                _isSelected = value;
                OnPropertyChanged(nameof(IsSelected));
            }
        }
    }
}
