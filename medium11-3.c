#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>

void herr_quit(const char*);

int main(int argc, char *argv[]){
	char *hostname;	/* ホスト名 */
	struct hostent *hostinfo;	/* ホスト情報 */
	struct in_addr **paddr;	/* ホスト名に対応するIPアドレスのリスト
							   (あるホスト名に対応するIPアドレスは複数存在しうるため，リスト形式になっている) */
	char *ip_addr;	/* IPアドレスの文字列 */	

	/* ホスト名をコマンドラインから取得 */
	if(argc != 2){
		puts("USAGE: hostinfo <hostname>\n");
		exit(EXIT_FAILURE);
	}
	hostname = argv[1];

	/* ホスト名からホスト情報を得る(lookup) */
	hostinfo = gethostbyname(hostname);
	if(!hostinfo){
		herr_quit("gethostbyname");
	}

	/* ホスト名の表示 */
	printf("hostname: %s\n",hostinfo->h_name);

	/* IPアドレスの表示 */
	puts("addresses:");
	paddr = (struct in_addr **)(hostinfo->h_addr_list);
	while(*paddr){
		ip_addr = inet_ntoa(**paddr);
		printf("\t%s\n", inet_ntoa(**paddr));
		paddr++;
	}

	exit(EXIT_SUCCESS);
}

void herr_quit(const char *msg){
	herror(msg);
	exit(EXIT_FAILURE);
}
