#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>

#define PIPE_INDEX_READ  0
#define PIPE_INDEX_WRITE 1
#define FILENAME "input.txt"
#define BUFSIZE PIPE_BUF

/* util */

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

void handleFailed() {
  // fork失敗したとき
  perror("fork");
  exit(EXIT_FAILURE);
}

void waitOrExit() {
  int status;
  wait(&status);
  if (!statusIsSuccess(status)) {
    fprintf(stderr, "status = %d\n", status);
    exit(EXIT_FAILURE);
  }
  return;
}

int min(int a, int b) {
  return a > b ? b : a;
}

/* handlers */

/* stdoutをpipe_writeとつないで，ls -lした結果をパイプで送る */
void handleChild(int pipe_read, int pipe_write) {

  close(pipe_read);
  close(stdout->_file);
  dup2(pipe_write,stdout->_file);

  system("ls -l");

  close(pipe_write);
  close(pipe_read);
  exit(EXIT_SUCCESS);
}

/* childから受信した内容の行数を表示 */
void handleParent(int pipe_read, int pipe_write) {
  char buffer[BUFSIZE];
  int len;
  int newline_count;
  int i;

  close(pipe_write);

  /* childが終わるのを待つ */
  waitOrExit();

  /* パイプ読んで改行を数える */
  newline_count = 0;
  while ((len = read(pipe_read, buffer, sizeof(buffer))) > 0) {
    write(stdout->_file, buffer, len);
    for(i = 0; i < len; i++) {
      if (buffer[i] == '\n') newline_count++;
    }
  }

  close(pipe_read);
  printf("total: %d\n", newline_count);
}

/* main */

int main(int argc, char *argv[]) {
  int fd_pipe[2];
  if(pipe(fd_pipe)<0){
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  pid_t pid = fork();

  if (pidIsFailed(pid)) {
    handleFailed();
  }

  if (pidIsChild(pid)) {
    handleChild(fd_pipe[PIPE_INDEX_READ], fd_pipe[PIPE_INDEX_WRITE]);
  }

  if (pidIsParent(pid)) {
    handleParent(fd_pipe[PIPE_INDEX_READ], fd_pipe[PIPE_INDEX_WRITE]);
  }

  exit(EXIT_FAILURE);
}
