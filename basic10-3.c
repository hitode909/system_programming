
#include <sys/socket.h>
#include <sys/un.h>
#include<stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void err_quit(const char*);

int main(int argc, char *argv[]){
	int sockfd;	/* ソケット用ファイルディスクリプタ */
	char *sockname;	/* ソケット名 */
	struct sockaddr_un srv;	/* アドレス */
	socklen_t socklen;	/* 構造体のサイズ */
	struct sockaddr_un cli;	/* クライアントのアドレス */

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

	/* サーバ構造体を初期化 & セットアップ */
	memset(&srv, 0, sizeof(srv));
	srv.sun_family = AF_UNIX;
	strncpy(srv.sun_path, sockname, sizeof(srv.sun_path));

	/* ソケットをアドレスにバインド */
	if((bind(sockfd, (struct sockaddr *)&srv, SUN_LEN(&srv)))<0){
		err_quit("bind");
	}

	/* 接続を待つ */
	if((listen(sockfd,1)<0)){
		err_quit("listen");
	}
	printf("socket available: %s\n", srv.sun_path);

	/* 全ての接続を受け付けるために永久ループ */
	while(accept(sockfd, (struct sockaddr *)&cli, &socklen)>=0){
		printf("new connection granted.\n");
	}

	close(sockfd);

	exit(EXIT_SUCCESS);
}

void err_quit(const char *msg){
	perror(msg);
	exit(EXIT_FAILURE);
}

      