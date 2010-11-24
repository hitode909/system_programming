
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
	int msgid;	/* 識別子 */
	msg_t msg;	/* 送信メッセージ */
	int len;	/* メッセージのデータ長 */

	/* メッセージキューの識別子を得る */
	if(argc != 2){
		puts("USAGE: basic09-2_snd <msgid>");
		exit(EXIT_FAILURE);
	}
	msgid = atoi(argv[1]);

	/* メッセージ生成 */
	sprintf(msg.text, "Message from %d", getpid());
	msg.type = getpid();

	/* メッセージキューにメッセージ送信 */
	len = strlen(msg.text);
	if(msgsnd(msgid, &msg, len, 0)<0){
		perror("msgsnd");
		exit(EXIT_FAILURE);
	}

	printf("Message posted: %s\n", msg.text);

	exit(EXIT_SUCCESS);
}

      