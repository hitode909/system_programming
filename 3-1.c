#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void){

  int i;

  for(i=0;;i++){
    printf("i=%d\n",i);
    sleep(1);
  }

  return 0;
}

/*
SIGTSTP: Ctrl+z
suspendする．

SIGCONT: fgコマンド
SIGSTOPでsuspendされたプロセスを再開する

SIGQUIT: Ctrl+\
131で終了 echo $?して確認

SIGINT: Ctrl+c
130で終了 echo $?して確認

SIGSTOP: Ctrl+s
一時停止する．なにかキーを押すと再開する
*/
