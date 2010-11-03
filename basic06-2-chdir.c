
/*
 * chdir を利用して新しいディレクトリへ移動する
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    if(chdir(argv[1]) 
  