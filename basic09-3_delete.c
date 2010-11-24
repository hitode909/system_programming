
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int semid;	/* セマフォ集合識別子 */

	/* セマフォ集合識別子をコマンドラインから取得 */
	if(argc != 2){
		puts("USAGE: basic09-3_delete <semid>");
		exit(EXIT_FAILURE);
	}
	semid = atoi(argv[1]);

	/* セマフォ集合を削除 */
	if(semctl(semid,0,IPC_RMID)<0){
		/* 失敗時 */
		perror("semctl PIC_RMID");
		exit(EXIT_FAILURE);
	}
	else{
		printf("semaphore set %d removed\n", semid);
	}

	exit(EXIT_SUCCESS);
}

      