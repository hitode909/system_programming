#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<readline/readline.h>
#include<readline/history.h>

/* util */

int executeCommand(char *options[]) {
  char* command = options[0];
  return execvp(command, options) != -1;
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

// input:  "ls -l ~"
// return: ["ls", "-l", "~"]
char** getOptionsFromLine(char* line) {
  const char *sep = " ";
  char** options;
  options = malloc(sizeof(char*) * 100);
  char* word;
  int length = 0;

  for (word = strtok(line, sep); word; word = strtok(NULL, sep)) {
    options[length++] = word;
  }
  options[length++] = NULL;

  return options;
}

void freeOptions(char** options) {
  free(options);
}

/* handlers */

void handleChild(char *line) {
  char** options = getOptionsFromLine(line);
  int success = executeCommand(options);
  freeOptions(options);
  if (!success) perror("execv");
  exit(success ? EXIT_SUCCESS : EXIT_FAILURE);
}

void handleFailed(char *line) {
  perror("fork");
  exit(EXIT_FAILURE);
}

void handleParent(char *line) {
  int status;
  wait(&status);
  return;
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

// fork manager
void executeInputLine(char* line) {
  pid_t pid = fork();

  if (pidIsFailed(pid)) {
    return handleFailed(line);
  }

  if (pidIsChild(pid)) {
    return handleChild(line);
  }

  if (pidIsParent(pid)) {
    return handleParent(line);
  }

  fprintf(stderr, "Something wrong.");
  exit(EXIT_FAILURE);
}

/* main */

int main(int argc, char *argv[]) {
  inputLoop(&executeInputLine);
  exit(EXIT_SUCCESS);
}
