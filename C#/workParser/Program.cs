using System;
using System.Net.Http;
using System.Threading.Tasks;
using HtmlAgilityPack;
using System.Collections.Generic;


class Program
{
    static async Task Main(string[] args)
    {
        string url = "https://spb.hh.ru/search/vacancy?enable_snippets=false&experience=noExperience&search_field=name&search_field=company_name&search_field=description&work_format=REMOTE";

        var vacancies = await ParseVacanciesAsync(url);

        foreach (var vacancy in vacancies)
        {
            Console.WriteLine($"Title: {vacancy.Title}");
            Console.WriteLine($"Company: {vacancy.Company}");
            Console.WriteLine($"Link: {vacancy.Link}");
            Console.WriteLine($"Salary: {vacancy.Location}");
            Console.WriteLine(new string('-', 60));
        }
    }

    struct Vacancy
    {
        public string Title { get; set; }
        public string Company { get; set; }
        public string Link { get; set; }
        public string Location { get; set; }
    }

    static async Task<List<Vacancy>> ParseVacanciesAsync(string url)
    {
        var vacancies = new List<Vacancy>();
        var httpClient = new HttpClient();
        httpClient.DefaultRequestHeaders.Add("User-Agent", "Mozilla/5.0");

        var response = await httpClient.GetStringAsync(url);

        var htmlDoc = new HtmlDocument();
        htmlDoc.LoadHtml(response);

        var nodes = htmlDoc.DocumentNode.SelectNodes("//div[contains(@class, 'vacancy-serp-item')]");

        if (nodes != null)
        {
            foreach (var node in nodes)
            {
                var titleNode = node.SelectSingleNode("");
                var companyNode = node.SelectSingleNode("");
                var locationNode = node.SelectSingleNode("");

                string title = titleNode?.InnerText?.Trim() ?? "Нет названия";
                string link = titleNode?.GetAttributeValue("href", "") ?? "Нет ссылки";
                string company = companyNode?.InnerText?.Trim() ?? "Не указана";
                string location = locationNode?.InnerText?.Trim() ?? "Где-то";

                vacancies.Add(new Vacancy
                {
                    Title = HtmlEntity.DeEntitize(title),
                    Company = HtmlEntity.DeEntitize(company),
                    Location = HtmlEntity.DeEntitize(location),
                    Link = link
                });
            }
        }

        return vacancies;
    }
}