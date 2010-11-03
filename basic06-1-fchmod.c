

/*
 * ファイルを作成して fchmod でモードを変更する
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(void)
{
    mode_t mode = 0755;
    int fd;

    /* ファイルを作成 */
    if((fd = open("empty.file", O_CREAT, 0644)) < 0) {
	perror("open");
	exit(EXIT_FAILURE);
    }
    /* lsでファイルをリストする */
    system("ls -l empty.file");
    /* そのファイルのパーミッションを変更する */
    if((fchmod(fd, mode)) < 0) {
	perror("fchmod");
	exit(EXIT_FAILURE);
    }
    /* もう1度ファイルをlsする */
    system("ls -l empty.file");
    exit(EXIT_SUCCESS);
}

      