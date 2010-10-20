#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void block_sigint() {
  printf("block SIGINT\n");
  if(sighold(SIGINT)<0){
    perror("sighold");
    exit(EXIT_FAILURE);
  }
}

void unblock_sigint() {
  printf("unblock SIGINT\n");
  if(sigrelse(SIGINT)<0){
    perror("sigrelse");
    exit(EXIT_FAILURE);
  }
}

void block_sigchld() {
  printf("block SIGCHLD\n");
  if(sighold(SIGCHLD)<0){
    perror("sighold");
    exit(EXIT_FAILURE);
  }
}

void unblock_sigchld() {
  printf("unblock SIGCHLD\n");
  if(sigrelse(SIGCHLD)<0){
    perror("sigrelse");
    exit(EXIT_FAILURE);
  }
}

pid_t child;                    /* timeout handlerから利用するため，childはここにある */

void handler(int _) {
  int status;
  wait(&status);
  if(WIFSIGNALED(status)){
    int signum;
    signum = WTERMSIG(status);
    printf("Parent: Child was terminated by %d\n", signum);
  }
}

void timeout_handler(int _) {
  block_sigchld();
  printf("SIGALRM handler: Child timeout ! Terminating Child by sending SIGTERM.\n");
  kill(child, SIGTERM);
  pause();
}

int main(void){

  printf("Parent: Making child process...\n");
  if((child = fork()) == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  } else if(child == 0) {
    /* child */
    block_sigint();
    printf("child: sleep 5\n");
    sleep(5);
    unblock_sigint();
    pause();
    exit(EXIT_SUCCESS);
  } else {
    /* parent */
    printf("Parent: setting signal handler.\n");
    sleep(1);
    if(signal( SIGCHLD, handler) == SIG_ERR) {
      perror("signal");
      exit(EXIT_FAILURE);
    }
    if(signal(SIGALRM, timeout_handler)==SIG_ERR){
      perror("signal");
      exit(EXIT_FAILURE);
    }
    printf("Parent: waiting for Child termination.timeout = 2\n");
    alarm(2);
    kill(child, SIGINT);
    pause();
  }
  exit(EXIT_SUCCESS);
}
