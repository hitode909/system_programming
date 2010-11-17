
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define BUFSIZE PIPE_BUF
	/* パイプに一度に書き込めるバッファのサイズ．このサイズまでのデータならば，write(),read()システムコールで読み書き中に他のプロセスに割り込まれることはない */

int main(void){
	int fd[2];	/* パイプに接続される2つのファイルディスクリプタ */
	char buf_write[BUFSIZE]="input to pipe: basic08-2\n";	/* 書き込み用バッファ */
	char buf_read[BUFSIZE];	/* 読み込みようバッファ */
	int len;	/* 読み書きしたバイト数 */

	/* パイプのオープン．
	 * fd[1]に，書き込み側のファイルディスクリプタ
	 * fd[0]に，読み込み側のファイルディスクリプタが返る
	 */
	if(pipe(fd)<0){
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	printf("pipe's descriptors are %d & %d\n", fd[0], fd[1]);

	/* パイプ入力のファイルディスクリプタに何かを出力する */
	/* 成功すれば，パイプ出力のファイルディスクリプタに出力内容が入力されるはず */
	//strcpy(buf,"basic08-2.c");
	write(fd[1], buf_write, strlen(buf_write));

	/* パイプ出力のファイルディスクリプタへの入力内容を読み込み標準出力に出力する */
	if((len=read(fd[0], buf_read, sizeof(buf_read)))<0){
		perror("read");
	}
	write(1, buf_read, len);

	/* パイプのクローズ */
	close(fd[0]);
	close(fd[1]);

	exit(EXIT_SUCCESS);
}

      