#include <stdio.h>
#include <stdlib.h>

void printOddEven(int arr[], int n) {
    printf("\nOdd/Even define each number:\n");
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            printf("%d is even\n", arr[i]);
        } else {
            printf("%d is odd\n", arr[i]);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Try: %s <num1> <num2> ... <numN>\n", argv[0]);
        return 1;
    }

    int n = argc - 1;
    int *arr = (int *)malloc(n * sizeof(int)); //dynamic allocation

    for (int i = 0; i < n; i++) {
        arr[i] = atoi(argv[i + 1]);
    }

    printOddEven(arr, n);
    free(arr); //as array no longer needed
    return 0;
}

