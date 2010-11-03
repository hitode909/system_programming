
/*
 * メモリマップファイルの作成
 */

#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

void err_quit(char *msg);

int main(int argc, char *argv[])
{
    int fd;
    void *map;
    struct stat statbuf;

    /* マップしたいファイルを開く */
    if(argc != 2) {
        puts("USAGE: basic06-3-mkmap <ファイル>");
        exit(EXIT_FAILURE);
    }
    if((fd = open(argv[1], O_RDONLY)) < 0)
	err_quit("open");

    /* mmapのためにファイル長を得る */
    fstat(fd, &statbuf);

    /* 入力ファイルをマップする */
    if((map = mmap(NULL, statbuf.st_size, PROT_READ,
		   MAP_SHARED, fd, 0)) == MAP_FAILED)
        err_quit("mmap");
    printf("%pにマップが作成された\n", &map);

    /* ファイルを閉じてマップをやめる */
    close(fd);
    munmap(map, statbuf.st_size);
    exit(EXIT_SUCCESS);
}

void err_quit(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

      