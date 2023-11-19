#include <stdio.h>
#include "func.h"
#include <locale.h>
#include "libxl.h"
#include <curl\curl.h>
#include <string.h>
//#define CURL_STATICLIB

//int main()
//{
//	//setlocale(LC_ALL, "Rus");
//	char vector[255];
//	
//	FILE* file = fopen("test.txt", "r");
//
//	fgets(vector,255,file);
//	printf("%s", file);
//	
//	fclose(file);
//	return 0;
//}

//int main()
//{
//	int ar[3] = {1,2,3};
//	int arr[3] = { 4,5,6 };
//	char chy[4] = { 'x' ,'a' ,'h','w' };
//	
//	FILE* file = fopen("test.xls", "w");
//
//	for (int i = 0; i < 3; i++)
//		fprintf(file, "%c\t%d\t%d\t%d\n", chy[i], ar[i], arr[i], ar[i] + arr[i]);
//
//	/*for (int i = 0; i < 3; i++)
//	{
//		fprintf(file, "%d\n", ar[i] + arr[i]);
//	}*/
//
//	fclose(file);
//	return 0;
//}
static size_t WD(char* ptr, size_t size, size_t nmemb, FILE * data)
{
	return fwrite(ptr, size, nmemb, data);
}
int main()
{
	FILE* heder = fopen("heder.txt", "w");
	if (heder == NULL)
		return 1;
	FILE* body = fopen("body.html","w");
	if (body == NULL)
		return 1;

	CURL* ch = curl_easy_init();

	if (ch)
	{
		curl_easy_setopt(ch, CURLOPT_URL, "https://ru.wikipedia.org/wiki/GTK");

		curl_easy_setopt(ch, CURLOPT_WRITEDATA, body);
		curl_easy_setopt(ch, CURLOPT_WRITEFUNCTION, WD);

		curl_easy_setopt(ch, CURLOPT_WRITEHEADER, heder);

		CURLcode res = curl_easy_perform(ch);
		if (res != CURLE_OK)
			puts("alle xuyna\n");
		curl_easy_cleanup(ch);
	}

	fclose(heder);
	fclose(body);


	getchar();
	return 0;
}
