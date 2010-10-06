
  /*
  * login名を得る
  */

  #include <stdio.h>
  #include <stdlib.h>
  #include <sys/types.h>
  #include <unistd.h>
  #include <pwd.h>

  int main(void) {

        char *login;
        struct passwd *pentry;

        /* login名を得る */
         if((login = getlogin()) == NULL) {
              perror("getlogin");
              exit(EXIT_FAILURE);
         }

         printf("このプロセスを実行しているユーザのログイン名: %s\n", login);

         /* loginのパスワードのエントリーを得る */
        if((pentry = getpwnam(login)) == NULL) {
              perror("getpwnam");
              exit(EXIT_FAILURE);
        }
        /* パスワードのエントリーのうちGECOSフィールドを表示 */
        printf("フルネーム: %s\n", pentry->pw_gecos);

        exit(EXIT_SUCCESS);
  }

