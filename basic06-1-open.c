
/*
 * ファイルのopen/close
 */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    int fd;
    char path[] = "hello";

    if((fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0644)) 
  