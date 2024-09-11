using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lib1
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Random rnd = new Random();
            int[] arr = new int[10];

            for (int i = 0; i < arr.Length; i++)
                arr[i] = rnd.Next(0, 15);

            var sortArr = arr.OrderBy(x => x);

            foreach (int i in sortArr)
                Console.WriteLine(i);
        }
    }
}
