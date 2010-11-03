
/*
 * cat(1)の機能をメモリマップを用いて実装
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
    char *src;
    struct stat statbuf;

    /* ソース・ファイルを開く */
    if(argc != 2) {
        puts("USAGE: basic06-3-mmcat <ファイル>");
        exit(EXIT_FAILURE);
    }
    if((fd = open(argv[1], O_RDONLY)) < 0)
         err_quit("open");

    /* mmapするためにファイルの長さを得る */
    fstat(fd, &statbuf);

    /* 入力ファイルをマップする */
    if((src = mmap(NULL, statbuf.st_size, PROT_READ,
		   MAP_SHARED, fd, 0)) == MAP_FAILED)
        err_quit("mmap");

    /* 書き出しをする */
    write(STDOUT_FILENO, src, statbuf.st_size);

    /* クリーンアップする */
    close(fd);
    munmap(src, statbuf.st_size);

    exit(0);
}

void err_quit(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

      