#include <stdio.h>

int addition(int num1, int num2) {
    return num1 + num2;
}

int subtraction(int num1, int num2) {
    return num1 - num2;
}

int multiplication(int num1, int num2) {
    return num1 * num2;
}

int main() {
    int num1, num2;
    char operator;

    printf("Enter the first number: ");
    scanf("%d", &num1); // numeric input

    printf("Enter the second number: ");
    scanf("%d", &num2); // numeric input

    printf("Enter the operator (+, -, or *): ");
    scanf(" %c", &operator); // operator input %c character

    if (operator == '+') {
        printf("Result: %d\n", addition(num1, num2));
    } else if (operator == '-') {
        printf("Result: %d\n", subtraction(num1, num2));
    } else if (operator == '*') {
        printf("Result: %d\n", multiplication(num1, num2));
    } else {
        printf("Invalid operator. Please use +, -, or *.\n");
    }

    return 0;
}
