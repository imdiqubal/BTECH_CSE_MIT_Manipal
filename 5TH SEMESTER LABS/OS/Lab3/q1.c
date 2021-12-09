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
                perror("Fork\n");
                exit(EXIT_FAILURE);
            }
            break;
        
        case 0: {
                printf("Inside the child process..\n");
                for(int i = 0; i < 10; i++) {
                    sleep(1);
                    printf("Sleeping child process for %d seconds..\n", i + 1);
                }
                exit(0);
            }
            break;

        default: {
                printf("Waiting for the child..\n");
                wait(NULL);
                printf("Child process finished execution..\n");
                exit(0);
            }
    }
}