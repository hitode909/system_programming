#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<readline/readline.h>
#include<readline/history.h>

/* 2-7 */
int display_ProcessInfo(char *name, char *position) {
    printf("        I am %s at the %s.\n", name, position);
    printf("        My user %d\n", getuid());
    printf("        My ID is %d and the ID of my parent is %d\n", getpid(), getppid());
    return 1;
}

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
  display_ProcessInfo("child", "after fork call");
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
  display_ProcessInfo("parent", "after fork call");
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
  display_ProcessInfo("simple shell", "at the begining");
  inputLoop(&executeInputLine);
  exit(EXIT_SUCCESS);
}

/*
        I am simple shell at the at the begining.
        My user 502
        My ID is 26350 and the ID of my parent is 23897
PROMPT> ls
        I am parent at the after fork call.
        My user 502
        My ID is 26350 and the ID of my parent is 23897
        I am child at the after fork call.
        My user 502
        My ID is 26351 and the ID of my parent is 26350
1-1.c                   1-5.c                   2-2-2.c                 2-4.c                   Makefile
1-2-2.c                 1-6.c                   2-2.c                   2-5.c                   README
1-2.c                   1-7.c                   2-3-2.c                 2-6.c                   a.out
1-3.c                   2-1.c                   2-3.c                   2-7.c                   get_sample_code.rb
PROMPT> pwd
        I am parent at the after fork call.
        My user 502
        My ID is 26350 and the ID of my parent is 23897
        I am child at the after fork call.
        My user 502
        My ID is 26352 and the ID of my parent is 26350
/Users/fkd/co/system_programming

1. simple shell は fork における親か子か
親

2. キーボードから入力されたコマンドを実行しているのは fork における親か子か
子
 */
