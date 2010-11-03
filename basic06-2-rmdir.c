
/*
 * rmdirによるディレクトリの削除
 */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    if(rmdir(argv[1])) {
	perror("rmdir");
	exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}

      