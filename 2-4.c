
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


/*
  一回目はディスクへのアクセスが発生するが，二度目以降はファイルがキャッシュに乗っているので速い．
  grepは子プロセスで行うので，子プロセスの時間のほうが大きい．
  (∩≧≦∩) ./a.out
経過時間:   0.40 秒
親プロセスの時間
        user CPU:   0.00 秒
        sys  CPU:   0.00 秒
子プロセスの時間
        user CPU:   0.04 秒
        sys  CPU:   0.04 秒
<|`・・´|/ ./a.out
経過時間:   0.03 秒
親プロセスの時間
        user CPU:   0.00 秒
        sys  CPU:   0.00 秒
子プロセスの時間
        user CPU:   0.01 秒
        sys  CPU:   0.00 秒

 */
