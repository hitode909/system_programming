#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

/* function prototype declaration */
void handler(int);

int i;

int main(void){
	struct timespec sleep_time=(struct timespec){1,0};
	struct timespec reminder;

	/* set signal handler */
	if(signal(SIGALRM, handler)==SIG_ERR){
		perror("signal");
		exit(EXIT_FAILURE);
	}

	/* set first alarm */
	alarm(3);

	for(i=0;;i++){
		printf("i=%d\n",i);
		nanosleep(&sleep_time, &reminder);
	}

	return 0;
}

void handler(int signum){
	i=0;
	alarm(3);
}
