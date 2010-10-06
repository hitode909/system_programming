
  /*
  * times()の利用例
  */

  #include <stdio.h>
  #include <stdlib.h>
  #include <sys/times.h>
  #include <time.h>
  #include <unistd.h>

  void doit(char *, clock_t);

  int main(void) {
      clock_t start, end;
      struct tms t_start, t_end;

      start = times(&t_start);
      /* 画面の乱れをなくすために出力をリダイレクトする */
      system("grep the /usr/share/doc/*/* > /dev/null 2> /dev/null");
      end = times(&t_end);

      doit("経過時間", end - start);

      puts("親プロセスの時間");
      doit("\tuser CPU", t_end.tms_utime);
      doit("\tsys  CPU", t_end.tms_stime);

      puts("子プロセスの時間");
      doit("\tuser CPU", t_end.tms_cutime);
      doit("\tsys  CPU", t_end.tms_cstime);

      exit(EXIT_SUCCESS);
  }

  void doit(char *str, clock_t time) {
      /* 毎秒のクロック刻みを得る */
      long tps = sysconf(_SC_CLK_TCK);

      printf("%s: %6.2f 秒\n", str, (float)time/tps);
  }
    