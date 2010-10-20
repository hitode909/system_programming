
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

/* function prototype declaration */
void handler(int);

int i;

int main(void){
	/* set first alarm */
	if(alarm(5)>0){
		puts("an alarm was already set");
	}
	sleep(30);

	return 0;
}

/*
  5秒後に終了する

  zsh: alarm      ./a.out

 */
