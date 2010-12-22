#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

#define MY_ABORT(__COMMENT__) \
      fprintf (stderr, "\n" __COMMENT__ "\n"); \
      exit (1);

/*
 * スレッドパラメータ格納用
 */
typedef struct
{
	char printVal;
	int interval;
} MY_THREAD_ARG;

/*
 * スレッドイニシャル関数
 */
void * myThread (void *arg)
{
	MY_THREAD_ARG *my_thread_arg = (MY_THREAD_ARG *) arg;
	int i = 0;

	for (i = 0; i < 5; i++) {
		//fprintf (stderr, "%c", my_thread_arg->printVal);
		fprintf(stderr,"thread %c: count %d\n", my_thread_arg->printVal, i);
		sleep (my_thread_arg->interval);
    }

	return arg;
}

int main (int argc, char *argv[])
{
	int status;
	void *thread_return;

	// スレッドa用のパラメータ
	pthread_t thread_a;
	MY_THREAD_ARG thread_a_arg;
	thread_a_arg.printVal = 'a';
	thread_a_arg.interval = 1;

	// スレッドb用のパラメータ
	pthread_t thread_b;
	MY_THREAD_ARG thread_b_arg;
	thread_b_arg.printVal = 'b';
	thread_b_arg.interval = 2;

	pthread_attr_t attr_a;
	// スレッドaの属性初期化
	status = pthread_attr_init(&attr_a);
	if (status != 0) {
		MY_ABORT("failed to attr_init thread_a");
    }
	// スレッドa属性を合流可能に設定
	status = pthread_attr_setdetachstate(&attr_a, PTHREAD_CREATE_JOINABLE);
	if (status != 0) {
		MY_ABORT("failed to attr_setdetachstate thread_a");
    }
	// スレッドaを生成
	status = pthread_create (&thread_a, &attr_a, myThread, &thread_a_arg);
	if (status != 0) {
		MY_ABORT("failed to create thread_a");
    }

	pthread_attr_t attr_b;
	// スレッドbの属性初期化
	status = pthread_attr_init(&attr_b);
	if (status != 0) {
		MY_ABORT("failed to attr_init thread_b");
    }

	// スレッドb属性をデタッチ済に設定
	status = pthread_attr_setdetachstate(&attr_b, PTHREAD_CREATE_DETACHED);
	if (status != 0) {
		MY_ABORT("failed to attr_setdetachstate thread_b");
    }

	// スレッドbを生成
	status = pthread_create(&thread_b, &attr_b, myThread, &thread_b_arg);
	if (status != 0) {
		MY_ABORT("failed to create thread_b");
    }

	// スレッドaが終了するのを待つ.
	status = pthread_join(thread_a, &thread_return);
	if (status != 0) {
		MY_ABORT("failed to join thread_a");
    }
	else {
		fprintf(stderr,"\nthread a: pthread_join succeeded.\n");
		// スレッドのイニシャル関数の返り値をチェック.
		assert (&thread_a_arg == thread_return);
    }

	// スレッドbはデタッチしているので,joinに失敗する.
	status = pthread_join (thread_b, &thread_return);
	if (status != 0) {
		fprintf(stderr, "\nthread b: pthread_join failed.\n");
    }
	else {
		MY_ABORT("successed to join thread b");
    }
	fprintf (stderr, "\n");
	sleep(5);
	return 0;
}
