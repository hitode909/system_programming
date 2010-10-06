
  /*
  * UIDとGIDの出力
  */
  #include <stdio.h>
  #include <unistd.h>
  #include <stdlib.h>

  int main(void){
      printf("実ユーザID: %d\n", getuid());
      printf("有効ユーザID: %d\n", geteuid());
      printf("実グループID: %d\n", getgid());
      printf("有効グループID: %d\n", getegid());
      exit(EXIT_SUCCESS);
  }
        