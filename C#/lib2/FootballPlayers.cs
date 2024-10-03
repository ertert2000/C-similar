using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lib2
{
    public class FootballPlayer
    {
        private string name;
        private string firstName;
        private string position;



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

    }
}
