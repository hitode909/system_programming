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
  while(1) {
    int i;
    pthread_mutex_lock(&mutex); /* lock */
    for (i = 0; i < 5; i++) {
      num++;
      printf("boss thread: num = %d\n", num);
      fflush(stdout);
      sleep(1);
    }
    pthread_mutex_unlock(&mutex); /* unlock */
  }
  return(EXIT_FAILURE);
}

/* worker thread */
void *print_number(void *args)
{
  while(1) {
    int i;
    pthread_mutex_lock(&mutex); /* lock */
    for (i = 0; i < 5; i++) {
      num++;
      printf("worker thread: num = %d\n", num);
      fflush(stdout);
      sleep(2);
    }
    pthread_mutex_unlock(&mutex); /* unlock */
  }
  return(NULL);
}
