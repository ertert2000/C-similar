using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Policy;
using System.Text;
using System.Threading.Tasks;
using HtmlAgilityPack;
using System.Net.Http;
using System.IO;


namespace pasterGame
{

    class Parameters
    {
        private string nameGame;
        private string mark;
        private int numMark;

        public void parsePage(string content)
        {
            HtmlDocument document = new HtmlDocument();
            document.LoadHtml(content);

            var heder = document.DocumentNode.SelectNodes("//h1").Where(x => x.GetAttributeValue("style", "").Contains("name"));

            foreach (var node in heder)
            {
                string name = node.InnerText;

                int indexDot = name.IndexOf(":");
                nameGame = name.Substring(0, indexDot);
            }

            var marks = document.DocumentNode.SelectNodes("//svg").Where(x => x.GetAttributeValue("class", "").Contains("active"));

            foreach (var nodeMarks in marks)
            {
                var use = nodeMarks.Descendants("use");

                string strMarks = use.FirstOrDefault().GetAttributeValue("href", string.Empty);

                mark = strMarks.Substring(strMarks.IndexOf("/") + 1);
            }
            showRes();
        }

        private void showRes()
        {
            switch (mark) 
            {
                case "izum":
                    numMark = 5;
                    mark = "Изумительно";
                    break;
                case "pohvalno":
                    numMark = 4;
                    mark = "Похвально";
                    break;
                case "prohodnyak":
                    numMark = 3;
                    mark = "Проходняк";
                    break;
                default:
                    numMark = 2;
                    mark = "Мусор";
                    break;
            }

            Console.WriteLine("Название: " + nameGame);
            Console.WriteLine($"Оценка: {mark} / {numMark}");
            Console.WriteLine();

            File.AppendAllText("Game.txt", "Название: " + nameGame + "\n");
            File.AppendAllText("Game.txt", $"Оценка: {mark} / {numMark}\n\n");
        }
    }
    internal class Program
    {
        
        static async Task Main(string[] args)
        {
            string prevPage = "";

            for (int i = 0; i != 181; i++)
            {
                HtmlDocument sourceDoc = null;
                HtmlWeb web = new HtmlWeb();
                if (i == 0)
                {
                    sourceDoc = web.Load("https://stopgame.ru/review");
                }
                else
                { 
                    sourceDoc = web.Load($"https://stopgame.ru/review/p{i}");
                }

                var urlGamePage = sourceDoc.DocumentNode.SelectNodes("//a").Where(x => x.GetAttributeValue("href", "").Contains("show"));

                foreach (var url in urlGamePage)
                {
                    string nextPage = url.GetAttributeValue("href", string.Empty);
                    int indexnextPage = nextPage.IndexOf("#");

                    if (indexnextPage != -1)
                        nextPage = nextPage.Substring(0, indexnextPage);

                    if (!prevPage.Equals(nextPage) || string.IsNullOrEmpty(prevPage))
                    {
                        prevPage = nextPage;
                        if (!string.IsNullOrEmpty(nextPage))
                        {
                            nextPage = "https://stopgame.ru" + nextPage;
                            string pageContent = await GetPageContentAsync(nextPage);
                            if (!string.IsNullOrEmpty(pageContent))
                            {
                                Parameters parameters = new Parameters();
                                parameters.parsePage(pageContent);
                            }
                        }
                    }
                }
            }

        }

        static async Task<string> GetPageContentAsync(string url)
        {
            using (HttpClient client = new HttpClient())
            {
                try
                {
                    HttpResponseMessage resp = await client.GetAsync(url);
                    resp.EnsureSuccessStatusCode();
                    string content = await resp.Content.ReadAsStringAsync();
                    return content;
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.Message);
                    return string.Empty;
                }
            }
        }
    }
    
}
