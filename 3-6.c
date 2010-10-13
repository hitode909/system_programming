#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <stdbool.h>

int count = 0;
bool doing = false;

void reset(int _) {
  printf("\nreset\n");
  count = 0;
}

void toggle(int _) {
  if (doing) {
    printf("\nstop\n");
    doing = false;
  } else {
    printf("\nstart\n");
    doing = true;
  }
}

int main(void){
  printf("    C-c: start / stop\n");
  printf("    C-z: reset / stop\n");
  if(signal(SIGINT, toggle) == SIG_ERR){
    perror("signal");
    exit(EXIT_FAILURE);
  }

  if(signal(SIGTSTP, reset) == SIG_ERR){
    perror("signal");
    exit(EXIT_FAILURE);
  }

  while(1) {
    while(doing) {
      sleep(1);
      printf("%d\n", ++count);
    }
    pause();
  }
  exit(EXIT_SUCCESS);
}
