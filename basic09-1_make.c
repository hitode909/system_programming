
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#define BUFSZ 200	/* 共有メモリのサイズ */

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

/*
プログラムが出力する数字は共有メモリ識別子

% ipcs
IPC status from <running system> as of Wed Nov 24 13:14:38 JST 2010
T     ID     KEY        MODE       OWNER    GROUP
Message Queues:T     ID     KEY        MODE       OWNER    GROUPShared Memory:

T     ID     KEY        MODE       OWNER    GROUP
Semaphores:

% ./9-1make
shared memory created: 131073, 32byte
% ipcs                                                                                                                                                                        [fkd@cyborg44.fse.cs.ritsumei.ac.jp:~/co/system_programming]
IPC status from <running system> as of Wed Nov 24 13:14:43 JST 2010
T     ID     KEY        MODE       OWNER    GROUP
Message Queues:

T     ID     KEY        MODE       OWNER    GROUP
Shared Memory:
m 131073 0x00000000 --rw-rw-rw-      fkd    staff

T     ID     KEY        MODE       OWNER    GROUP
Semaphores:

% ./9-1del 131073
shared memory deleted: 131073
% ipcs                                                                                                                                                                        [fkd@cyborg44.fse.cs.ritsumei.ac.jp:~/co/system_programming]
IPC status from <running system> as of Wed Nov 24 13:14:51 JST 2010
T     ID     KEY        MODE       OWNER    GROUP
Message Queues:

T     ID     KEY        MODE       OWNER    GROUP
Shared Memory:

T     ID     KEY        MODE       OWNER    GROUP
Semaphores:

 */
