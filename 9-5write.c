#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]){
  int shmid;	/* 共有メモリ識別子 */
  struct shmid_ds shminfo;	/* 共有メモリの情報 */
  int bufsz;	/* メモリセグメントのサイズ */
  char *shmaddr;	/* 共有メモリのアドレス */
  int i;
  char c;

  srand(time(NULL));

  /* 共有メモリ識別子を取得する */
  if(argc != 2){
    puts("USAGE: medium09-4 <shmid>");
    exit(EXIT_FAILURE);
  }
  shmid = atoi(argv[1]);

  /* 書き込みサイズを設定する */

  if (shmctl(shmid, IPC_STAT, &shminfo) < 0) {
    perror("shmctl");
    exit(EXIT_FAILURE);
  }
  printf("size = %d\n", (int)shminfo.shm_segsz);
  bufsz =  (int)shminfo.shm_segsz;

  /* 読み書き両用で共有メモリにプロセスをアタッチする */
  shmaddr = shmat(shmid, 0, 0);
  if(shmaddr == (void *)(-1)){
    perror("shmat");
    exit(EXIT_FAILURE);
  }

  while (1) {
    c = 'a' + rand() % ('z'-'a');
    /* 共有メモリにデータを書き込み */
    printf("write: ");
    for(i=0; i<bufsz; i++){
      *(shmaddr+i) = c;
      putc(c,stdout);
    }
    printf("\n");
    usleep(500000);
  }

  /* プロセスをデタッチする */
  if(shmdt(shmaddr)<0){
    perror("shmdt");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
