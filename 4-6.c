#include <stdio.h>
#include <string.h>
#include <pwd.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#define TARGET_NAME "harada"
#define OTHER_NAME "root"

void handler(int);

void block_sigalrm() {
   if(sighold(SIGALRM)<0){
      perror("sighold");
      exit(EXIT_FAILURE);
    }
}

void unblock_sigalrm() {
  if(sigrelse(SIGALRM)<0){
    perror("sigrelse");
    exit(EXIT_FAILURE);
  }
}

int main(void){
  struct passwd *ptr;

  if(signal(SIGALRM, handler)==SIG_ERR){
    perror("signal");
    exit(EXIT_FAILURE);
  }

  alarm(1);

  for(;;){
    block_sigalrm();
    ptr = getpwnam(TARGET_NAME);
    if(ptr==NULL){
      perror("getpwnam");
      exit(EXIT_FAILURE);
    }

    if(strcmp(ptr->pw_name,TARGET_NAME) != 0){
      printf("return value corrupted! pw_name =%s\n",ptr->pw_name);
      exit(EXIT_FAILURE);
    }
    unblock_sigalrm();
  }
}

void handler(int signum){
  struct passwd *ptr;

  printf("in signal handler\n");
  ptr = getpwnam(OTHER_NAME);
  if(ptr==NULL){
    perror("getpwnam");
    exit(EXIT_FAILURE);
  }

  alarm(1);
}
