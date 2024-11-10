using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace lib3_1
{
    public class SerializationException : Exception
    {
        public SerializationException() : base ("Save/load error") {}

        public SerializationException(string message) : base(message) { }
    }
}
