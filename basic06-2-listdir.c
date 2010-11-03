
/*
 * ディレクトリ・ファイルを読み出す
 */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

void err_quit(char *msg);

int main(int argc, char *argv[])
{
    DIR *dir;
    struct dirent *mydirent;
    int i = 1;

    if(argc != 2) {
	puts("USAGE: basic06-2-listdir <パス名>");
	exit(EXIT_FAILURE);
    }

    if((dir = opendir(argv[1])) == NULL)
	err_quit("opendir");
    while((mydirent = readdir(dir)) != NULL)
	printf("%3d : %s\n", i++, mydirent->d_name);

    closedir(dir);
    exit(EXIT_SUCCESS);
}

void err_quit(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

      