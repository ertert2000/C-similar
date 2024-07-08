#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

#include <sapi.h>
#include <sphelper.h>
#include <iostream>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <cstdlib>

// Функция для синтеза речи
void speak(const std::string& text) {
    // Инициализация COM
    if (FAILED(::CoInitialize(NULL))) {
        std::cerr << "Failed to initialize COM." << std::endl;
        return;
    }

    // Создание голосового синтезатора
    ISpVoice* pVoice = NULL;
    if (FAILED(::CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice))) {
        std::cerr << "Failed to create voice instance." << std::endl;
        ::CoUninitialize();
        return;
    }

    // Установка голоса на русский (если установлен соответствующий пакет)
    ISpObjectToken* pToken = NULL;
    if (SUCCEEDED(SpFindBestToken(SPCAT_VOICES, L"language=419", NULL, &pToken))) {
        pVoice->SetVoice(pToken);
        pToken->Release();
    }

    // Синтез текста
    std::wstring wtext(text.begin(), text.end());
    pVoice->Speak(wtext.c_str(), SPF_IS_XML, NULL);

    // Очистка
    pVoice->Release();
    ::CoUninitialize();
}

int main() {
    // Установка переменной окружения TESSDATA_PREFIX
    //const char* tessDataPath = "C:\\path\\to\\tessdata"; // Укажите путь к директории tessdata
    //_putenv_s("TESSDATA_PREFIX", tessDataPath); // Для Windows

    // Путь к изображению с рукописным текстом
    const char* imagePath = "222.png";

    // Инициализация Tesseract OCR
    tesseract::TessBaseAPI* ocr = new tesseract::TessBaseAPI();
    if (ocr->Init(NULL, "rus")) {
        std::cerr << "Could not initialize tesseract." << std::endl;
        return 1;
    }

    // Загрузка изображения
    Pix* image = pixRead(imagePath);
    if (!image) {
        std::cerr << "Could not read image." << std::endl;
        return 1;
    }

    // Распознавание текста
    ocr->SetImage(image);
    std::string outText = std::string(ocr->GetUTF8Text());

    // Вывод распознанного текста
    std::cout << "Recognized Text: " << std::endl << outText << std::endl;

    // Синтез речи
    speak(outText);

    // Очистка
    ocr->End();
    pixDestroy(&image);

    return 0;
}
