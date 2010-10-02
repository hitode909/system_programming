#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>

void printUsage() {
  fprintf(stderr, "Usage: medium01-1 command [option]\n");
}

int executeCommand(char *options[]) {
  char* command = options[0];
  return execv(command, options) != -1;
}

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    printUsage();
    exit(EXIT_FAILURE);
  }

  int success = executeCommand(argv+1);
  if (!success) perror("execv");
  exit(success ? EXIT_SUCCESS : EXIT_FAILURE);
}
