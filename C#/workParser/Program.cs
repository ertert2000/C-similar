using System;
using System.Net.Http;
using System.Threading.Tasks;
using HtmlAgilityPack;
using System.Collections.Generic;
using OpenQA.Selenium.Chrome;
using OpenQA.Selenium;


class Program
{
    static void Main(string[] args)
    {
        string url = "https://spb.hh.ru/search/vacancy?enable_snippets=false&experience=noExperience&search_field=name&search_field=company_name&search_field=description&work_format=REMOTE";

        Parser parser = new Parser();
        parser.connect(url);
        Thread.Sleep(5000);

        parser.close();
    }

}


class Parser
{

    private ChromeOptions options;
    private IWebDriver driver;
    public Parser()
    {
        try
        {
            options = new ChromeOptions();
            driver = new ChromeDriver(options);
        }
        catch (Exception ex)
        {
            Console.WriteLine("Error initializing ChromeDriver: " + ex.Message);
        }


    }

    public void connect(string url)
    {
        driver.Navigate().GoToUrl(url);
    }





    public void close()
    {
        driver.Quit();
    }



}