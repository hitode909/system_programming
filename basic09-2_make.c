
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	key_t key;	/* キー値 */
	int msgid;	/* 識別子 */

	key = 132;	/* キー値 */

	/* キュー作成 */
	msgid = msgget(key, IPC_CREAT|IPC_EXCL|0666);
	if(msgid<0){
		perror("msgget:create");
		exit(EXIT_FAILURE);
	}
	printf("created queue id =%d\n", msgid);

	/*
	 * 作成時と同じキーを指定してキューの識別子を取得．
	 * msgget()システムコールは，第二引数を0にすると
	 * 指定したキー値を持つ既存メッセージキューの識別子を返せる
	 * */
	msgid = msgget(key,0);
	if(msgid < 0){
		perror("msgget:open");
		exit(EXIT_FAILURE);
	}
	printf("queue id =%d\n", msgid);

	exit(EXIT_SUCCESS);
}

      