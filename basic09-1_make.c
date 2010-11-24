
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#define BUFSZ 32	/* 共有メモリのサイズ */

int main(void){
	int shmid;	/* 共有メモリ識別子 */

	/* 新たな共有メモリ作成 */
	/* メモリ領域は0で初期化される */
	shmid = shmget(IPC_PRIVATE, BUFSZ, 0666);
	if(shmid<0){
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	printf("shared memory created: %d, %dbyte\n", shmid, BUFSZ);

	exit(EXIT_SUCCESS);
}

      