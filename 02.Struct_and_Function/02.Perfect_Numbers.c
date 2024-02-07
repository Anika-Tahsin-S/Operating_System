#include <stdio.h>

int isPerfect(int num) {
    if (num <= 1) {
        return 0;
    }
    
    int sum = 1;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            sum += i;
            if (i != num / i) {
                sum += num / i;
            }
        }
    }
    return (sum == num);
}

void print_Perfect_Numbers(int start, int end) {
    int found = 0;
    for (int i = start + 1; i <= end; i++) {
        if (isPerfect(i)) {
            found = 1;
            printf("%d\n", i);
        }
    }
    if (!found) {
        printf("No perfect numbers found in the range %d to %d\n", start, end);
    }
}
int main() {
    int start, end;
    scanf("%d\n%d", &start, &end);
    printf("\n");
    print_Perfect_Numbers(start, end);

    return 0;
}

