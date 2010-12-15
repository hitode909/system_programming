﻿/*
  basic12-2a.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>

pthread_t thread;

static int arg;
static const int real_bad_error = -12;
static const int normal_error = -10;
static const int success = 1;

void * routine_x(void *arg_in)
{
  int *arg = (int *)arg_in;

  if (*arg == 1) {
    pthread_exit((void *)real_bad_error);

  } else if (*arg == 2) {
    return ((void *)normal_error);

  } else {
    return ((void *)success);
  }
}

extern int 
main(int argc, char **argv)
{
  extern int arg;
  pthread_t thread;
  void *status;

  if (argc < 2)
    printf("usage: %s [1-3]\n", argv[0]), exit(1);

  arg = atoi(argv[1]);

  pthread_create(&thread,
		 NULL,
		 routine_x ,
		 &arg);

  pthread_join(thread, &status);
  if (status == PTHREAD_CANCELED) {
    printf("Thread was canceled.\n");
  } else {
    printf("Thread completed and exit status is %ld.\n", (int)status);
  }

  return 0;
}

/*

basic12-2aおよびbasic12-2bに対しコマンドライン引数として1, 2, 3それぞれを与えたときの実行結果として表示される数値はどのようになるか．

% gcc -pthread basic12-2a.c
% ./a.out
usage: ./a.out [1-3]
% ./a.out 1
Thread completed and exit status is -12.
% ./a.out 2
Thread completed and exit status is -10.
% ./a.out 3
Thread completed and exit status is 1.

% gcc -pthread basic12-2b.c
% ./a.out
usage: ./a.out [1-3]
% ./a.out 1
Thread completed and exit status is -12.
% ./a.out 2
Thread completed and exit status is -10.
% ./a.out 3
Thread completed and exit status is 1.

 */
