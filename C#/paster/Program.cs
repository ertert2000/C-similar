using System;
using System.IO;
using System.Linq;
using HtmlAgilityPack;

class Program
{
    static void Main(string[] args)
    {
        HtmlWeb htmlWeb = new HtmlWeb();
        HtmlDocument doc = htmlWeb.Load("https://www.bbc.com/russian");
        //File.Create("News.txt");

        var panelNews = doc.DocumentNode.SelectNodes("//div[@class='promo-text']");
        foreach (var tag in panelNews)
        {
            var H3 = tag.Descendants("h3");
            var time = tag.Descendants("time");
            var p = tag.Descendants("p");
            var urlNew = H3.FirstOrDefault().Descendants("a");

            Console.WriteLine($"Заголовок: {H3.FirstOrDefault().InnerText}");
            File.AppendAllText("News.txt", $"Заголовок: {H3.FirstOrDefault().InnerText}\n");
            try
            {
                var attributeValue = time.FirstOrDefault()?.GetAttributeValue("datetime", "");

                if (string.IsNullOrEmpty(attributeValue))
                { 
                    Console.WriteLine("Дата не указана.");
                    File.AppendAllText("News.txt", "Дата не указано.\n");
                }
                else
                { 
                    Console.WriteLine($"Дата: {attributeValue}");
                    File.AppendAllText("News.txt", $"Дата: {attributeValue}\n");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Произошла ошибка: {ex.Message}");
            }

            Console.WriteLine($"Описание: {p.FirstOrDefault()?.InnerText.Trim()}");
            File.AppendAllText("News.txt", $"Описание: {p.FirstOrDefault()?.InnerText.Trim()} \n");

            Console.WriteLine($"Ссылка: {urlNew.FirstOrDefault().GetAttributeValue("href", "")}");
            File.AppendAllText("News.txt", $"Ссылка: {urlNew.FirstOrDefault().GetAttributeValue("href", "")} \n");

            Console.WriteLine();
            File.AppendAllText("News.txt", "\n");
        }
        
    }


}
