#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Try: %s <num1> <num2> ... <numN>\n", argv[0]);
        return 1;
    }

    pid_t childPid = fork();

    if (childPid == 0) {
        execvp("./sort", argv);
        perror("Error in execution of sort.c");
        return 1;
    } else if (childPid < 0) {
        perror("Error in generating child process");
        return 1;
    } else {
        wait(NULL); 
        pid_t oddevenPid = fork();

        if (oddevenPid == 0) {
            execvp("./oddeven", argv);
            perror("Error in execution of oddeven.c");
            return 1;
        } else if (oddevenPid < 0) {
            perror("Error in generating oddeven process");
            return 1;
        } else {
            wait(NULL);
        }
    }
    
    int n = argc - 1;
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = atoi(argv[i + 1]);
    }
    
    free(arr);
    return 0;
}

