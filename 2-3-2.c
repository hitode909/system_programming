/* 標準入力からnice値を入力，設定 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int getd(){
    int to;
    char buffer[256];
    fgets(buffer, 256, stdin);
    sscanf(buffer, "%d",&to);
    return to;
}

int main(void) {
    int nice_value;

    printf("nice> ");
    nice_value = nice(getd());

    if (nice_value == -1) {
        perror("nice");
        exit(EXIT_FAILURE);
    }

    printf("nice value = %d\n", nice_value);

    exit(EXIT_SUCCESS);
}


/*
  高い値を設定すると上限に丸められる．低い値を設定するとエラーが発生する．
|ﾟﾟ| ./a.out
nice> 400
nice value = 19
(n´・・`)η ./a.out
nice> -400
nice: Operation not permitted
 */
