#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>

void disp(int _) {
  static int i = 0;
  printf("i=%d\n", ++i);
}

int main(void){
  if(signal( SIGINT, disp) == SIG_ERR){
    perror("signal");
    exit(EXIT_FAILURE);
  }

  while(1) {
    pause();
  }
  exit(EXIT_SUCCESS);
}

/*

^Ci=1
^Ci=2
^Ci=3
^Ci=4
^Ci=5
^Ci=6
^\zsh: quit       ./a.out
 */
