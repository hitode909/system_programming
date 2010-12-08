#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define PORT 50000	/* 接続を待ち受けるポート番号 */

void err_quit(const char*);

int main(void){
	int sockfd;	/* ソケット用ファイルディスクリプタ(接続待ち用) */
	int infd;	/* ソケット用ファイルディスクリプタ(クライアントとの通信用) */
	struct sockaddr_in srv;	/* ソケットアドレス構造体 */
	socklen_t socklen;	/* srvのサイズ */
	int i;

	/* ソケット作成 */
	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if(sockfd <0){
		/* ソケット作成失敗時 */
		err_quit("socket");
	}
	/* ソケットのオプションを，ローカルアドレスを使いまわすように設定する．
	 * ソケットのクローズ後，当該ソケットに対応するアドレスはある程度の時間無効になる．
	 * このアドレスを再利用するためには，以下のようにオプションを設定する.
	 * */
	i=1;
	setsockopt(sockfd, SOL_SOCKET, 0, &i, sizeof(i));

	/* 接続を待ち受けるアドレスを設定 */
	memset(&srv, 0, sizeof(srv));
	srv.sin_family = AF_INET;
	srv.sin_port = htons(PORT);	/* 50000番ポート */
	srv.sin_addr.s_addr = htonl(INADDR_ANY);	/* 任意のIPアドレスで受付 */

	/* ソケットをアドレスにバインド */
	socklen = sizeof(srv);
	if((bind(sockfd, (struct sockaddr *)&srv, socklen))<0){
		err_quit("bind");
	}

	/* incoming接続を待つ */
	if((listen(sockfd,5)<0)){
		err_quit("listen");
	}
	printf("TCP/IP socket available: \n");
	printf("\tport %d\n", ntohs(srv.sin_port));
	printf("\taddr %s\n", inet_ntoa(srv.sin_addr));

	/* 接続を受け付ける */
	while((infd=accept(sockfd, (struct sockaddr *)&srv, &socklen))>=0){
		puts("new connection granted");
		close(infd);	/* 接続をクローズ */
	}

	exit(EXIT_SUCCESS);
}


void err_quit(const char *msg){
	perror(msg);
	exit(EXIT_FAILURE);
}
