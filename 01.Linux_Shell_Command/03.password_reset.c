#include <stdio.h>
#include <stdbool.h> // bool for true false
#include <ctype.h> // character handle
#include <string.h>

bool hasLowercase(char password) {
    return islower(password) != 0;
}
bool hasUppercase(char password) {
    return isupper(password) != 0;
}
bool hasDigit(char password) {
    return isdigit(password) != 0;
}
bool hasSpecialChar(char password) {
    return strchr("_,$#@", password) != NULL;
}

int main() {
    char password[100];
    printf("Enter a password: ");
    scanf("%s", password);

    bool isLowerMissing = true;
    bool isUpperMissing = true;
    bool isDigitMissing = true;
    bool isSpecialCharMissing = true;

    for (int i = 0; password[i] != '\0'; i++) {
        if (hasLowercase(password[i])) {
            isLowerMissing = false;
        }
        if (hasUppercase(password[i])) {
            isUpperMissing = false;
        }
        if (hasDigit(password[i])) {
            isDigitMissing = false;
        }
        if (hasSpecialChar(password[i])) {
            isSpecialCharMissing = false;
        }
    }

    bool hasErrors = false;

    if (isLowerMissing) {
        //if (hasErrors) {
        //  printf(", ");
        //}
        printf("Lowercase character missing");
        hasErrors = true;
    }
    if (isUpperMissing) {
        if (hasErrors) {
            printf(", ");
        }
        printf("Uppercase character missing");
        hasErrors = true;
    }
    if (isDigitMissing) {
        if (hasErrors) {
            printf(", ");
        }
        printf("Digit missing");
        hasErrors = true;
    }
    if (isSpecialCharMissing) {
        if (hasErrors) {
            printf(", ");
        }
        printf("Special character missing");
    }

    if (!hasErrors) {
        printf("OK");
    }

    printf("\n");

    return 0;
}

