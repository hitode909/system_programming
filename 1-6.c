#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* util */

void printUsage() {
  fprintf(stderr, "Usage: medium01-2 command [option]\n");
}

int executeCommand(char *options[]) {
  char* command = options[0];
  printf("Child process : execute a new program %s.\n", command);
  return execv(command, options) != -1;
}

int pidIsChild(pid_t pid) {
  return pid == 0;
}

int pidIsFailed(pid_t pid) {
  return pid == -1;
}

int pidIsParent(pid_t pid) {
  return pid > 0;
}

int statusIsSuccess(int status) {
  return status == 0;
}

/* handlers */

void handleChild(int argc, char *argv[]) {
    // child = コマンド表示+実行
    if (argc <= 1) {
      printUsage();
      exit(EXIT_FAILURE);
    }

    int success = executeCommand(argv+1);
    if (!success) perror("execv");
    exit(success ? EXIT_SUCCESS : EXIT_FAILURE);
}

void handleFailed(int argc, char *argv[]) {
  // fork失敗したとき
  perror("fork");
  exit(EXIT_FAILURE);
}

void handleParent(int argc, char *argv[]) {
  int status;
  wait(&status);
  printf("Parent process : child process has just finished.\n");
  printf("status = %d\n", status);
  exit(statusIsSuccess(status) ? EXIT_SUCCESS : EXIT_FAILURE);
}

/* main */

int main(int argc, char *argv[]) {
  pid_t pid = fork();

  if (pidIsFailed(pid)) {
    handleFailed(argc, argv);
  }

  if (pidIsChild(pid)) {
    handleChild(argc, argv);
  }

  if (pidIsParent(pid)) {
    handleParent(argc, argv);
  }

  fprintf(stderr, "Something wrong.");
  exit(EXIT_FAILURE);
}
