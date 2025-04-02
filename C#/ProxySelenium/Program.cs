using OpenQA.Selenium.Chrome;
using OpenQA.Selenium;


class Program
{
    public static void Main()
    {
        

        var proxy = new Proxy
        {
            Kind = ProxyKind.Manual,
            IsAutoDetect = false,
            HttpProxy = $"{proxy_host}:{proxy_port}",
            SslProxy = $"{proxy_host}:{proxy_port}",
        };
        var options = new ChromeOptions
        {
            Proxy = proxy
        };
        //options.AddArgument($"--proxy-server=https://{proxy_user}:{proxy_pass}@{proxy_host}:{proxy_port}");

        using (var driver = new ChromeDriver(options))
        {
            driver.Navigate().GoToUrl("https://sicmt.ru/fgis-taksi/car?id=7539cc86-2315-4c41-be86-646237a43025");
            Thread.Sleep(3000);

            driver.FindElement(By.ClassName("sic-fgis-card_topButton")).Click();
            Thread.Sleep(10000);
            driver.Quit();
        }

    }
}
