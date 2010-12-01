
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void err_quit(const char*);

int main(int argc, char *argv[]){
	char *sockname;	/* ソケット名 */
	int sockfd;	/* ソケット用ファイルディスクリプタ */
	struct sockaddr_un cli;	/* 接続先アドレスを表す構造体 */
	socklen_t socklen;	/* 構造体cliのサイズ */

	/* ソケット名をコマンドライン引数から取得 */
	if(argc!=2){
		puts("USAGE: mksock <filename>");
		exit(EXIT_FAILURE);
	}
	sockname = argv[1];

	/* ソケット作成 */
	sockfd = socket(PF_UNIX, SOCK_STREAM, 0);
	if(sockfd <0){
		/* ソケット作成失敗時 */
		err_quit("socket");
	}

	/* 接続先アドレス設定 */
	memset(&cli, 0, sizeof(cli));
	cli.sun_family = AF_UNIX;
	strncpy(cli.sun_path, sockname, sizeof(cli.sun_path));
	socklen = SUN_LEN(&cli);

	/* サーバに接続 */
	if(connect(sockfd, (struct sockaddr *)&cli, socklen)){
		err_quit("connect");
	}
	printf("connected to socket %s\n", cli.sun_path);


	exit(EXIT_SUCCESS);
}

void err_quit(const char *msg){
	perror(msg);
	exit(EXIT_FAILURE);
}

      