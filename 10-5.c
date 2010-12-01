#include <sys/socket.h>
#include <sys/un.h>
#include<stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include<string.h>
#include<stdbool.h>
#define BUFSIZE 200

void err_quit(const char*);
void do_server(const char*);
void do_client(const char*);

int main(int argc, char *argv[]){
  char *sockname;
  bool is_server;

  /* mainでは，do_serverとdo_clientを呼ぶだけ */

  if(argc!=3){
    puts("USAGE: 10-4 [server|client] <socket name>");
    exit(EXIT_FAILURE);
  }
  is_server = strcmp(argv[1], "server") == 0;
  sockname = argv[2];

  if (is_server) {
    do_server(sockname);
  } else {
    do_client(sockname);
  }

  exit(EXIT_SUCCESS);
}

void err_quit(const char *msg){
  perror(msg);
  exit(EXIT_FAILURE);
}

int create_socket() {
  int fd;
  fd = socket(PF_UNIX, SOCK_STREAM, 0);
  if(fd <0){
    /* ソケット作成失敗時 */
    err_quit("socket");
  }
  return fd;
}

void do_server(const char* sockname) {
  int sockfd;	/* ソケット用ファイルディスクリプタ */
  struct sockaddr_un srv;		/* サーバ用構造体 */
  struct sockaddr_un cli;	/* クライアントのアドレス */
  socklen_t socklen;	/* 構造体cliのサイズ */
  int acceptfd;	/* 通信用ファイルディスクリプタ */
  int len;
  char buf[BUFSIZE];	/* 入力内容を保持する配列 */

  /* ソケット作成 */
  sockfd = create_socket();

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

  /* acceptする */
  acceptfd = accept(sockfd, (struct sockaddr *)&cli, &socklen);
  printf("new connection granted\n");

  /* clientからのを読んで標準出力に表示 */
  while((len=read(acceptfd, buf, sizeof(buf)))){
    write(stdout->_file, buf, len);
  }

  /* fd閉じる */
  close(acceptfd);
  close(sockfd);

  exit(EXIT_SUCCESS);

}

void do_client(const char* sockname) {
  int sockfd;	/* ソケット用ファイルディスクリプタ */
  struct sockaddr_un cli;	/* 接続先アドレスを表す構造体 */
  socklen_t socklen;	/* 構造体cliのサイズ */
  int len;
  char buf[BUFSIZE];	/* 入力内容を保持する配列 */

  /* ソケット作成 */
  sockfd = create_socket();

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

  /* PIDを送信 */
  sprintf(buf, "PID = %d\n", getpid());
  len = strlen(buf);
  write(sockfd, buf, len);

  printf("sent %s", buf);

  /* fd閉じる */
  close(sockfd);

}

/*
% ./a.out server hello
socket available: hello
new connection granted
PID = 52828

% ./a.out client hello
connected to socket hello
sent PID = 52828


 */
