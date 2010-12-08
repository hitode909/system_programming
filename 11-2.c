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

int do_server(void){
  int sockfd;
  int infd;
  struct sockaddr_in srv;
  socklen_t socklen;
  int i;
  int len;
  char buf[BUFSIZE];	/* 入力内容を保持する配列 */

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

    /* clientからのを読んで標準出力に表示 */
    while((len=read(infd, buf, sizeof(buf)))){
      write(stdout->_file, buf, len);
    }
    /* 接続をクローズ */
    close(infd);
  }

  exit(EXIT_SUCCESS);
}


int do_client(char* ip_addr, char* port_str){
  int sockfd;	/* ソケット用ファイルディスクリプタ */
  struct sockaddr_in cli;	/* クライアント用ソケット構造体 */
  socklen_t socklen;
  int port;	/* ポート番号 */
  char buf[BUFSIZE];

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
  sprintf(buf, "PID = %d\n", getpid());
  write(sockfd, buf, strlen(buf));
  printf("sent %s", buf);

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
    puts("USAGE: 11-2 server");
    puts("USAGE: 11-2 client <server> <host>");
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
