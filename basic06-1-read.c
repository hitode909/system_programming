
/*
 * read および write システムコール
 */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    int fdsrc, fdnull, fdtmp, numbytes;
    char buf[10];

    /* このソースファイルと /dev/null と /tmp/foo.bar をオープンする */
    if((fdsrc = open("basic06-1-read.c", O_RDONLY, 0644)) < 0) {
	perror("open basic06-1-read.c");
	exit(EXIT_FAILURE);
    }
    if((fdnull = open("/dev/null", O_WRONLY)) < 0) {
	perror("open /dev/null");
	close(fdsrc); /* これをオープンしたのでクローズする */
	exit(EXIT_FAILURE);
    }
    if((fdtmp = open("/tmp/foo.bar", O_CREAT|O_TRUNC|O_WRONLY, 0644)) < 0) {
	perror("open /tmp/foo.bar");
	close(fdsrc); /* ここで両ファイルを閉じなければならない */
	close(fdnull);
	exit(EXIT_FAILURE);
    }

    /* 10バイト読み出したら10バイト書き込む */
    while((numbytes = read(fdsrc, buf, 10)) != 0) {
	if(write(fdnull, buf, 10) < 0) /* nullデバイス */
	    perror("write /dev/null");
	if(write(fdtmp, buf, numbytes) < 0) /* /tmpにある一時ファイル */
	    perror("write /tmp/foo.bar");
    }

    /* 使ったファイルを閉じて終了する */
    close(fdsrc);
    close(fdnull);
    close(fdtmp);

    exit(EXIT_SUCCESS);
}

      