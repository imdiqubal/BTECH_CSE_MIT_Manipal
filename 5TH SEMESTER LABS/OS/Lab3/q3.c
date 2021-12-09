#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main() {
    printf("Parent process starting..\n");
    int r_val = fork();
    
    switch(r_val) {
        case -1: {
            perror("Fork..\n");
            exit(EXIT_FAILURE);
        }
        break;

        case 0: {
            printf("Inside the child process..\n");
            pid_t curr_pid = getpid();
            printf("PID of child process is: %d\n", curr_pid);
            exit(0);
        }
        break;

        default: {
            pid_t curr_pid = getpid();
            printf("PID of parent process: %d\n", curr_pid);
            printf("Waiting for child..\n");
            wait(NULL);
            printf("Child process finished execution..\n");
            exit(0);
        }
    }
}