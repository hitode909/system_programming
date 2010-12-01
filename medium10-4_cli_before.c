
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

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

        /* 接続が切れないようsleepする */
        printf("sleep 100\n");
        sleep(100);

	exit(EXIT_SUCCESS);
}

void err_quit(const char *msg){
	perror(msg);
	exit(EXIT_FAILURE);
}

/*
サーバー側
% ./server hello
socket available: hello
new connection granted.

2回接続が来てからプログラムを終了．

クライアント側
% ./client hello
connected to socket hello
sleep 100

サーバーを終了するとConnection refusedになる．

% ./client hello
connect: Connection refused


接続中のnetstat

unix  2      [ ACC ]     STREAM     LISTENING     1619065 12239/server        hello
unix  2      [ ACC ]     STREAM     LISTENING     3269   -                   /tmp/.gdm_socket
unix  2      [ ACC ]     STREAM     LISTENING     1434011 -                   /var/run/acpid.socket
unix  2      [ ACC ]     STREAM     LISTENING     1644   -                   public/cleanup
unix  2      [ ACC ]     STREAM     LISTENING     1663   -                   public/flush
unix  2      [ ACC ]     STREAM     LISTENING     1679   -                   public/showq
unix  3      [ ]         STREAM     CONNECTED     1619066 12239/server        hello
unix  3      [ ]         STREAM     CONNECTED     1619068 12240/client


 */
