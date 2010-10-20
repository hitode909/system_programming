#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define __USE_XOPEN_EXTENDED
#define _XOPEN_SOURCE 500
#include <signal.h>

int main(void){
	/* SIGINTシグナルのブロック */
	if(sighold(SIGINT)<0){
		perror("sighold");
		exit(EXIT_FAILURE);
	}
	printf("block SIGINT\n");

	sleep(5);

	if(sigrelse(SIGINT)<0){
		perror("sigrelse");
		exit(EXIT_FAILURE);
	}
	printf("unblock SIGINT\n");

	for(;;){
		pause();
		sleep(1);
	}

	return 0;
}

/*
unblockした後にkillする
% ./a.out &
[1] 17757
% block SIGINT
unblock SIGINT
   kill -s INT 17757
%
[1]  + interrupt  ./a.out
% %
unblockする前にkillする
% ./a.out &
[1] 17659
% block SIGINT
kill -s INT 17659
%
[1]  + interrupt  ./a.out

 */
