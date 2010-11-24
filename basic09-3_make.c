
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
	int semid;	/* セマフォ集合識別子 */
	int flags = 0666;	/* パーミッション */
	int nsems = 1;	/* セマフォの数 */

	/* セマフォ集合作成 */
	semid = semget(IPC_PRIVATE, nsems, flags);
	if(semid < 0){/* セマフォ集合作成失敗時 */
		perror("semget");
		exit(EXIT_FAILURE);
	}
	printf("semaphore %d created\n", semid);

	/* セマフォ値を1に初期化 */
	if(semctl(semid,0,SETVAL,1)<0){
		perror("semctl:SEtVAL");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}

      