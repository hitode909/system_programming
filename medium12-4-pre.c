#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *print_number(void *args);

int num = 0;
pthread_mutex_t mutex;

/* boss thread */
int main(void)
{
  pthread_t thread;

  pthread_mutex_init(&mutex, NULL); /* init */
  pthread_create(&thread, NULL, print_number, NULL); /* generating new thread */
  while(num < 100) {
    pthread_mutex_lock(&mutex); /* lock */
    num++;
    pthread_mutex_unlock(&mutex); /* unlock */
    printf("boss thread: num = %d\n", num);
    fflush(stdout);
    sleep(1);
  }
  return(EXIT_FAILURE);
}

/* worker thread */
void *print_number(void *args)
{
  while(num < 100) {
    pthread_mutex_lock(&mutex); /* lock */
    num++;
    pthread_mutex_unlock(&mutex); /* unlock */
    printf("worker thread: num = %d\n", num);
    fflush(stdout);
    sleep(2);
  }
  return(NULL);
}

/*
変更前

boss thread: num = 1
boss thread: num = 2
boss thread: num = 3
boss thread: num = 4
boss thread: num = 5
worker thread: num = 6
worker thread: num = 7
worker thread: num = 8
worker thread: num = 9
worker thread: num = 10
boss thread: num = 11
boss thread: num = 12
boss thread: num = 13
boss thread: num = 14
boss thread: num = 15
worker thread: num = 16
^C

変更後

boss thread: num = 1
worker thread: num = 2
boss thread: num = 3
worker thread: num = 4
boss thread: num = 5
worker thread: num = 6

実行時間は，変更後のほうが短い．
sleepしてる間，片方のthreadが待つ必要がなくなるため．

 */
