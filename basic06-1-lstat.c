
/*
 * lstat の利用例
 */

#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    struct stat buf;
    mode_t mode;
    char type[80];

    if(argc != 2) {
	puts("USAGE: basic06-1-lstat FILENAME");
	exit(EXIT_FAILURE);
    }

    if((lstat(argv[1], &buf)) 
  