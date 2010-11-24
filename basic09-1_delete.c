
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#define BUFSZ 16	/* 共有メモリのサイズ */

int main(int argc, char *argv[]){
	int shmid;	/* 共有メモリ識別子 */

	/* 共有メモリの識別子を得る */
	if(argc != 2){
		puts("USAGE: basic09-1_delete <identifier>");
		exit(EXIT_FAILURE);
	}
	shmid = atoi(argv[1]);

	/* 共有メモリを削除する */
	if(shmctl(shmid, IPC_RMID,NULL)<0){
		perror("shmctl: IPC_RMID");
		exit(EXIT_FAILURE);
	}

	printf("shared memory deleted: %d\n", shmid);

	exit(EXIT_SUCCESS);
}

      