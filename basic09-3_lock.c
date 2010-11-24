
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int semid;	/* セマフォ集合識別子 */
	struct sembuf sop;	/* 操作 */
	int nsop;	/* 操作数 */

	/* セマフォ集合の識別子を得る */
	if(argc != 2){
		puts("USAGE: basic09-3_lock <semid>");
		exit(EXIT_FAILURE);
	}
	semid = atoi(argv[1]);


	/* 操作設定 */
	sop.sem_num = 0;
	sop.sem_op = -1;
		/*
		 * 操作:1 (sem_op>0の場合，その値をセマフォの値に加える
		 * 操作:0 (sem_op=0の場合，セマフォ値が0になるまで待つ．読み込み許可必要
		 * 操作:-1 (sem_op<0の場合，絶対値がセマフォから引かれる
		 * */
	sop.sem_flg = 0;
	nsop = 1;

	/* セマフォ集合の操作 */
	if(semop(semid, &sop, nsop)<0){
		perror("semop");
		exit(EXIT_FAILURE);
	}

	printf("Semaphore %d locked!\n", semid);

	exit(EXIT_SUCCESS);
}
