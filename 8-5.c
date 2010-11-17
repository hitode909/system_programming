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

int min(int a, int b) {
  return a > b ? b : a;
}

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

	/* fifo開く */
        int fifo = open(name, O_RDONLY);
        if (fifo < 0) {
          perror("open");
          exit(EXIT_FAILURE);
        }

        /* fifo読んで表示 */
        char buffer[BUFSIZE];
        int len = 1;
        while ((len = read(fifo, buffer, sizeof(buffer))) > 0) {
          buffer[min(BUFSIZE - 1, len)] = '\0';
          write(stdout->_file, buffer, len);
        }
        close(fifo);

	exit(EXIT_SUCCESS);
}
