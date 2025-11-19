#include <stdio.h>      // printf, perror
#include <stdlib.h>     // exit, srandom, random
#include <sys/types.h>  // pid_t
#include <sys/wait.h>   // wait, WIFEXITED, WEXITSTATUS
#include <unistd.h>     // fork, getpid, getppid, sleep
#include <time.h>       // time

void ChildProcess(void);

int main(void) {
    pid_t pid1, pid2, finished_pid;
    int status;

    /* First fork */
    pid1 = fork();

    if (pid1 < 0) {
        perror("First fork failed");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        /* First child */
        ChildProcess();
        /* Not reached */
    } else {
        /* In parent after first fork — do second fork */
        pid2 = fork();

        if (pid2 < 0) {
            perror("Second fork failed");
            exit(EXIT_FAILURE);
        } else if (pid2 == 0) {
            /* Second child */
            ChildProcess();
            /* Not reached */
        }

        /* Parent: wait for both children to complete */
        finished_pid = wait(&status);
        if (finished_pid == -1) {
            perror("wait failed");
        } else {
            if (WIFEXITED(status)) {
                printf("Child Pid: %d has completed with status %d\n",
                       (int)finished_pid, WEXITSTATUS(status));
            } else {
                printf("Child Pid: %d has completed abnormally\n",
                       (int)finished_pid);
            }
        }

        finished_pid = wait(&status);
        if (finished_pid == -1) {
            perror("wait failed");
        } else {
            if (WIFEXITED(status)) {
                printf("Child Pid: %d has completed with status %d\n",
                       (int)finished_pid, WEXITSTATUS(status));
            } else {
                printf("Child Pid: %d has completed abnormally\n",
                       (int)finished_pid);
            }
        }
    }

    return 0;
}

void ChildProcess(void) {
    int max_loop;
    int i;

    /* Seed RNG differently for each child and each run */
    unsigned int seed = (unsigned int)(time(NULL) ^ getpid());
    srandom(seed);

    /* Random number of iterations: 1..30 (no more than 30, at least 1) */
    max_loop = (int)(random() % 30) + 1;

    for (i = 0; i < max_loop; i++) {
        /* Random sleep each iteration: 1..10 seconds */
        int sleep_time = (int)(random() % 10) + 1;

        printf("Child Pid: %d is going to sleep!\n", (int)getpid());
        sleep(sleep_time);
        printf("Child Pid: %d is awake!\nWhere is my Parent: %d\n",
               (int)getpid(), (int)getppid());
    }

    exit(EXIT_SUCCESS);
}
