
/*
 * getcwd を用いて現在の作業ディレクトリを表示
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define BUFSZ 10

int main(void)
{
    char *statbuf = malloc(BUFSZ);
    char *nullbuf = NULL;
    int i = 1;

    printf("実行例1:\n");
    /* 静的にバッファを割り当てる */
    while((getcwd(statbuf, i * BUFSZ)) == NULL) {
	++i;
	statbuf = realloc(statbuf, i * BUFSZ);
	printf("%d 回目: realloc呼出 (バッファサイズ %d)\n", i - 1, i * BUFSZ);
    }
    free(statbuf);
    printf("現在のディレクトリは%s\n", statbuf);

    printf("実行例2:\n");
    /* getcwdにメモリを割当てさせる */
    printf("現在のディレクトリは%s\n", getcwd(nullbuf, 0));
    /* メモリリークを防ぐためにnullbufを開放しなければならない */
    free(nullbuf);

    exit(EXIT_SUCCESS);
}

      