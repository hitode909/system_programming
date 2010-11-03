
/*
 * lseek の利用
 */

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    char ftmp[] = "tmpXXXXXX";
    char buf[10];
    int i, infd, outfd;

    /* 入力ファイルを開く */
    if((infd = open("devices.txt", O_RDONLY)) 
  