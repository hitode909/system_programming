#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handler(int _) {
  int status;
  wait(&status);
  if(WIFSIGNALED(status)){
    int signum;
    signum = WTERMSIG(status);
    printf("Parent: Child was terminated by %d\n", signum);
  }
}

int main(void){
  pid_t child;

  printf("Parent: Making child process...\n");
  if((child = fork()) == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  } else if(child == 0) {
    pause();
    exit(EXIT_SUCCESS);
  } else {
    /* parent */
    printf("Parent: setting signal handler.\n");
    if(signal( SIGCHLD, handler) == SIG_ERR) {
      perror("signal");
      exit(EXIT_FAILURE);
    }
    printf("Parent: waiting for Child termination.\n");
    kill(child, SIGINT);
    pause();
  }
  exit(EXIT_SUCCESS);
}
