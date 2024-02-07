#include <stdio.h>
#include <stdlib.h>


int Descending_Compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
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

    qsort(arr, n, sizeof(int), Descending_Compare);

    printf("Sorted Array in Descending Order: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr); //as array no longer needed
    return 0;
}

