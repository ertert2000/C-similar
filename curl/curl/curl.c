#include <stdio.h>
#include <curl/curl.h>
#include "func.h"

//int main()
//{
//	CURL* hande = curl_easy_init();
//	if (hande)
//	{
//		curl_easy_setopt(hande, CURLOPT_URL, "https://ru.wikipedia.org/wiki/GTK");
//		CURLcode res = curl_easy_perform(hande);
//		curl_easy_cleanup(hande);
//	}
//
//	getchar();
//	return 0;
//}
int main()
{
    CURL* curl_handle = curl_easy_init();
    if (curl_handle)
    {
        // задаем  url адрес
        curl_easy_setopt(curl_handle, CURLOPT_URL, "https://www.cyberforum.ru");
        // выполняем запрос
        CURLcode res = curl_easy_perform(curl_handle);
        // закрываем дескриптор curl
        curl_easy_cleanup(curl_handle);
    }

    getchar();
    return 0;
}