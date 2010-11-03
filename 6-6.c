#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void err_quit(char *msg);

int main(int argc, char *argv[])
{
  DIR *dir;

  const char *sep = "/";
  char** options;
  options = malloc(sizeof(char*) * 100);
  char* dir_name;

  if(argc != 2) {
    puts("USAGE: 6-6 <パス名>");
    exit(EXIT_FAILURE);
  }

  for (dir_name = strtok(argv[1], sep); dir_name; dir_name = strtok(NULL, sep)) {
    if (argv[1] != dir_name) { /* 相対パスのとき，先頭-1を'/'にするとおかしくなる */
      *(dir_name-1) = '/';
    }
    printf("%s\n", argv[1]);

    if((dir = opendir(argv[1])) == NULL) {
      printf("mkdir %s\n", argv[1]);
      if(mkdir(argv[1], 0755)) {
        perror("mkdir");
        exit(EXIT_FAILURE);
      }
    } else {
      closedir(dir);
    }
  }

  exit(EXIT_SUCCESS);
}


/*
+R ./a.out /Users/fkd/fuba/fubauab
/Users
/Users/fkd
/Users/fkd/fuba
mkdir /Users/fkd/fuba
/Users/fkd/fuba/fubauab
mkdir /Users/fkd/fuba/fubauab
 */
