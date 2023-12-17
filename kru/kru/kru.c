#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <libintl.h>

#define _(String) gettext(String)

struct Numbers {
    const char* units[10];
    const char* tens[10];
    const char* hundreds[10];
};

void printNumberInWords(int number, const struct Numbers* translations) {
    if (number < 0 || number > 9999) {
        printf("Number out of range.\n");
        return;
    }

    int thousands = number / 1000;
    int hundreds = (number % 1000) / 100;
    int tens = (number % 100) / 10;
    int units = number % 10;

    if (thousands > 0)
        printf("%s %s ", translations->hundreds[thousands], _("thousands"));

    if (hundreds > 0)
        printf("%s %s ", translations->hundreds[hundreds], _("hundreds"));

    if (tens == 1) {
        printf("%s ", translations->tens[units]);
    }
    else {
        if (tens > 1)
            printf("%s ", translations->tens[tens]);
        if (units > 0)
            printf("%s ", translations->units[units]);
    }

    printf("%s\n", _("rubles"));
}

int main() {
    setlocale(LC_ALL, "");
    bindtextdomain("kru", "locale");
    textdomain("kru");

    struct Numbers russianTranslations = {
        {"", _("one"), _("two"), _("three"), _("four"), _("five"), _("six"), _("seven"), _("eight"), _("nine")},
        {"", _("ten"), _("twenty"), _("thirty"), _("forty"), _("fifty"), _("sixty"), _("seventy"), _("eighty"), _("ninety")},
        {"", _("one hundred"), _("two hundred"), _("three hundred"), _("four hundred"), _("five hundred"), _("six hundred"), _("seven hundred"), _("eight hundred"), _("nine hundred")}
    };

    int inputNumber;
    printf("Enter the amount in rubles (0-9999): ");
    scanf("%d", &inputNumber);

    printNumberInWords(inputNumber, &russianTranslations);

    return 0;
}
