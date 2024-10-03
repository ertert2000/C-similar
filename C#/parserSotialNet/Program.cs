using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using HtmlAgilityPack;
using System.Net.Http;
using System.Xml.Linq;

namespace parserSotialNet
{
    internal class Program
    {
        static void Main(string[] args)
        {
            var url = "https://vk.com/friends?id=295694678&section=all";
            var web = new HtmlWeb();
            var doc = web.Load(url);
            var nodes = doc.DocumentNode.SelectNodes("//div");

            if (nodes != null)
            {
                foreach (var node in nodes)
                {
                    Console.WriteLine(node.InnerText);
                }
            }
            else
            {
                Console.WriteLine("Не удалось найти посты.");
            }
        }
    }
}
