#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void sem_lock(int semid) {
  struct sembuf sop;
  int nsop;
  sop.sem_num = 0;
  sop.sem_op = -1;
  sop.sem_flg = 0;
  nsop = 1;

  if(semop(semid, &sop, nsop)<0){
    perror("semop");
    exit(EXIT_FAILURE);
  }
}

void sem_unlock(int semid) {
  struct sembuf sop;
  int nsop;
  sop.sem_num = 0;
  sop.sem_op = 1;
  sop.sem_flg = 0;
  nsop = 1;

  if(semop(semid, &sop, nsop)<0){
    perror("semop");
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char *argv[]){
  int shmid;	/* 共有メモリ識別子 */
  int semid;
  struct shmid_ds shminfo;	/* 共有メモリの情報 */
  int bufsz;	/* メモリセグメントのサイズ */
  char *shmaddr;	/* 共有メモリのアドレス */
  int i;
  char c;

  /* 共有メモリ識別子を取得する */
  if(argc != 3){
    puts("USAGE: 9-6read <shmid> <semid>");
    exit(EXIT_FAILURE);
  }
  shmid = atoi(argv[1]);
  semid = atoi(argv[2]);

  /* 読み込みサイズを設定する */

  if (shmctl(shmid, IPC_STAT, &shminfo) < 0) {
    perror("shmctl");
    exit(EXIT_FAILURE);
  }
  printf("size = %d\n", (int)shminfo.shm_segsz);
  bufsz =  (int)shminfo.shm_segsz;

  /* 読み書き両用で共有メモリにプロセスをアタッチする */
  shmaddr = shmat(shmid, 0, SHM_RDONLY);
  if(shmaddr == (void *)(-1)){
    perror("shmat");
    exit(EXIT_FAILURE);
  }

  while (1) {
    /* 共有メモリからデータを読み込み表示 */
    sem_lock(semid);
    printf("read: ");
    for(i=0; i<bufsz; i++){
      c = *(shmaddr+i);
      putc(c,stdout);
    }
    printf("\n");
    sem_unlock(semid);
    usleep(500);
  }

  /* プロセスをデタッチする */
  if(shmdt(shmaddr)<0){
    perror("shmdt");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
