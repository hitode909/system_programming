#include <stdio.h>
#include <unistd.h>

int main(void){
    int i;
    printf("pid: %d\n", getpid());

    /* receive signals */
    for(i=0;;i++){
        printf("i=%d\n",i);
        pause();
    }

    return 0;
}
