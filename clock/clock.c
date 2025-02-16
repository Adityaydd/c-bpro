#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void fill_time(char *, int format); // filling the time in the time buffer
int main() {
  char time[100];
  int format;
  printf("Chose the format 1 for 12 & 2 for 24:");
  scanf("%d", &format);
  while (1) {
    system("clear");
    fill_time(time, format);

    printf("current_time:%s\n", time);
    sleep(1);
  }
  return 0;
}
void fill_time(char *buffer, int format) {

  time_t rawtime; // get a number in rawtime from sys that is used to get the
                  // time from (1971)
  struct tm *current_time;
  time(&rawtime);
  current_time = localtime(&rawtime);
  if (format == 2) {
    strftime(buffer, 100, "%H:%M:%S", current_time);
  } else {

    strftime(buffer, 100, "%I:%M:%S %p", current_time);
  }
}
