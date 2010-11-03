
/*
 * ファイルを指定の長さに短縮する
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    long len;

    if(argc != 3)
	exit(EXIT_FAILURE);
    len = strtol(argv[2], NULL, 10);

    if(truncate(argv[1], len)) {
	perror("truncate");
	exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

      