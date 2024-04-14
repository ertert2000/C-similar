using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Diagnostics.CodeAnalysis;
using System.Globalization;
using System.Linq;
using System.Runtime.InteropServices;
using System.Runtime.Remoting.Messaging;
using System.Security.Cryptography;
using System.Text.RegularExpressions;
using System.Windows;

namespace Solution
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine(PigIt("Hello world !"));
            Console.WriteLine(PigIt2("Hello world !"));
        }


        public static string PigIt(string str)
        {
            string[] words = str.Split(' ');
            char temp;

            string ans = "";

            for (int i = 0; i < words.Length; i++)
            {

                temp = words[i][0];
                words[i].Remove(0);
                ans += words[i] + temp;

                ans += "ay ";

            }



            //str.Replace()






            //for (int j = 0; j < words[i].Length; j++)
            //{

            //}



            return ans;
        }


















        public static string PigIt2(string str)
        {

            var words = str.Split(' ');
            foreach (var word in words)
            {
                if (word.Length > 1)
                {
                    word.Concat(word[0].ToString() + "ay");
                    word.Remove(word[0]);
                }
            }
            string.Join(" ", words);
            return str;
        }
    }
}