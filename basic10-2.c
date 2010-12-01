
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

/*
% ./a.out hello &



% netstat --unix --all --program
(Not all processes could be identified, non-owned process info
 will not be shown, you would have to be root to see it all.)
Active UNIX domain sockets (servers and established)
Proto RefCnt Flags       Type       State         I-Node PID/Program name    Path
unix  2      [ ACC ]     STREAM     LISTENING     1768   -                   /dev/gpmctl
unix  2      [ ACC ]     STREAM     LISTENING     3281   -                   /tmp/.X11-unix/X0
unix  2      [ ACC ]     STREAM     LISTENING     1604381 -                   /var/run/proftpd/proftpd.sock
unix  2      [ ACC ]     STREAM     LISTENING     1609385 -                   /var/run/proftpd/proftpd.sock
unix  12     [ ]         DGRAM                    901    -                   /dev/log
unix  2      [ ACC ]     STREAM     LISTENING     1870   -                   /tmp/.font-unix/fs7100
unix  2      [ ACC ]     STREAM     LISTENING     1651   -                   private/rewrite
unix  2      [ ACC ]     STREAM     LISTENING     1655   -                   private/bounce
unix  2      [ ACC ]     STREAM     LISTENING     1659   -                   private/defer
unix  2      [ ACC ]     STREAM     LISTENING     1667   -                   private/proxymap
unix  2      [ ACC ]     STREAM     LISTENING     1671   -                   private/smtp
unix  2      [ ACC ]     STREAM     LISTENING     1675   -                   private/relay
unix  2      [ ACC ]     STREAM     LISTENING     1609966 -                   /tmp/ssh-VxWfy11554/agent.11554
unix  2      [ ACC ]     STREAM     LISTENING     1683   -                   private/error
unix  2      [ ACC ]     STREAM     LISTENING     1687   -                   private/local
unix  2      [ ACC ]     STREAM     LISTENING     1691   -                   private/virtual
unix  2      [ ACC ]     STREAM     LISTENING     1695   -                   private/lmtp
unix  2      [ ACC ]     STREAM     LISTENING     1699   -                   private/maildrop
unix  2      [ ACC ]     STREAM     LISTENING     1703   -                   private/old-cyrus
unix  2      [ ACC ]     STREAM     LISTENING     1707   -                   private/cyrus
unix  2      [ ACC ]     STREAM     LISTENING     1711   -                   private/uucp
unix  2      [ ACC ]     STREAM     LISTENING     1715   -                   private/ifmail
unix  2      [ ACC ]     STREAM     LISTENING     1719   -                   private/bsmtp
unix  2      [ ACC ]     STREAM     LISTENING     1194   -                   /var/run/.nscd_socket
unix  2      [ ]         STREAM                   1612357 12070/a.out         hello

PID = 12070
Path = hello


   --protocol=family , -A
       Specifies the address families (perhaps better described as low level protocols) for which connections are to be shown.  family is a comma (',') separated list of address family keywords like inet,  unix,
       ipx, ax25, netrom, and ddp.  This has the same effect as using the --inet, --unix (-x), --ipx, --ax25, --netrom, and --ddp options.

   -a, --all
       Show both listening and non-listening sockets.  With the --interfaces option, show interfaces that are not marked

   -p, --program
       Show the PID and name of the program to which each socket belongs.

 */
