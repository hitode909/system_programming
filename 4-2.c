
#include <stdio.h>
#include <string.h>
#include <pwd.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#define TARGET_NAME "harada"
#define OTHER_NAME "root"

void handler(int);

int main(void){
	struct passwd *ptr;

	if(signal(SIGALRM, handler)==SIG_ERR){
		perror("signal");
		exit(EXIT_FAILURE);
	}

	alarm(1);

	for(;;){
		ptr = getpwnam(TARGET_NAME);
		if(ptr==NULL){
			perror("getpwnam");
			exit(EXIT_FAILURE);
		}

		if(strcmp(ptr->pw_name,TARGET_NAME) != 0){
			printf("return value corrupted! pw_name =%s\n",ptr->pw_name);
			exit(EXIT_FAILURE);
		}
		//else{/* 注意!! rainbow環境下でここを表示させると，アラームハンドラが起動できない */
		//	printf("pw_name =%s\n",ptr->pw_name);
		//}
		/* 注意!! sleepとalarmを混用してはならない(sleepはalarmを使って実装されてる) */
	}
}

void handler(int signum){
	struct passwd *ptr;

	printf("in signal handler\n");
	ptr = getpwnam(OTHER_NAME);	/* 非リエントラントな関数呼び出し */
	if(ptr==NULL){
		perror("getpwnam");
		exit(EXIT_FAILURE);
	}

	alarm(1);
}


/*
非リエントラントなので，失敗することがある

in signal handler
in signal handler
return value corrupted! pw_name =root
 */
