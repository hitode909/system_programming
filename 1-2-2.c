/*
 * execveを使ってchmod +xする．dummy.txtが必要．
 */


/* chmod */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void){
    char *argv[] = {"/bin/chmod", "+x", "dummy.txt"};

    if(execve("/bin/chmod", argv, NULL) == -1) {
        perror("execve");
        exit(EXIT_FAILURE);
    }
    puts("ここに来るはずがない");
    exit(EXIT_SUCCESS);
}


/*
｜n´`｜η touch dummy.txt
(∩`・・´∩) ls -l dummy.txt
-rw-r--r--  1 fkd  staff  0 Oct  6 13:51 dummy.txt
╰|´・・` | ./a.out
(｢◕◕)｢ ls -l dummy.txt
-rwxr-xr-x  1 fkd  staff  0 Oct  6 13:51 dummy.txt
 */
