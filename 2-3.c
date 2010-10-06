
  #include <stdio.h>
  #include <stdlib.h>
  #include <unistd.h>

  int main(void) {
        int nice_value;

        nice_value = nice(0);
        printf("nice value = %d\n", nice_value);
        sleep(6);

        nice_value = nice(5);
        printf("Nice(5) executed.\n");
        printf("nice value = %d\n", nice_value);
        sleep(6);

        nice_value = nice(5);
        printf("Nice(5) executed.\n");
        printf("nice value = %d\n", nice_value);
        sleep(6);

        nice_value = nice(5);
        printf("Nice(5) executed.\n");
        printf("nice value = %d\n", nice_value);
        sleep(6);

        nice_value = nice(5);
        printf("Nice(5) executed.\n");
        printf("nice value = %d\n", nice_value);
        sleep(6);

        exit(EXIT_SUCCESS);
  }
    