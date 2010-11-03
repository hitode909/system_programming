
/*
 * lseek の利用
 */

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    char ftmp[] = "tmpXXXXXX";
    char buf[10];
    int i, infd, outfd;

    /* 入力ファイルを開く */
    if((infd = open("devices.txt", O_RDONLY)) < 0) {
	perror("open devices.txt");
	exit(EXIT_FAILURE);
    }
    /* 出力用の一時ファイルを作成する */
    if((outfd = mkstemp(ftmp)) < 0) {
	perror("mkstemp");
	exit(EXIT_FAILURE);
    }
    printf("出力ファイルは%s\n", ftmp);

    /* ファイルに初期位置を設定する */
    lseek(infd, 100, SEEK_SET);
    /*
     * 100バイトごとに最初の10バイトを
     * 出力ファイルにコピーする
     */
    for(i = 0; i < 10; ++i) {
	read(infd, buf, 10);
	write(outfd, buf, 10);
	lseek(infd, 90, SEEK_CUR); /* 90バイト先へ飛ぶ */
    }

    close(infd);
    close(outfd);
    exit(EXIT_SUCCESS);
}

      