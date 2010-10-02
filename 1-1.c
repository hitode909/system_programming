/*
 * 簡単なforkの使い方
 */

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {

  pid_t child;
  if((child = fork()) == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  } else if(child == 0) {
    puts("子プロセスで");
    printf("\t子のpid = %d\n", getpid());
    printf("\t子のppid = %d\n", getppid());
    exit(EXIT_SUCCESS);
  } else {
    puts("親プロセスで");
    printf("\t親のpid = %d\n", getpid());
    printf("\t親のppid = %d\n", getppid());
  }
  exit(EXIT_SUCCESS);
}
