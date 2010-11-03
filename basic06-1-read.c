
/*
 * read および write システムコール
 */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    int fdsrc, fdnull, fdtmp, numbytes;
    char buf[10];

    /* このソースファイルと /dev/null と /tmp/foo.bar をオープンする */
    if((fdsrc = open("basic06-1-read.c", O_RDONLY, 0644)) 
  