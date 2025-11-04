
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>


void ChildProcessOne(void);
void ChildProcessTwo(void);
void ParentProcess(void);

void main(void){

  pid_t pid, pid2, finished_pid;
  pid = fork();

  if (pid < 0){
    perror("First fork failed\n");
  }else if (pid == 0){
    ChildProcessOne();
  }else{
    pid2 = fork();
    if (pid2 < 0){
      perror("First fork failed\n");
    }else if (pid2 == 0){
      ChildProcessTwo();
    }
    finished_pid = wait(NULL);
    printf("Child Pid: %d has completed\n", finished_pid);
    finished_pid = wait(NULL);
    printf("Child Pid: %d has completed\n", finished_pid);
  }

}

void ChildProcessOne(void){
  int max_loop;
  int max_sleep;
  int i;
  srandom(50);
  max_loop = random() % 30;
  max_sleep = random() % 10;
  for (i = 1; i <= max_loop; i++){
    printf("Child Pid: %d is going to sleep!\n", getpid());
    sleep(max_sleep);
    printf("Child Pid: %d is awake!\nWhere is my Parent: %d\n", getpid(), getppid());
  };
  exit(0);

}

void ChildProcessTwo(void){
  int max_loop;
  int max_sleep;
  int i;
  srandom(50);
  max_loop = random() % 30;
  max_sleep = random() % 10;
  for (i = 1; i <= max_loop; i++){
    printf("Child Pid: %d is going to sleep!\n", getpid());
    sleep(max_sleep);
    printf("Child Pid: %d is awake!\nWhere is my Parent: %d\n", getpid(), getppid());
  };
  exit(0);
}
