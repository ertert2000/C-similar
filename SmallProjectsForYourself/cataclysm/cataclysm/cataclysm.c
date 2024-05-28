//#include <stdio.h>
//#include <locale.h>
//#include <libintl.h>
//#define _(String) gettext(String)
//#define PACKAGE "cataclysm"
//#define LOCALEDIR "./locale/"
//
//
//int main()
//{
//	system("chcp 65001");
//	setlocale(LC_ALL, "");
//	bindtextdomain(PACKAGE, LOCALEDIR);
//	textdomain(PACKAGE);
//	printf(_("hello word"));
//	getchar();
//	return 0;
//}

//bind_textdomain_codeset(PACKAGE, "WINDOWS-1251");

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <string.h> 
#include <ctype.h> 

int isVowel(char c) {
    char vowels[] = "aeiouAEIOU";
    for (int i = 0; i < strlen(vowels); i++) {
        if (c == vowels[i]) {
            return 1;
        }
    }
    return 0;
}

void sortWords(char words[][50], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strlen(words[i]) > strlen(words[j])) {
                char temp[50];
                strcpy(temp, words[i]);
                strcpy(words[i], words[j]);
                strcpy(words[j], temp);
            }
        }
    }
}

int main() {
    char delimiters[100];
    char text[1000];

    printf("Enter a string of delimiter characters: ");
    fgets(delimiters, 100, stdin);
    delimiters[strcspn(delimiters, "\n")] = 0;  // удаляем символ новой строки из ввода 

    printf("Enter the text: ");
    fgets(text, 1000, stdin);
    text[strcspn(text, "\n")] = 0;  // удаляем символ новой строки из ввода 

    char words[100][50];
    int wordCount = 0;

    char* word = strtok(text, delimiters);

    while (word != NULL && wordCount < 100) {
        if (isVowel(word[0])) {
            strcpy(words[wordCount], word);
            wordCount++;
        }
        word = strtok(NULL, delimiters);
    }

    sortWords(words, wordCount);

    printf("Words starting with a vowel letter in non-decreasing order of length:\n");
    for (int i = 0; i < wordCount; i++) {
        printf("%s\n", words[i]);
    }

    return 0;
}