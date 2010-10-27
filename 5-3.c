#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  int i;
  printf("sys_nerr = %d\n", sys_nerr);
  for(i = 0; i < sys_nerr; i++) {
    printf("%d: %s\n", i, sys_errlist[i]);
  }
  exit(EXIT_SUCCESS);
}

/*
sys_nerr = 104
0: Undefined error: 0
1: Operation not permitted
2: No such file or directory
3: No such process
4: Interrupted system call
5: Input/output error

 */
