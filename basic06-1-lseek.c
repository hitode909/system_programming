
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
    if((infd = open("rfc959.txt", O_RDONLY)) < 0) {
	perror("open rfc959.txt");
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

/*
  10バイト表示して90バイト飛ぶ，を10回繰り返す．

+R ./a.out
出力ファイルはtmp8T9qnR
+R cat tmp8T9qnR
                  J.es RFC: 76ER PROTOCOsfer
   Prands are i SMNT (StrD
      (Pe previouscomputer
 %
 */
