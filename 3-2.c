/*
  m2_receiveは起動すると，PIDと，i=0を表示して待つ．
  m2_receiveはSIGTERMを受け取ると，終了する．
  m2_sendは，起動すると標準入力からPIDを受け取り，SIGTERMを送る．
 */

/*
pid: 28049
i=0
zsh: terminated  ./m2_receive
 */

/* m2_receive

#include <stdio.h>
#include <unistd.h>

int main(void){
    int i;
    printf("pid: %d\n", getpid());

    for(i=0;;i++){
        printf("i=%d\n",i);
        pause();
    }

    return 0;
}

*/

/*
pid? 28049
 */

/* m2_send
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define LINESIZE 256

int main(void){
  pid_t pid;
  char line[LINESIZE];

  printf("pid? ");
  fgets(line,sizeof(line),stdin);
  sscanf(line,"%d\n",&pid);

  if(kill(pid, SIGTERM)<0){
    perror("kill");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}

*/
