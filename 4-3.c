#include <stdio.h>
#include <stdlib.h>
#define __USE_XOPEN_EXTENDED	/* rainbow環境用 */
#include <signal.h>
#include <unistd.h>

int main(void){
	/* SIGINTシグナルのブロック */
	if(sighold(SIGINT)<0){
		perror("sighold");
		exit(EXIT_FAILURE);
	}

	/* SIGTERMシグナルのブロック */
	if(sighold(SIGTERM)<0){
		perror("sighold");
		exit(EXIT_FAILURE);
	}

	for(;;){
		pause();
	}

	return 0;
}

/*
  ブロックされているので，SIGINTとSIGTERMを受け付けない．

% ./a.out &
[1] 17493
% kill -s INT 17493
% kill -s TERM 17493
% kill -s QUIT 17493
%
[1]  + quit       ./a.out

*/
