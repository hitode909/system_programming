#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<termios.h>
#include<unistd.h>

#define position int
#define cursor int
#define CTRLD 0x04
#define ESC 0x1b
#define CURSOR_I 'I'
#define CURSOR_X 'X'
#define LINE_WIDTH 40

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

    tio.c_lflag &= ~(ICANON|IEXTEN|ECHO|ECHOE|ECHOK|ECHONL);

    tio.c_cc[VMIN] = 1;	 /* 受信するべき文字の最小数 */
    tio.c_cc[VTIME] = 0;	/* バーストで短期のデータ伝送をタイムアウトするために使用する0.10秒単位のタイマ */

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

cursor toggle(cursor current) {
  if (current == CURSOR_I) {
    return CURSOR_X;
  } else {
    return CURSOR_I;
  }
}

position left(position current) {
  current--;
  if (current < 0) {
    current = LINE_WIDTH - 1;
  }
  return current;
}

position right(position current) {
  current++;
  if (current >= LINE_WIDTH) {
    current = 0;
  }
  return current;
}

int main(void)
{
  unsigned char	c;
  StdinRaw(1);
  setbuf(stdout, NULL);

  int pos = 0;
  int new_pos = 0;
  cursor status = CURSOR_X;

  printf("%c", status);
  while (1) {
    c = getchar();
    switch(c) {
    case 'h':
      new_pos = left(pos);
      break;
    case 'l':
      new_pos = right(pos);
      break;
    case ESC:
      status = toggle(status);
      break;
    case CTRLD:
      goto _break;
    default:
      continue;
    }

    printf("\b");
    while (new_pos < pos) {
      printf(" \b\b");
      pos--;
    }
    while (new_pos > pos) {
      printf(" ");
      pos++;
    }
    printf("%c", status);
    fflush(stdout);

  }
_break:

  StdinRaw(0);

  return(EXIT_SUCCESS);
}
