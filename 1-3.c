/*
 * waitの例
 */
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
  pid_t child;
  int status;

  if((child = fork()) == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  } else if(child == 0) {
    printf("子プロセス：\n");
    printf("\t子のpid = %d\n", getpid());
    printf("\t子のppid = %d\n", getppid());
    exit(EXIT_SUCCESS);
  } else {
    /* 子の終了を待つ */
    wait(&status);
    printf("親プロセス：\n");
    printf("\t親のpid = %d\n", getpid());
    printf("\t親のppid = %d\n", getppid());
    printf("\t子プロセスはstatus=%dで終了した．\n", status);
  }
  exit(EXIT_SUCCESS);
}
