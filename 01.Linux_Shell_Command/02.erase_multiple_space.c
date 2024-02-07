#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 1000

int main() {
    FILE *inputFile, *outputFile; // interact with input and output data
    char inputFileName[100], outputFileName[100];
    char inputString[MAX_STRING_LENGTH];
    char outputString[MAX_STRING_LENGTH] = ""; // init with empty str
    const char space[2] = " ";
    char *word;

    printf("Enter the input file name: ");
    scanf("%s", inputFileName);

    printf("Enter the output file name: ");
    scanf("%s", outputFileName);

    inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        printf("Error: Unable to open the input file.\n");
        return 1;
    }

    outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        printf("Error: Unable to open the output file.\n");
        fclose(inputFile);
        return 1;
    }

    while (fgets(inputString, MAX_STRING_LENGTH, inputFile) != NULL) {// fgets to read line from input file into input str
        word = strtok(inputString, space); // split str into smaller str
        while (word != NULL) {
            strcat(outputString, word); // concat to the end of output str
            strcat(outputString, " "); // adds space after each word
            word = strtok(NULL, space); // gets next token (word)
        }
        strcat(outputString, "\n");
    }

    fprintf(outputFile, "%s", outputString);
    printf("Output without extra spaces -> %s.\n", outputFileName);

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}

