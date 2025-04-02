using OpenQA.Selenium;
using OpenQA.Selenium.Chrome;
using OpenQA.Selenium.DevTools.V131.Profiler;
using System;
using System.Net;


namespace dossier
{
    class Program
    {
        static void Main()
        {
            string password = "apOlak155937!!";
            string login = "9117231223";
            using (var vkParser = new VKParser(password, login))
            {
                vkParser.enterInVK();

                vkParser.getAllMassege("https://vk.ru/im/convo/437212633?entrypoint=list_all");

                vkParser.Close();
            }
        }
    }
}