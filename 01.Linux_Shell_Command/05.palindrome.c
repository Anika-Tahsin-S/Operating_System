#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h> // char handling like checking whether a character is alphanumeric, converting characters to uppercase or lowercase, etc.


bool isPalindrome(const char* str) {
    int length = strlen(str);
    const char* start = str; // init pointer start to the begining of input str
    const char* end = str + length - 1;

    while (start < end) {
        if (tolower(*start) != tolower(*end)) {
            return false;
        }
        start++;
        end--;
    }
    return true;
}

int main() {
    char input[100];

    printf("Enter a string: ");
    fgets(input, sizeof(input), stdin); // reads line
    input[strcspn(input, "\n")] = '\0'; // finding length of input file not have \n

    if (isPalindrome(input)) {
        printf("Palindrome\n");
    } else {
        printf("Not Palindrome\n");
    }

    return 0;
}
