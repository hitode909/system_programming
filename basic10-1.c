
#include <sys/socket.h>
#include <sys/un.h>
#include<stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include<string.h>

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

	/* ソケットをクローズ */
	close(sockfd);

	exit(EXIT_SUCCESS);
}

void err_quit(const char *msg){
	perror(msg);
	exit(EXIT_FAILURE);
}


/*
プログラムbasc10-1.cを実行し，アドレスのバインドに成功した場合，指定したパスの特殊ファイルが生成されることを確認せよ．
% ./101 hello
% ls -l | grep hello
srwxr-xr-x  1 fkd  staff       0 Dec  1 13:21 hello

また，同一パスの特殊ファイルが既に存在する場合，バインドに失敗することを確認せよ．
% ./101 hello
bind: Address already in use
% rm hello
% ./101 hello
%
 */
