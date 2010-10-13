#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define LINESIZE 256

int main(void){
  pid_t pid;
  char line[LINESIZE];

  /* input pid */
  printf("pid? ");
  fgets(line,sizeof(line),stdin);
  sscanf(line,"%d\n",&pid);

  /* send signal */
  if(kill(pid, SIGTERM)<0){
    perror("kill");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}

