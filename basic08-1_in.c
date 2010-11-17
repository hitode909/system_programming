
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#define FILENAME "input.txt"	/* ファイル名 */
#define BUFSIZE 10

int main(void){
	int fdin;	/* 入力用ファイルディスクリプタ */
	char buf[BUFSIZE];	/* 入力内容を保持する配列 */
	int len;	/* ファイルディスクリプタから読み込めたサイズ */

	/* ファイルinput.txtを読み込み専用でオープンし，
	 * ファイルディスクリプタを割り当てる */
	fdin = open(FILENAME, O_RDONLY);
	if(fdin<0){
		perror("open");
		exit(EXIT_FAILURE);
	}

	printf("file discripter %d opened!\n", fdin);

	/* ファイルinput.txtの内容を読み込み標準出力に出力 */
	while((len=read(fdin, buf, sizeof(buf)-1))>0){
		write(1, buf, len);	/* 1は標準出力のファイルディスクリプタ */
	}

	/* ファイルディスクリプタのクローズ */
	close(fdin);

	exit(EXIT_SUCCESS);
}

/* bufから1(標準出力にwriteする) */
