#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<termios.h>
#include<unistd.h>
#include <signal.h>

int StdinRaw(int flag)
{
  static struct termios	tio_save;
  struct termios	tio;

  if (flag == 1){
    if (tcgetattr(0, &tio) == -1) {
      perror("tcgetattr");
      return(-1);
    }
    tio_save = tio; /* store data */

    tio.c_iflag &= ~(BRKINT|ISTRIP|IXON);
    /*
      「入力モード」
      ブレークにシグナルを送らない
      入力文字を 7 ビットにストリップしない
      START/STOP 出力制御を不可能にする
    */

    tio.c_lflag &= ~(ICANON|IEXTEN|ECHO|ECHOE|ECHOK|ECHONL);
    /*
      「ローカルモード」
      標準的な入力 (ERASEおよびKILL処理)を不可能にする
      VEOLZ,VSWTCH,VREPRINT,VDISCARD,VDSUSP,VWERASE,VLNEXT特殊制御文字を無効にする
      入力されたすべての文字を表示しない
      ERASE文字をバックスペース-空白文字-バックスペースの文字列として表示しない
      KILL文字の後のNLを表示しない
      NLをエコーしない
    */

    tio.c_cc[VMIN] = 0;	 /* 受信するべき文字の最小数 */
    tio.c_cc[VTIME] = 10;	/* バーストで短期のデータ伝送をタイムアウトするために使用する0.10秒単位のタイマ */

    if (tcsetattr(0, TCSANOW, &tio) == -1){
      perror("tcsetattr");
      return(-1);
    }
    return(0);
  }
  else{
    if(tcsetattr(0, TCSANOW, &tio_save) == -1){
      perror("tcsetattr");
      return(-1);
    }
    return(0);
  }
}


int main(void)
{
  int c;

  int i;
  for (i = 10; i > 0; i--) {
    printf("%d> ", i);
    StdinRaw(1);
    setbuf(stdout, NULL);
    c = getchar();
    StdinRaw(0);
    if (c != EOF) {
      i = 11;
    }
    if (i == 0 && c == EOF) {
      break;
    }
  }
  StdinRaw(0);

  return(EXIT_SUCCESS);
}
