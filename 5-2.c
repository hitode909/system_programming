#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include <time.h>
#include <unistd.h>

void doit(char *, clock_t);
void sample_func1(void);
void sample_func2(void);

int main(void)
{
  clock_t start, end;
  struct tms t_start, t_end;

  start = times(&t_start);
  sample_func1();
  end = times(&t_end);

  doit("sample_func1:\n経過時間", end - start);
  puts("実行時間");
  doit("\tuser CPU", t_end.tms_utime);
  doit("\tsys  CPU", t_end.tms_stime);

  start = times(&t_start);
  sample_func2();
  end = times(&t_end);

  doit("sample_func2:\n経過時間", end - start);
  puts("実行時間");
  doit("\tuser CPU", t_end.tms_utime);
  doit("\tsys  CPU", t_end.tms_stime);

  exit(EXIT_SUCCESS);
}

void sample_func1(void)
{
  int i, j, k;

  for (i = 0; i < 1000; i++)
    for (j = 0; j < 1000; j++)
      for (k = 0; k < 1000; k++);
}

void sample_func2(void)
{
  int i, j, k;
  pid_t mypid;

  for (i = 0; i < 1000; i++)
    for (j = 0; j < 1000; j++)
      for (k = 0; k < 20; k++)
        mypid = getpid();
}

void doit(char *str, clock_t time)
{
  /* 毎秒のクロック刻みを得る */
  long tps = sysconf(_SC_CLK_TCK);

  printf("%s: %6.2f 秒\n", str, (float)time/tps);
}

/*

  sample_func1はfor文を回しているだけで，ユーザーモードで動作するので，sys CPUは増えない．
  sample_func2は，カーネルモードでgetpidしているので，sys CPUが増える．

sample_func1:
経過時間:   1.91 秒
実行時間
    user CPU:   1.91 秒
    sys  CPU:   0.00 秒

sample_func2:
経過時間:   5.66 秒
実行時間
    user CPU:   5.02 秒
    sys  CPU:   2.55 秒
 */
