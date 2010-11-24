
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[]){
	int msgid;	/* メッセージキュー識別子 */

	/* メッセージキューの識別子を得る */
	if(argc != 2){
		puts("USAGE: basic09-2_delete <msgid>");
		exit(EXIT_FAILURE);
	}
	msgid = atoi(argv[1]);

	/* メッセージキューの削除 */
	if(msgctl(msgid, IPC_RMID,NULL)<0){
		perror("msgctl: IPC_RMID");
		exit(EXIT_FAILURE);
	}
	printf("deleted queue id = %d\n", msgid);

	exit(EXIT_SUCCESS);
}

      