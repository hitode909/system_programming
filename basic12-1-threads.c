/*
  マルチスレッドのサンプル
 */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>

void *do_one_thing(void *);
void *do_another_thing(void *);
void do_wrap_up(int, int);

int r1 = 0, r2 = 0;

extern int
main(void)
{
  pthread_t       thread1, thread2;
 
  if (pthread_create(&thread1, 
		 NULL,
		 do_one_thing,
		 (void *) &r1) != 0)
	perror("pthread_create"), exit(1); 

  if (pthread_create(&thread2, 
		 NULL, 
		 do_another_thing,
		 (void *) &r2) != 0)
	perror("pthread_create"), exit(1); 
  
  if (pthread_join(thread1, NULL) != 0)
	perror("pthread_join"),exit(1);

  if (pthread_join(thread2, NULL) != 0)
	perror("pthread_join"),exit(1);

  do_wrap_up(r1, r2);

  return 0; 
}

void *do_one_thing(void *pnum_times)
{
  int i, j, x;
  
  for (i = 0;  i < 4; i++) {
    printf("doing one thing\n"); 
    for (j = 0; j < 10000; j++) x = x + i;
    (*(int *)pnum_times)++;
  }

  return(NULL);
}

void *do_another_thing(void *pnum_times)
{
  int i, j, x;
  
  for (i = 0;  i < 4; i++) {
    printf("doing another \n"); 
    for (j = 0; j < 10000; j++) x = x + i;
    (*(int *)pnum_times)++;
  }

  return(NULL);
}

void do_wrap_up(int one_times, int another_times)
{
  int total;

  total = one_times + another_times;
  printf("All done, one thing %d, another %d for a total of %d\n",
	one_times, another_times, total);
}

/*
basic12-1-threads.cにおいて，do_wrap_upの呼び出しの前にpthread_joinが必要となる理由は何か．

threadの終了を待つため

pthread joinは，指定したスレッドの終了を待つ関数である．

        #include <pthread.h>
        int pthread_join(pthread_t th, void **thread_return);
        •   引数thで指定したスレッドが終了するのを待つ．
        •   引数thread returnがNULLでない場合，thの返り値がこの引数で指し示される領域に格納される．
        •   あるスレッドの終了を待つことができるスレッドは高々一つ(最大で一つ)である．すでに別のスレッドが終了を待っているスレッドthに対してpthread joinを呼び出すとエラーが返る．
        •   返り値は，成功した場合0が返る．エラーの場合はエラーコードが 返る．
 */
