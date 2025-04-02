using System;
using System.Net.Http;
using System.Runtime.InteropServices.JavaScript;
using System.Text.RegularExpressions;
using HtmlAgilityPack;
using Newtonsoft.Json.Linq;


class Program
{

    static async Task Main()
    {
        string html;
        HashSet<string> engWords = null;
        for (int i = 1; i <= 7; i++)
        {
            if (i == 1)
                html = File.ReadAllText($"C:\\Users\\erter\\Downloads\\Telegram Desktop\\ChatExport_2025-03-29\\messages.html");
            else
                html = File.ReadAllText($"C:\\Users\\erter\\Downloads\\Telegram Desktop\\ChatExport_2025-03-29\\messages{i}.html");

            engWords = extractEngWords(html);


            Dictionary<string, string> translate = new Dictionary<string, string>();

            foreach (string engWord in engWords)
            {
                string translation = await translateWord(engWord);
                translate[engWord] = translation;
            }

            using (StreamWriter sw = new StreamWriter("output.txt", true))
            {
                foreach (var entry in translate)
                {
                    sw.WriteLine($"{entry.Key} - {entry.Value}");
                }
            }
        }
    }

    static HashSet<string> extractEngWords(string html)
    {
        HtmlDocument doc = new HtmlDocument();
        doc.LoadHtml(html);
        
        string text = doc.DocumentNode.InnerText;
        MatchCollection matches = Regex.Matches(text, @"\b[a-zA-Z]+\b");

        return new HashSet<string>(matches.Select(x => x.Value.ToLower()));
    }

    static async Task<string> translateWord(string word)
    {
        string url = $"https://api.mymemory.translated.net/get?q={word}&langpair=en|ru";

        using (HttpClient client = new HttpClient())
        {
            string json = await client.GetStringAsync(url);
            JObject obj = JObject.Parse(json);

            return obj["responseData"]["translatedText"].ToString();
        }
    }
}