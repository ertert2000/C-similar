#include <iostream>
#include <windows.h>
#include <string>



#include "utils.h"
#include "file_operations.h"
#include "drive_operations.h"

void ShowMenu()
{
    std::wcout << L"\nМеню:\n";
    std::wcout << L"1. Показать все диски\n";
    std::wcout << L"2. Показать информацию о диске\n";
    std::wcout << L"3. Создать каталог\n";
    std::wcout << L"4. Удалить каталог\n";
    std::wcout << L"5. Создать файл\n";
    std::wcout << L"6. Скопировать файл\n";
    std::wcout << L"7. Переместить файл\n";
    std::wcout << L"8. Показать атрибуты файла\n";
    std::wcout << L"9. Показать информацию о файле\n";
    std::wcout << L"10. Показать время файла\n";
    std::wcout << L"11. Установить время файла\n";
    std::wcout << L"12. Изменить атрибуты файла\n";
    std::wcout << L"0. Выход\n";
    std::wcout << L"Выберите опцию: ";
}

int main()
{
    std::locale::global(std::locale(""));
    std::wcout.imbue(std::locale());

    std::wcout << L"Добро пожаловать в менеджер дисков и файлов!" << std::endl;

    HANDLE hFile;

    int choice;
    int input4;
    std::wstring input, input2, input3;
    DWORD attributes = 0;

    do
    {
        system("cls");
        ShowMenu();
        std::wcin >> choice;
        std::wcin.ignore();

        switch (choice)
        {
        case 1:
            system("cls");
            ListDrives();
            system("pause");
            break;
        case 2:
            system("cls");
            std::wcout << L"Введите букву диска (например, C:\\): ";
            std::getline(std::wcin, input);
            ShowDriveInfo(input);
            system("pause");
            break;
        case 3:
            system("cls");
            std::wcout << L"Введите имя каталога: ";
            std::getline(std::wcin, input);
            if (CreateDirectory(input.c_str(), NULL) || GetLastError() == ERROR_ALREADY_EXISTS)
                std::wcout << L"Каталог создан: " << input << std::endl;
            else
                std::wcerr << L"Ошибка: не удалось создать каталог " << input << std::endl;
            break;
        case 4:
            system("cls");
            std::wcout << L"Введите имя каталога: ";
            std::getline(std::wcin, input);
            if (RemoveDirectory(input.c_str()))
                std::wcout << L"Каталог удален: " << input << std::endl;
            else
                std::wcerr << L"Ошибка: не удалось удалить каталог " << input << std::endl;
            system("pause");
            break;
        case 5:
            system("cls");
            std::wcout << L"Введите имя файла: ";
            std::getline(std::wcin, input);
            hFile = CreateFile(input.c_str(), GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

            if (hFile != INVALID_HANDLE_VALUE)
            {
                CloseHandle(hFile);
                std::wcout << L"Файл создан: " << input << std::endl;
            }
            else
                std::wcerr << L"Ошибка: не удалось создать файл " << input << std::endl;
            system("pause");
            break;
        case 6:
            system("cls");
            std::wcout << L"Введите исходное имя файла: ";
            std::getline(std::wcin, input);
            std::wcout << L"Введите имя файла назначения: ";
            std::getline(std::wcin, input2);
            CopyFile(input, input2);
            system("pause");
            break;
        case 7:
            system("cls");
            std::wcout << L"Введите исходное имя файла: ";
            std::getline(std::wcin, input);
            std::wcout << L"Введите имя файла назначения: ";
            std::getline(std::wcin, input2);
            MoveFile(input, input2);
            system("pause");
            break;
        case 8:
            system("cls");
            std::wcout << L"Введите имя файла: ";
            std::getline(std::wcin, input);
            PrintFileAttributes(input, true);
            system("pause");
            break;
        case 9:
            system("cls");
            std::wcout << L"Введите имя файла: ";
            std::getline(std::wcin, input);
            GetFileInfo(input);
            system("pause");
            break;
        case 10:
            system("cls");
            std::wcout << L"Введите имя файла: ";
            std::getline(std::wcin, input);
            ShowFileTime(input);
            system("pause");
            break;
        case 11:
            system("cls");
            std::wcout << L"Введите имя файла: ";
            std::getline(std::wcin, input);
            std::wcout << L"Введите время (гггг-мм-дд чч:мм:сс): ";
            std::getline(std::wcin, input2);
            std::wcout << L"Выберите тип времени (c для создания, a для доступа, w для записи): ";
            std::getline(std::wcin, input3);
            SetFileTime(input, input2, input3);
            system("pause");
            break;
        case 12:
            system("cls");


            std::wcout << L"Введите путь к файлу: ";
            std::getline(std::wcin, input);

            std::wcout << L"Выберите атрибуты (можно несколько, через пробел):\n"
                L"1 - Только для чтения\n"
                L"2 - Скрытый\n"
                L"3 - Системный\n"
                L"4 - Архивный\n"
                L"5 - Обычный файл (сброс остальных атрибутов)\n"
                L"Введите номера (0 - завершить): ";

            while (std::wcin >> input4 && input4 != 0)
                switch (input4)
                {
                case 1:
                    attributes |= FILE_ATTRIBUTE_READONLY;
                    break;
                case 2:
                    attributes |= FILE_ATTRIBUTE_HIDDEN;
                    break;
                case 3:
                    attributes |= FILE_ATTRIBUTE_SYSTEM;
                    break;
                case 4:
                    attributes |= FILE_ATTRIBUTE_ARCHIVE;
                    break;
                case 5:
                    attributes = FILE_ATTRIBUTE_NORMAL;
                    break;
                default:
                    std::wcout << L"Неверный ввод!\n";
                    break;
                }

            SetFileAttribute(input, attributes);
            system("pause");
            break;
        case 0:
            system("cls");
            std::wcout << L"Выход из программы." << std::endl;
            system("pause");
            break;
        default:
            system("cls");
            std::wcout << L"Неверный выбор. Пожалуйста, попробуйте снова." << std::endl;
            system("pause");
            break;
        }
    } while (choice != 0);

    return 0;
}
