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

void print_lstat(char* filename) {
  struct stat buf;
  mode_t mode;
  char type[80];

  if((lstat(filename, &buf)) < 0) {
    perror("lstat");
    exit(EXIT_FAILURE);
  }
  mode = buf.st_mode;
  printf("    FILE: %s\n", filename);
  printf("   INODE: %lld\n", buf.st_ino);
  printf("  DEVICE: %d,%d\n", major(buf.st_dev),
         minor(buf.st_dev));
  printf("    MODE: %#o\n", mode & ~(S_IFMT));
  printf("   LINKS: %d\n", buf.st_nlink);
  printf("     UID: %d\n", buf.st_uid);
  printf("     GID: %d\n", buf.st_gid);
  if(S_ISLNK(mode))
    strcpy(type, "シンボリックリンク");
  else if(S_ISREG(mode))
    strcpy(type, "通常ファイル");
  else if(S_ISDIR(mode))
    strcpy(type, "ディレクトリ");
  else if(S_ISCHR(mode))
    strcpy(type, "キャラクタデバイス");
  else if(S_ISBLK(mode))
    strcpy(type, "ブロックデバイス");
  else if(S_ISFIFO(mode))
    strcpy(type, "FIFO");
  else if(S_ISSOCK(mode))
    strcpy(type, "ソケット");
  else
    strcpy(type, "知らないタイプ");
  printf("    TYPE: %s\n", type);
  printf("    SIZE: %lld\n", buf.st_size);
  printf("BLK SIZE: %d\n", buf.st_blksize);
  printf("  BLOCKS: %d\n", (int)buf.st_blocks);
  printf("ACCESSED: %s", ctime(&buf.st_atime));
  printf("MODIFIED: %s", ctime(&buf.st_mtime));
  printf(" CHANGED: %s", ctime(&buf.st_ctime));

}

int main(int argc, char *argv[])
{
  DIR *dir;
  struct dirent *mydirent;

  if(argc != 2) {
    puts("USAGE: 6-5 <パス名>");
    exit(EXIT_FAILURE);
  }

  if((dir = opendir(argv[1])) == NULL)
    err_quit("opendir");
  while((mydirent = readdir(dir)) != NULL) {
    printf("------------\n");
    print_lstat(mydirent->d_name);
  }

  closedir(dir);
  exit(EXIT_SUCCESS);
}

void err_quit(char *msg)
{
  perror(msg);
  exit(EXIT_FAILURE);
}
