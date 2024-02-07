#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Try: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "a");
    if (file == NULL) {
        file = fopen(argv[1], "w");
        if (file == NULL) {
            perror("Error in creating file");
            return 1;
        }
    }

    char inputString[100];
    printf("'-1' to stop!!\n");

    do {
        printf("String for txt file: ");     
        fgets(inputString, sizeof(inputString), stdin);
        inputString[strcspn(inputString, "\n")] = '\0';
        if (strcmp(inputString, "-1") != 0) {
        fprintf(file, "%s\n", inputString);
        }
    } while (strcmp(inputString, "-1") != 0);

    fclose(file);
    printf("Check txt file for the goods!\n");
    return 0;
}

