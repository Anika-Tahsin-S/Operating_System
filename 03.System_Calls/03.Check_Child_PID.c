#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void createChild(int child_Number) {
    printf("Child %d (PID=%d)\n", child_Number, getpid());
}

int main() {
    int a, b;
    a = fork();

    if (a == 0) {
        createChild(1);

        if (getpid() % 2 != 0) {
            b = fork();
            if (b == 0) {
                createChild(2);            
            } else if (b < 0) {
                perror("Error in generating second child process");
                return 1;
            }
        }
    } else if (a < 0) {
        perror("Error in generating first child process");
        return 1;
    } else {
        wait(NULL);
        int num_Processes = 1 + (a > 0) + (b > 0);
        printf("Number of processes created: %d\n", num_Processes);
    }
    return 0;
}

