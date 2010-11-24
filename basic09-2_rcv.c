
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
#define BUFSZ 256

/* メッセージを表す構造体 */
typedef struct {
	long type;	/* メッセージタイプ */
	char text[BUFSZ];	/* データバッファ */
} msg_t;

int main(int argc, char *argv[]){
	int msgid;	/* メッセージキュー識別子 */
	msg_t msg;	/* 受信メッセージ */

	/* メッセージキューの識別子を得る */
	if(argc != 2){
		puts("USAGE: basic09-2_rcv <msgid>");
		exit(EXIT_FAILURE);
	}
	msgid = atoi(argv[1]);

	/* キューからメッセージ受信 */
	/* msgrcvの第４引数
	 *	=0: キューの先頭のメッセージ受信
	 *	>0: メッセージタイプが第４引数に等しい，最も先頭側のメッセージ受信
	 *	<0: メッセージタイプが第４引数の絶対値以下の，最も先頭側のメッセージ受信
	 * */
	/* msgrcvの第5引数
	 *  IPC_NOWAIT: 受信可能なメッセージがない場合，システムコールは失敗して直ちに帰る．
	 *  MSG_EXCEPT: 0以上の第４引数と一緒に指定して，第4引数以外のタイプの最初のメッセージを受信する．
	 *  MSG_NOERROR: 受信したメッセージのデータバッファサイズが第3引数より長かった場合は切り詰める
	 */
	if(msgrcv(msgid, &msg, sizeof(msg.text), 0, IPC_NOWAIT)<0){
		perror("msgsnd");
		exit(EXIT_FAILURE);
	}

	printf("Message received: %s\n", msg.text);

	exit(EXIT_SUCCESS);
}

      