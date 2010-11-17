
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#define FILENAME "output.txt"	/* ファイル名 */
#define BUFSIZE 10

int main(void){
	int fdout;	/* 出用ファイルディスクリプタ */
	char buf[BUFSIZE];	/* 入力内容を保持する配列 */
	int len;	/* ファイルディスクリプタから読み込めたサイズ */

	/* ファイルoutput.txtを書き込み専用，およびファイルが存在しない場合は作成する指定でオープンし，
	 * ファイルディスクリプタを割り当てる */
	fdout = open(FILENAME, O_WRONLY|O_CREAT|O_TRUNC);
	if(fdout<0){
		perror("open");
		exit(EXIT_FAILURE);
	}

	printf("file discripter %d opened!\n"
			"input text:\n"
			, fdout);

	/* 標準入力から読み込みファイルoutput.txtに出力 */
	while((len=read(0, buf, sizeof(buf)))>0){
		/* 0は標準入力のファイルディスクリプタ */
		write(fdout, buf, len);
	}

	/* ファイルディスクリプタのクローズ */
	close(fdout);

	exit(EXIT_SUCCESS);
}

      