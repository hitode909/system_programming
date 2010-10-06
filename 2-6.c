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

// 子供 = いろいろ表示
void handleChild() {
    printf("I am the child.\n");
    printf("        pid of child = %d\n", getpid());
    printf("        ppid of child = %d\n", getppid());
    exit(EXIT_SUCCESS);
}

void handleFailed() {
    perror("fork");
    exit(EXIT_FAILURE);
}

// 親 = いろいろ表示
void handleParent(int pid) {
    printf("I am the parent. My child id is %d.\n", pid);
    printf("        pid of parent = %d\n", getpid());
    printf("        ppid of parent = %d\n", getppid());

    int status;
    waitpid(pid, &status, 0);

    printf("process ID of\n");
    printf("        the child is %d\n", pid);
    printf("        the parent is %d\n", getpid());
    printf("        the shell is %d\n", getppid());

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
I am the parent. My child id is 25897.
        pid of parent = 25896
        ppid of parent = 23897
I am the child.
        pid of child = 25897
        ppid of child = 25896
process ID of
        the child is 25897
        the parent is 25896
        the shell is 23897
 */
