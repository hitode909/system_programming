#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<readline/readline.h>
#include<readline/history.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>


/* util */

void executeTruncate(char* filename, int size) {
  truncate(filename, size);
}

void executeLseekcat(char* filename, int from, int size) {
  char buf[256];
  int fd;

  if((fd = open(filename, O_RDONLY)) < 0) {
    perror("open");
    exit(EXIT_FAILURE);
  }

  lseek(fd, from, SEEK_SET);
  read(fd, buf, size);
  printf("%s\n", buf);
  close(fd);
}

/* input loop, call callback */
void inputLoop(void callback(char* line)) {
  char *line = NULL;

  while (1) {
    line = readline("PROMPT> ");

    if (line == NULL) {
      free(line);
      break;
    }

    if (strlen(line) == 0) {
      free(line);
      continue;
    }
    add_history(line);
    callback(line);
    free(line);
  }
  return;
}


void executeInputLine(char* line) {
  printf("%s\n", line);
  char filename[256];
  int from, size;

  if (strncmp(line, "truncate", sizeof("truncate")-1) == 0) {
    sscanf(line, "truncate %s %d", filename, &size);
    if (strlen(filename) > 0 && size >= 0) {
      executeTruncate(filename, size);
    } else {
      printf("truncate (filename) (size)\n");
    }
  }
  else if (strncmp(line, "lseekcat", sizeof("lseekcat")-1) == 0) {
    sscanf(line, "lseekcat %s %d %d", filename, &from, &size);
    if (strlen(filename) > 0 && from >= 0 && size < 256 && size >= 0) {
      executeLseekcat(filename, from, size);
    } else {
      printf("lseekcat (filename) (from>=0) (size<256)\n");
    }
  }
}

/* main */

int main(int argc, char *argv[]) {
  inputLoop(&executeInputLine);
  exit(EXIT_SUCCESS);
}
