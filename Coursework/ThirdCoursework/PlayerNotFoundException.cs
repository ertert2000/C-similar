using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lib3_1
{
    public class PlayerNotFoundException : Exception
    {
        public PlayerNotFoundException() : base("Selected player not found.")
        {
        }

        public PlayerNotFoundException(string message) : base(message)
        {
        }
    }
}
