#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

void mperror(const char *s, int errnum) {
  fprintf(stderr, "%s: %s\n", s, strerror(errnum));
}

int main(void){
  char *argv[] = {"/bin/lsls", NULL};

  if(execve("/bin/lsls", argv, NULL) == -1) {
    mperror("execve", errno);
    exit(EXIT_FAILURE);
  }
  exit(EXIT_SUCCESS);
}

