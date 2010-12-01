
#include <sys/socket.h>
#include <sys/un.h>
#include<stdlib.h>
#include <stdio.h>
#include <unistd.h>

void err_quit(const char*);

int main(int argc, char *argv[]){
	int sockfd;	/* ソケット用ファイルディスクリプタ */
	char *sockname;	/* ソケット名 */
	struct sockaddr_un srv;		/* サーバ用構造体 */

	/* ソケットの名前をコマンドライン引数から取得 */
	if(argc!=2){
		puts("USAGE: basic10-1 <socket name>");
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

	/* プログラムが直ぐに終了しないように，
	 * 自身を終了させるようなシグナルを捕捉するまで待つ
	 */
	pause();

	/* ソケットクローズ */
	close(sockfd);

	exit(EXIT_SUCCESS);
}

void err_quit(const char *msg){
	perror(msg);
	exit(EXIT_FAILURE);
}

      