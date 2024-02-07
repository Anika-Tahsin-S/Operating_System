#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void grandchildProcess() {
    printf("I am grandchild\n");
}

int main() {
    pid_t childPid = fork();

    if (childPid < 0) {
        perror("Error in generating child process");
        return 1;
    } else if (childPid == 0) {
        pid_t grandchildPid = fork();

        if (grandchildPid == 0) {
            grandchildProcess();
        } else if (grandchildPid < 0) {
            perror("Error in generating grandchild process");
            return 1;
        } else {
            wait(NULL);
            printf("I am child\n");
        }
    } else {
        wait(NULL);
        printf("I am parent\n");
    }

    return 0;
}

