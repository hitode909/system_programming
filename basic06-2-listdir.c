
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

    if(argc != 2) {
	puts("USAGE: basic06-2-listdir <パス名>");
	exit(EXIT_FAILURE);
    }

    if((dir = opendir(argv[1])) == NULL)
	err_quit("opendir");
    while((mydirent = readdir(dir)) != NULL)
      printf("%3lld : %s\n", mydirent->d_ino, mydirent->d_name);

    closedir(dir);
    exit(EXIT_SUCCESS);
}

void err_quit(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

/*
2664269 : .
1363979 : ..
2664270 : .git
3829185 : .gitignore
2664332 : 1-1.c
2667677 : 1-2-2.c
2667787 : 1-2.c
2664334 : 1-3.c
2664335 : 1-5.c
 */
