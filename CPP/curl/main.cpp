#define _CRT_SECURE_NO_WARNINGS
#include <curl/curl.h>
#include <iostream>

size_t wdata(void* ptr, size_t size, size_t nmemb, FILE* stream)
{
	size_t writ = fwrite(ptr, size, nmemb, stream);
	return writ;
}

int main()
{
	CURL* curl = curl_easy_init();
	FILE* file = fopen("haarcascade_frontalface_default.xml", "wb");

	//curl_easy_setopt(curl, CURLOPT_URL, "https://raw.githubusercontent.com/opencv/opencv/4.x/data/haarcascades/haarcascade_eye.xml");haarcascade_frontalface_default.xml
	curl_easy_setopt(curl, CURLOPT_URL, "https://raw.githubusercontent.com/opencv/opencv/4.x/data/haarcascades/haarcascade_frontalface_default.xml");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, wdata);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

	CURLcode res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	fclose(file);

	return 0;
}





//const char* smtp_server = "smtp://smtp.gmail.com:587";
//const char* from_email = "alekseipoliakoff@gmail.com";
//const char* to_email = "ertert2000@yandex.ru";
//const char* subject = "Еще одно тестовое письмо";
//const char* email_body = "Привет мир, это робот";
//const char* password = "kcnw bsbb eyvt aspu"; // Пароль вашей учетной записи Gmail
//
//// Функция для чтения данных письма
//size_t payload_source(void* ptr, size_t size, size_t nmemb, void* userp) {
//    const char** payload = (const char**)userp;
//
//    if (*payload == nullptr) {
//        return 0; // Конец данных
//    }
//
//    size_t len = strlen(*payload);
//    size_t total_size = size * nmemb;
//
//    if (len > total_size) {
//        len = total_size;
//    }
//
//    memcpy(ptr, *payload, len);
//    *payload += len;
//
//    return len;
//}
//
//int main() {
//    CURL* curl;
//    CURLcode res = CURLE_OK;
//    struct curl_slist* recipients = nullptr;
//    const char* payload = email_body;
//
//    // Инициализация libcurl
//    curl = curl_easy_init();
//    if (curl) {
//        // Настройки SMTP-сервера
//        curl_easy_setopt(curl, CURLOPT_URL, smtp_server);
//        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL); // Включаем SSL/TLS
//
//        // Устанавливаем учетные данные для аутентификации
//        curl_easy_setopt(curl, CURLOPT_USERNAME, from_email);
//        curl_easy_setopt(curl, CURLOPT_PASSWORD, password);
//
//        // Устанавливаем получателей
//        recipients = curl_slist_append(recipients, to_email);
//        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
//
//        // Устанавливаем отправителя
//        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, from_email);
//
//        // Настраиваем данные письма
//        std::string full_email = "To: " + std::string(to_email) + "\r\n" +
//            "From: " + std::string(from_email) + "\r\n" +
//            "Subject: " + subject + "\r\n\r\n" + email_body;
//        const char* payload_ptr = full_email.c_str();
//
//        curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
//        curl_easy_setopt(curl, CURLOPT_READDATA, &payload_ptr);
//        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
//
//        // Отправляем письмо
//        res = curl_easy_perform(curl);
//
//        if (res != CURLE_OK) {
//            std::cerr << "Ошибка при отправке письма: " << curl_easy_strerror(res) << std::endl;
//        }
//        else {
//            std::cout << "Письмо успешно отправлено!" << std::endl;
//        }
//
//        // Освобождаем память
//        curl_slist_free_all(recipients);
//        curl_easy_cleanup(curl);
//    }
//
//    return (res == CURLE_OK) ? 0 : 1;
//}