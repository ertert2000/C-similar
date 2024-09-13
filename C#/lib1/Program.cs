using System;
using System.Linq;

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
