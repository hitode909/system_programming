#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

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

/* handlers */

// 子供 = pidを表示して10秒待って終了
void handleChild() {
    printf("I am the child. I will sleep 10 seconds.\n");
    sleep(10);
    exit(EXIT_SUCCESS);
}

void handleFailed() {
    perror("fork");
    exit(EXIT_FAILURE);
}

// 親 = 子供を待って終了
void handleParent(int pid) {
    printf("I am the parent. My child id is %d.\n", pid);
    int status;
    waitpid(pid, &status, 0);
    exit(EXIT_SUCCESS);
}

/* main */
int main(void) {
    pid_t pid = fork();

    if (pidIsFailed(pid)) {
        handleFailed();
    }

    if (pidIsChild(pid)) {
        handleChild();
    }

    if (pidIsParent(pid)) {
        handleParent(pid);
    }

    fprintf(stderr, "Something wrong.");
    exit(EXIT_FAILURE);

}

/*
｜´・・`｜ ./a.out
I am the parent. My child id is 25579.
I am the child. I will sleep 10 seconds.

┐｜＾＾｜┌ ps l
  UID   PID  PPID CPU PRI NI      VSZ    RSS WCHAN  STAT   TT       TIME COMMAND
  502 23897 23896   0  31  0    76356   2172 -      S    s003    0:00.88 zsh
  502 25578 23897   0  31  0    75328    296 -      S+   s003    0:00.00 ./a.out
  502 25579 25578   0  31  0    75328    144 -      S+   s003    0:00.00 ./a.out
 */
