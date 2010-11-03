
/*
 * ファイルのopen/close
 */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    int fd;
    char path[] = "hello";

    if((fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0644)) < 0) {
	perror("open");
	exit(EXIT_FAILURE);
    } else
	printf("ファイル %s を開いた\n", path);
    if(close(fd) < 0) {
	perror("close");
	exit(EXIT_FAILURE);
    } else
	printf("ファイル %s を閉じた\n", path);
    exit(EXIT_SUCCESS);
}

      