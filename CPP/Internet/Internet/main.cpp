#define CURL_STATICLIB
#include <iostream>
#include <curl/curl.h>

using namespace std;
int main()
{
	CURL* curl;
	CURLcode res;
	curl = curl_easy_init();

	curl_easy_setopt(curl, CURLOPT_URL, "https://curl.se/libcurl/c/libcurl-tutorial.html");
	//curl_easy_setopt(curl, CUR);
	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);


	return 0;
}