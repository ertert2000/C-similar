#include <stdio.h>
#include "heder/func.h"
#include <locale.h>
#include "libxl.h"
#include <curl/curl.h>
#include <string.h>

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
struct car
{
	int weht;
	char * model;
};

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
//static size_t WD(char* ptr, size_t size, size_t nmemb, FILE * data)
//{
//	return fwrite(ptr, size, nmemb, data);
//}
//int main()
//{
//
//    FILE* header= fopen("heder.txt", "w");
//    if (header == NULL)
//        return 1;
//    FILE* body = fopen("body.html", "w");
//    if (body == NULL)
//        return 1;
//
//    CURL* curl_handle = curl_easy_init();
//    if (curl_handle)
//    {
//        curl_easy_setopt(curl_handle, CURLOPT_URL, "https://www.cyberforum.ru");
//
//
//        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, body);
//        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WD);
//
//        curl_easy_setopt(curl_handle, CURLOPT_WRITEHEADER, header);
//
//        CURLcode res = curl_easy_perform(curl_handle);
//        if (res != CURLE_OK)
//            puts("xuina");
//        curl_easy_cleanup(curl_handle);
//    }
//
//    fclose(header);
//    fclose(body);
//
//    getchar();
//    return 0;
//}

//int main()
//{
//	char str[100];
//	
//	fgets(str, 100, stdin);
//	while ((getchar()) != '\n');
//	FILE* stringg = fopen(str, "w");
//	if (stringg == NULL)
//		return 1;
//	for (int i = 0; i < 10; i++)
//		fprintf(stringg, "%d", i);
//	fclose(stringg);
//	return 0;
//}

int main() {
    char str[100];
    printf("������� ��� �����: ");

    fgets(str, sizeof(str), stdin);

    // �������� ������� ����� ������, ���� �� ������������
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }

    FILE* filePointer = fopen(str, "w");
    if (filePointer == NULL) {
        perror("������ ��� �������� �����");
        return 1;
    }

    for (int i = 0; i < 10; i++) {
        fprintf(filePointer, "%d", i);
    }

    fclose(filePointer);
    return 0;
}