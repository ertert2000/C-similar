using Newtonsoft.Json;
using OpenQA.Selenium;
using OpenQA.Selenium.Chrome;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using Formatting = Newtonsoft.Json.Formatting;

namespace dossier
{
    class VKParser : IDisposable
    {
        private ChromeOptions options;
        private readonly IWebDriver driver;
        private string password, login;

        public VKParser(string password, string login) 
        {
            try
            {
                options = new ChromeOptions(); 
                driver = new ChromeDriver(options);
            }
            catch (Exception e) 
            {
                Console.WriteLine(e.Message);
            }

            this.password = password;
            this.login = login;
        }

        public void enterInVK()
        {
            string SMSCode;
            try
            {
                driver.Navigate().GoToUrl("https://vk.ru");
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }

            try
            {
                driver.FindElement(By.CssSelector("button[data-testid='enter-another-way']")).Click();
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }

            try
            {
                driver.FindElement(By.CssSelector("input[name='login']")).SendKeys(login);
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }

            try
            {
                driver.FindElement(By.CssSelector("button[data-test-id='submit_btn']")).Click();
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }

            Console.WriteLine("Введите SMS-код:");
            SMSCode = Console.ReadLine() ?? "";

            try
            {
                var smsInputs = driver.FindElements(By.CssSelector("input[name='otp-cell']"));

                for (int i = 0; i < smsInputs.Count && i < SMSCode.Length; i++)
                    smsInputs[i].SendKeys(SMSCode[i].ToString());
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }

            Thread.Sleep(5000);

            try
            {
                driver.FindElement(By.CssSelector("input[name='password']")).SendKeys(password);
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }

            try
            {
                driver.FindElement(By.CssSelector("button[type='submit']")).Click();
            }
            catch (Exception e)
            { 
                Console.WriteLine(e.Message); 
            }

            Thread.Sleep(10000);
        }

        public void profilesParsing()
        {
            driver.FindElement(By.CssSelector("li[id='l_fr']")).Click();


            Thread.Sleep(5000);

            HashSet<string> profileLinks = new HashSet<string>();
            int scrollCount = 20;
            int lastHeight = 0;

            for (int i = 0; i < scrollCount; i++)
            {
                var elements = driver.FindElements(By.CssSelector("a[href^='https://vk.ru/']"));

                foreach (var el in elements)
                {
                    string link = el.GetAttribute("href");
                    if (!profileLinks.Contains(link))
                    {
                        Console.WriteLine($"Найден профиль: {link}");
                        profileLinks.Add(link);
                    }
                }



                IJavaScriptExecutor js = (IJavaScriptExecutor)driver;
                js.ExecuteScript(@"
                    function smoothScroll() {
                        var start = window.scrollY;
                        var end = document.body.scrollHeight;
                        var distance = end - start;
                        var duration = 10000; // Длительность анимации в миллисекундах
                        var startTime;

                        function scrollStep(timestamp) {
                            if (!startTime) startTime = timestamp;
                            var progress = timestamp - startTime;
                            var scrollAmount = Math.min(progress / duration, 1) * distance;
                            window.scrollTo(0, start + scrollAmount);
                            if (progress < duration) {
                                requestAnimationFrame(scrollStep);
                            }
                        }

                        requestAnimationFrame(scrollStep);
                    }
                    smoothScroll();
                ");

                Thread.Sleep(15000);

                int newHeight = Convert.ToInt32(js.ExecuteScript("return document.body.scrollHeight"));
                if (newHeight == lastHeight)
                    break;
                lastHeight = newHeight;
            }

            string[] temp = {"https://vk.ru/a.aluu",
                            "https://vk.ru/tocsotanya",
                            "https://vk.ru/toosick",
                            "https://vk.ru/crexysqe",
                            "https://vk.ru/aliceabrtop",
                            "https://vk.ru/nensides",
                            "https://vk.ru/r.shrftdnv",
                            "https://vk.ru/naroslava",
                            "https://vk.ru/sonyapoll",
                            "https://vk.ru/aliceeegubb",
                            "https://vk.ru/whyfckinalwaysme",
                            "https://vk.ru/alannuer",
                            "https://vk.ru/jolitole",
                            "https://vk.ru/crispyy1337",
                            "https://vk.ru/pingvin2107",
                            "https://vk.ru/iten3",
                            "https://vk.ru/kmspointegralam",
                            "https://vk.ru/trubinov_59",
                            "https://vk.ru/g3rb3r539",
                            "https://vk.ru/id300115677",
                            "https://vk.ru/setnapudga",
                            "https://vk.ru/ryaha22",
                            "https://vk.ru/ohayob",
                            "https://vk.ru/mdmahonest",
                            "https://vk.ru/id549516354",
                            "https://vk.ru/astatienko"};

            foreach (var t in temp)
                profileLinks.Add(t);

            foreach (var profile in profileLinks)
                dataParsingProfile(profile);
        }

        private void dataParsingProfile(string url)
        {

            if (url.Contains("ad_office"))
                return;

            driver.Navigate().GoToUrl(url);

            Thread.Sleep(5000);

            var nameElement = driver.FindElement(By.Id("owner_page_name"));
            string name = nameElement.Text.Trim();

            if (name.Equals("DELETED"))
                return;

            Console.WriteLine($"Собираем данные для {name}...");

            string folderName = $"Profiles/{name}";

            if (Directory.Exists(folderName))
                return;

            Directory.CreateDirectory(folderName);

            driver.FindElement(By.XPath("//span[contains(text(), 'Подробнее')]")).Click();
            Thread.Sleep(5000);

            using (StreamWriter writer = new StreamWriter($"{folderName}/info.txt"))
            {
                writer.WriteLine($"Имя фамилия: {name}\n");

                writer.WriteLine($"Тег: @{url.Split(new string[] { "vk.ru/" }, StringSplitOptions.None)[1]}\n");

                try
                {
                    writer.WriteLine($"{driver.FindElement(By.ClassName("ProfileFullCommonInfo__caption")).Text}\n");
                }
                catch (Exception e)
                {
                    //Console.WriteLine(e);
                }

                try
                {
                    writer.WriteLine($"{driver.FindElement(By.ClassName("ProfileFullCommonInfoCareer__caption")).Text}\n");
                }
                catch (Exception e)
                {
                    //Console.WriteLine(e);
                }

                try
                {
                    writer.WriteLine($"{driver.FindElement(By.ClassName("ProfileFullStacks__count")).Text}");
                }
                catch (Exception e)
                {
                    //Console.WriteLine(e);
                }

                try
                {
                    writer.WriteLine($"{driver.FindElement(By.ClassName("ProfileFullStacks__caption")).Text}\n");
                }
                catch (Exception e)
                {
                    //Console.WriteLine(e);
                }

                try
                {
                    writer.WriteLine($"\tЛИЧНАЯ ИНФОРМАЦИЯ\n\n");
                }
                catch (Exception e)
                {
                    //Console.WriteLine(e);
                }

                try
                {
                    writer.WriteLine($"{driver.FindElement(By.ClassName("ProfileModalInfoRow__label")).Text}");
                }
                catch (Exception e)
                {
                    //Console.WriteLine(e);
                }

                try
                {
                    writer.WriteLine($"{driver.FindElement(By.ClassName("ProfileModalInfoRow__value")).Text}\n");
                }
                catch (Exception e)
                {
                    //Console.WriteLine(e);
                }
            }

            Thread.Sleep(2000);

            driver.FindElement(By.CssSelector("div[data-testid='modal-close-button']")).Click();

            driver.FindElement(By.XPath("//span[contains(text(), 'Фото')]")).Click();

            try { driver.FindElement(By.XPath("//span[contains(text(), 'Фото')]")).Click(); } catch (Exception e) { }

            Thread.Sleep(5000);

            var photos = driver.FindElements(By.CssSelector("img[class^='PhotosPagePhotoGridVirtualItem__img--XYtyA']"));
            int photoIndex = 1;
            using (WebClient client = new WebClient())
            {
                foreach (var photo in photos)
                {
                    string photoUrl = photo.GetAttribute("src");
                    string photoPath = $"{folderName}/photo_{photoIndex}.jpg";
                    Console.WriteLine($"Скачивание фото {photoPath}");
                    client.DownloadFile(photoUrl, photoPath);
                    photoIndex++;
                }
            }
        }

        public void getAllMassege(string url)
        {
            try
            {
                driver.Navigate().GoToUrl(url);

                Thread.Sleep(5000);

                List<Dictionary<string, object>> chatData = new List<Dictionary<string, object>>();

                int lastMessageCount = 0;
                int attempts = 0;

                while (attempts < 10) // Ограничение на попытки скролла
                {
                    // Ждём загрузку контента
                    Thread.Sleep(3000);

                    // Получаем список сообщений
                    var chatBlocks = driver.FindElements(By.ClassName("ConvoHistory__dateStack"));
                    int currentMessageCount = chatBlocks.Count;

                    if (currentMessageCount == lastMessageCount) // Если ничего нового не загрузилось
                    {
                        attempts++;
                    }
                    else
                    {
                        lastMessageCount = currentMessageCount;
                        attempts = 0; // Сбрасываем попытки, если загрузились новые сообщения
                    }

                    // Парсим данные
                    foreach (var chat in chatBlocks)
                    {
                        try
                        {
                            string date = "";
                            try { date = chat.FindElement(By.ClassName("DateSeparator")).Text; }
                            catch (NoSuchElementException) { }

                            var messages = chat.FindElements(By.ClassName("ConvoHistory__messageBlock"));
                            List<Dictionary<string, string>> messageList = new List<Dictionary<string, string>>();

                            foreach (var msg in messages)
                            {
                                string userName = "", messageText = "", time = "";

                                try { userName = msg.FindElement(By.ClassName("PeerTitle__title")).Text; }
                                catch (NoSuchElementException) { }

                                try { messageText = msg.FindElement(By.ClassName("MessageText")).Text; }
                                catch (NoSuchElementException) { }

                                try { time = msg.FindElement(By.ClassName("ConvoMessageInfoWithoutBubbles__date")).Text; }
                                catch (NoSuchElementException) { }

                                messageList.Add(new Dictionary<string, string>
                            {
                                { "user", userName },
                                { "message", messageText },
                                { "time", time }
                            });
                            }

                            chatData.Add(new Dictionary<string, object>
                        {
                            { "date", date },
                            { "messages", messageList }
                        });
                        }
                        catch (Exception ex)
                        {
                            Console.WriteLine("Ошибка парсинга: " + ex.Message);
                        }
                    }

                    // Прокручиваем страницу вверх для подгрузки сообщений
                    ((IJavaScriptExecutor)driver).ExecuteScript("window.scrollBy(0, 1000);");
                }

                // Записываем в JSON
                string json = JsonConvert.SerializeObject(chatData, Formatting.Indented);
                File.WriteAllText("vk_messages.json", json);

                Console.WriteLine("Сообщения успешно сохранены в vk_messages.json");

            }
            catch (Exception ex)
            {
                Console.WriteLine("Ошибка: " + ex.Message);
            }


        }

        public void Close()
        {
            driver.Quit();
        }

        public void Dispose()
        {
            driver?.Quit();
            driver?.Dispose();
        }


    }
}
