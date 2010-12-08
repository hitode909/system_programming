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

/* 指定したhost, portに接続してfdを返す */
int http_connect(char* host_addr, char* port_str) {
  int sockfd;
  struct sockaddr_in cli;
  socklen_t socklen;
  int port;	/* ポート番号 */
  char ip_addr[BUFSIZE];

  get_ip_from_hostname(host_addr, ip_addr);

  port = atoi(port_str);

  /* ソケット作成 */
  sockfd = socket(PF_INET, SOCK_STREAM, 0);
  if(sockfd <0){
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

  return sockfd;
}

/* http getして表示 */
void http_get_and_print(char* host_addr, char* port_str, char* path) {
  char buf_req[BUFSIZE];
  char buf_res[BUFSIZE];
  int sockfd = http_connect(host_addr, port_str);
  int len;

  /* request */
  sprintf(buf_req, "GET %s HTTP/1.0\r\n\r\n  \n", path);
  write(sockfd, buf_req, strlen(buf_req));

  /* print response */
  while((len=read(sockfd, buf_res, sizeof(buf_res)))){
    write(stdout->_file, buf_res, len);
  }
  close(sockfd);
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
  if(argc != 4){
    puts("USAGE: 11-4 webmail.ritsumei.ac.jp 80 /index.html");
    exit(EXIT_FAILURE);
  }


  http_get_and_print(argv[1], argv[2], argv[3]);

  exit(EXIT_SUCCESS);
}


/*

% ./a.out webmail.ritsumei.ac.jp 80 /index.html
HTTP/1.1 200 OK^M
Date: Wed, 08 Dec 2010 04:55:09 GMT^M
Server: Apache^M
Last-Modified: Wed, 22 Jul 2009 11:20:40 GMT^M
ETag: "72e388-ff6-8fa39200"^M
Accept-Ranges: bytes^M
Content-Length: 4086^M

*/
