
/*
 * uidからパスワードデータベースを調べてフルネームを表示する
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>

int main(void) {

    char *login;
    struct passwd *pentry;

    uid_t uid = getuid();

    printf("このプロセスを実行しているユーザのUID: %d\n", uid);

    /* loginのパスワードのエントリーを得る */
    if((pentry = getpwuid(uid)) == NULL) {
        perror("getpwuid");
        exit(EXIT_FAILURE);
    }
    /* パスワードのエントリーのうちGECOSフィールドを表示 */
    printf("フルネーム: %s\n", pentry->pw_gecos);

    exit(EXIT_SUCCESS);
}

