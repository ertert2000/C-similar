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
            Console.WriteLine(PigIt("Hello, world !"));
        }


        public static string PigIt(string str)
        {
            string[] words = str.Split(' ');
            char temp;
            const string del = "!@#$%^&*()_+=><?.,-/";
            bool flag = true; 

            string ans = "";

            for (int i = 0; i < words.Length; i++)
            {
                for (int j = 0; j < del.Length; j++)
                    if (words[i].Contains(del[j]))
                    {
                        ans += words[i];
                        flag = false;
                    }

                if(flag)
                {
                    temp = words[i][0];
                    ans += words[i].Remove(0, 1) + temp + "ay ";
                }

                flag = true;


            }
            return ans;
        }

    }
}