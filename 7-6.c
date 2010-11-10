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

enum operator {UNDEF, ADD, SUB, MULTIPLE, DIVIDE};

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

int parse_num(int a, int b) {
  int bi = b - '0';
  if (a > 0) {
    return a * 10 + bi;
  } else {
    return bi;
  }
}

int process(int sum, int cur, enum operator op) {
  switch (op) {
  case ADD:
    return sum + cur;
  case SUB:
    return sum - cur;
  case MULTIPLE:
    return sum * cur;
  case DIVIDE:
    return sum / cur;
  case UNDEF:
    return sum;
  }
  return sum;
}

char operator_to_s(enum operator op) {
  switch (op) {
  case ADD:
    return '+';
  case SUB:
    return '-';
  case MULTIPLE:
    return '*';
  case DIVIDE:
    return '/';
  case UNDEF:
    return ' ';
  }
  return ' ';
}

void print_status(enum operator op, int cur, int sum) {
  printf("%cop:%c cur:%d sum:%d", 0x0d, operator_to_s(op), cur, sum);
}

int main(void)
{
  unsigned char	c;
  StdinRaw(1);
  setbuf(stdout, NULL);

  int sum = 0;
  int cur = 0;
  enum operator op = ADD;

  print_status(op, cur, sum);

  while (1) {
    c = getchar();
    switch(c) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      cur = parse_num(cur, c);
      break;
    case '+':
      if (cur != 0) {
        sum = cur;
        cur = 0;
      }
      op = ADD;
      break;
    case '-':
      if (cur != 0) {
        sum = cur;
        cur = 0;
      }
      op = SUB;
      break;
    case '*':
      if (cur != 0) {
        sum = cur;
        cur = 0;
      }
      op = MULTIPLE;
      break;
    case '/':
      if (cur != 0) {
        sum = cur;
        cur = 0;
      }
      op = DIVIDE;
      break;
    case '=':
      sum = process(sum, cur, op);
      break;
    case 'c':
      sum = 0;
      cur = 0;
      op = 0;
      break;
    default:
      continue;
    }
    print_status(op, cur, sum);
  }
   StdinRaw(0);

  return(EXIT_SUCCESS);
}
