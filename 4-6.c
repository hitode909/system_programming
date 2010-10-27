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

int main(void){
  struct passwd pwbuf, *ptr;
  char *buf;
  int len = 3000;
  buf=malloc(len);
  if(!buf){
    perror("malloc");
    exit(EXIT_FAILURE);
  }

  if(signal(SIGALRM, handler)==SIG_ERR){
    perror("signal");
    exit(EXIT_FAILURE);
  }

  alarm(1);

  for(;;){
    if (getpwnam_r(TARGET_NAME, &pwbuf, buf, len, &ptr) != 0) {
      perror("getpwnam");
      exit(EXIT_FAILURE);
    }

    if(strcmp(ptr->pw_name,TARGET_NAME) != 0){
      printf("return value corrupted! pw_name =%s\n",ptr->pw_name);
      exit(EXIT_FAILURE);
    }
  }
  free(buf);
}

void handler(int signum){
  struct passwd pwbuf, *ptr;
  char *buf;
  int len = 3000;
  buf=malloc(len);
  if(!buf){
    perror("malloc");
    exit(EXIT_FAILURE);
  }

  printf("in signal handler\n");
  if (getpwnam_r(OTHER_NAME, &pwbuf, buf, len, &ptr) != 0) {
    perror("getpwnam");
    exit(EXIT_FAILURE);
  }
  free(buf);

  alarm(1);
}
