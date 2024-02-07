#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void Grandchild(int id) {
    printf("%d. Grandchild process ID: %d\n", id, getpid());
}

void Child() {
    printf("2. Child process ID: %d\n", getpid());

    for (int i = 0; i < 3; i++) {
        pid_t grandchild_Pid = fork();

        if (grandchild_Pid == 0) {
            Grandchild(i + 3);
            return;
        } else if (grandchild_Pid < 0) {
            perror("Error grandchild process");
            return;
        } else {
            wait(NULL);
        }
    }
}

int main() {
    printf("1. Parent process ID: %d\n", getpid());

    pid_t child_Pid = fork();

    if (child_Pid == 0) {
        Child();
    } else if (child_Pid < 0) {
        perror("Error creating child process");
        return 1;
    } else {
        wait(NULL);
    }
    return 0;
}

