#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
  #include <unistd.h>

pthread_t thread;

static int arg;
static const int real_bad_error = -12;
static const int normal_error = -10;
static const int success = 1;

void * routine_x(void *arg_in)
{
  int *arg = (int *)arg_in;

  if (*arg == 1) {
    pthread_exit((void *)&real_bad_error);

  } else if (*arg == 2) {
    return ((void *)&normal_error);

  } else if (*arg == 3) {
    return ((void *)&success);

  } else if (*arg == 4) {
    while(1) {
      pthread_testcancel();
    }
  } else {
    printf("1-4...\n");
    return ((void *)&success);
  }
}

extern int
main(int argc, char **argv)
{
  extern int arg;
  pthread_t thread;
  void *statusp;

  if (argc < 2)
    printf("usage: %s [1-4]\n", argv[0]), exit(1);

  arg = atoi(argv[1]);

  if (arg < 1 || arg > 4)
    printf("usage: %s [1-4]\n", argv[0]), exit(1);

  pthread_create(&thread,
		 NULL,
		 routine_x ,
		 &arg);

  sleep(1);
  pthread_cancel(thread);
  pthread_join(thread, &statusp);
  if (statusp == PTHREAD_CANCELED) {
    printf("Thread was canceled.\n");
  } else {
    printf("Thread completed and exit status is %d.\n", *(int *)statusp);
  }

  return 0;
}

/*
% gcc 12-5.c
% ./a.out 1
Thread completed and exit status is -12.
% ./a.out
usage: ./a.out [1-4]
% ./a.out 2
Thread completed and exit status is -10.
% ./a.out 3
Thread completed and exit status is 1.
% ./a.out 4
Thread was canceled.
 */
