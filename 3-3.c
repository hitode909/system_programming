#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>

int main(void){

  int i;

  /* set signal handler */
  if(signal(SIGINT, SIG_IGN)==SIG_ERR){ /* SIG_IGN = ignore */
    perror("signal");
    exit(EXIT_FAILURE);
  }

  for(i=0;i<10;i++){
    printf("i=%d\n",i);
    sleep(1);
  }

  /* reset signal handler */
  if(signal(SIGINT, SIG_DFL)==SIG_ERR){ /* SIG_DEF = default */
    perror("signal");
    exit(EXIT_FAILURE);
  }

  for(;;i++){
    printf("i=%d\n",i);
    sleep(1);
  }

  return 0;
}

/*
i = 10までは，Ctrl-cしても無視される．i = 10を過ぎると終了できる．

i=4
^Ci=5
^C^C^C^C^C^C^C^C^C^C^C^C^C^C^C^C^C^C^C^C^C^C^C^C^C^C^Ci=6
i=7
i=8
^C^C^Ci=9
i=10
^C
 */
