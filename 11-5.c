#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include<stdbool.h>
#define PORT 50000
#define BUFSIZE 200

void err_quit(const char*);
void herr_quit(const char *);

int pidIsChild(pid_t pid) {
  return pid == 0;
}

int pidIsFailed(pid_t pid) {
  return pid == -1;
}

int pidIsParent(pid_t pid) {
  return pid > 0;
}

void handleFailed() {
  perror("fork");
  exit(EXIT_FAILURE);
}

void handleChild(int sockfd, int infd) {
  int len;
  char buf[BUFSIZE];

  close(sockfd);
  /* リクエストを標準出力に表示 */
  while((len=read(infd, buf, sizeof(buf)))){
    write(stdout->_file, buf, len);
  }
  close(infd);
  puts("a connection closed");
}

void handleParent(int sockfd, int infd) {
  close(infd);
}

/* hostnameからipを得る */
int get_ip_from_hostname(char* hostname, char* returns) {
  struct hostent *hostinfo;
  struct in_addr **paddr;

  hostinfo = gethostbyname(hostname);
  if(!hostinfo){
    herr_quit("gethostbyname");
  }

  paddr = (struct in_addr **)(hostinfo->h_addr_list);
  strcpy(returns, inet_ntoa(**paddr));
  return 1;
}

int do_server(void){
  int sockfd;
  int infd;
  struct sockaddr_in srv;
  socklen_t socklen;
  int i;
  pid_t pid;

  /* ソケット作成 */
  sockfd = socket(PF_INET, SOCK_STREAM, 0);
  if(sockfd <0){
    err_quit("socket");
  }

  /* ソケットのオプションを，ローカルアドレスを使いまわすように設定する． */
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

    pid = fork();

    if (pidIsFailed(pid)) {
      handleFailed();
    }

    if (pidIsChild(pid)) {
      handleChild(sockfd, infd);
    }

    if (pidIsParent(pid)) {
      handleParent(sockfd, infd);
    }

  }

  exit(EXIT_SUCCESS);
}


int do_client(char* host_addr, char* port_str){
  int sockfd;	/* ソケット用ファイルディスクリプタ */
  struct sockaddr_in cli;	/* クライアント用ソケット構造体 */
  socklen_t socklen;
  int port;	/* ポート番号 */
  char buf[BUFSIZE];
  char ip_addr[BUFSIZE];

  get_ip_from_hostname(host_addr, ip_addr);

  port = atoi(port_str);

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

  /* PIDを送信 */
  int i;
  for(i = 0; i < 100; i++) {
    sprintf(buf, "%d from %d\n", i, getpid());
    write(sockfd, buf, strlen(buf));
    printf("sent %s", buf);
    sleep(1);
  }

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

int main(int argc, char *argv[]){
  bool is_server;

  /* mainでは，do_serverとdo_clientを呼ぶだけ */

  if(strcmp(argv[1], "server") != 0 && strcmp(argv[1], "client") != 0){
    puts("USAGE: 11-5 server");
    puts("USAGE: 11-5 client <server> <host>");
    exit(EXIT_FAILURE);
  }
  is_server = strcmp(argv[1], "server") == 0;
  char* server = argv[2];
  char* port = argv[3];

  if (is_server) {
    do_server();
  } else {
    do_client(server, port);
  }

  exit(EXIT_SUCCESS);
}


/*
% ./a.out client cyborg44.fse.cs.ritsumei.ac.jp 50000
connected to socket.
sent 0 from 95893
sent 1 from 95893
sent 2 from 95893
sent 3 from 95893
sent 4 from 95893

% ./a.out server
TCP/IP socket available:
        port 50000
        addr 0.0.0.0
new connection granted
0 from 95893
1 from 95893
2 from 95893
3 from 95893
4 from 95893
new connection granted
0 from 95895
5 from 95893
1 from 95895
6 from 95893

Proto Recv-Q Send-Q  Local Address          Foreign Address        (state)
tcp4       0      0  localhost.50000        localhost.58641        ESTABLISHED
tcp4       0      0  localhost.58641        localhost.50000        ESTABLISHED
tcp4       0      0  cyborg44.fse.cs..50000 cyborg44.fse.cs..58640 ESTABLISHED
tcp4       0      0  cyborg44.fse.cs..58640 cyborg44.fse.cs..50000 ESTABLISHED

 */
