
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


/*
｜∩´・・`∩｜ sudo -u kyoyu ./a.out
実ユーザID: 503
有効ユーザID: 503
実グループID: 20
有効グループID: 20
┐(⊙⊙)┌ sudo -u kyoyu id
uid=503(kyoyu) gid=20(staff) groups=20(staff),98(_lpadmin),103(com.apple.sharepoint.group.3),102(com.apple.sharepoint.group.2)
(∩≧≦∩) ./a.out
実ユーザID: 502
有効ユーザID: 502
実グループID: 20
有効グループID: 20
(´・・`) ./a.out
実ユーザID: 502
有効ユーザID: 502
実グループID: 20
有効グループID: 20

ユーザIDとuidが対応，グループIDとgidが対応
周囲の人と比べると，ユーザーIDは変わるが，グループIDは変わらない．
 */
