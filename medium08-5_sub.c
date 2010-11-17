
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#define BUFSIZE 256

void clear_buf(char *, int);

int main(int argc, char *argv[]){
	mode_t mode=0666;	/* 作成するFIFOのパーミッション */
	char *name;	/* FIFOの名前 */

	/* コマンドライン引数のチェック */
	/* 第一引数で与えられた名前のFIFOを作成する */
	if(argc != 2){
		puts("USAGE: newfifo <name>");
		exit(EXIT_FAILURE);
	}
	name = argv[1];

	/* FIFOの作成 */
	if((mkfifo(name, mode)<0)){
		if(errno!=EEXIST){
			perror("mkffio");
			exit(EXIT_FAILURE);
		}
	}

	/* 別のターミナルからpingコマンドを実行し始めるまでしばらく待つ */
	sleep(5);

	/* FIFOからデータを読み込む処理を記述 */

	exit(EXIT_SUCCESS);
}

      