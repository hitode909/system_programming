#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>

void err_quit(const char *);
void herr_quit(const char *);

int main(int argc, char *argv[]){
	int sockfd;	/* ソケット用ファイルディスクリプタ */
	struct sockaddr_in cli;	/* クライアント用ソケット構造体 */
	socklen_t socklen;
	char *ip_addr;	/* 接続先アドレス */
	int port;	/* ポート番号 */


	/* アドレスをコマンドライン引数から取得 */
	if(argc!=3){
		puts("USAGE: netconn <ip address> <port>");
		exit(EXIT_FAILURE);
	}
	ip_addr = argv[1];
	port = atoi(argv[2]);

	/* ソケット作成 */
	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if(sockfd <0){
		/* ソケット作成失敗時 */
		err_quit("socket");
	}

	/* クライアント構造体をセットアップ */
	memset(&cli, 0, sizeof(cli));
	cli.sin_family = AF_INET;
	cli.sin_port = htons(port);
	if(!(inet_aton(ip_addr,&cli.sin_addr))){
			herr_quit("inet_aton");
	}

	/* ソケットに接続 */
	socklen = sizeof(cli);
	if(connect(sockfd, (struct sockaddr *)&cli, socklen)){
		err_quit("connect");
	}
	printf("connected to socket.\n");
        sleep(3000);            /* クライアントプログラム内で，すぐにプログラムが終了しない工夫をしているか */

	/* 接続をクローズ */
	close(sockfd);

	exit(EXIT_SUCCESS);
}

void err_quit(const char *msg){
	perror(msg);
	exit(EXIT_FAILURE);
}

void herr_quit(const char *msg){
	herror(msg);
	exit(EXIT_FAILURE);
}


/*
% netstat --tcp --all --program | grep 50000
Proto Recv-Q Send-Q Local Address           Foreign Address         State       PID/Program name
tcp        0      0 *:50000                 *:*                     LISTEN      9412/srv

% netstat --tcp --all --program | grep 50000
tcp        0      0 *:50000                 *:*                     LISTEN      11993/srv
tcp        0      0 localhost.localdo:33044 localhost.localdo:50000 ESTABLISHED 11995/cli
tcp        0      0 localhost.localdo:50000 localhost.localdo:33044 ESTABLISHED 11993/srv
*/
