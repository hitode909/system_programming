
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
        puts("USAGE: basic06-3-mmcat ");
        exit(EXIT_FAILURE);
    }
    if((fd = open(argv[1], O_RDONLY)) 
  