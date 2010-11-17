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

/* handlers */

/* child -> parent input.txtの内容をパイプで送る */
void handleChild(int pipe_read, int pipe_write) {
  int fd_in;
  char buffer[BUFSIZE];
  int len;

  close(pipe_read);
  /* ファイル開く */
  fd_in = open(FILENAME, O_RDONLY);
  if(fd_in<0){
    perror("open");
    exit(EXIT_FAILURE);
  }

  /* ファイル読む */
  if((len = read(fd_in, buffer, sizeof(buffer)))<0){
    perror("read");
  }
  close(fd_in);

  /* ファイルの内容書く */
  write(pipe_write, buffer, len);

  close(pipe_write);
  exit(EXIT_SUCCESS);
}

/* childから受信した内容を表示 */
void handleParent(int pipe_read, int pipe_write) {
  char buffer[BUFSIZE];
  int len;

  close(pipe_write);

  /* childが終わるのを待つ */
  waitOrExit();

  /* パイプ読む */
  if((len=read(pipe_read, buffer, sizeof(buffer)))<0){
    perror("read");
  }

  /* stdoutに出力 */
  write(stdout->_file, buffer, len);

  close(pipe_read);

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
