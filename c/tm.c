#include <stdio.h>
#include <time.h>
#include <unistd.h>

void print_help_message() {
  printf("tm - print time\n");
  printf("usage: tm [h|n|u|f] [args]\n");
  printf("  if no option, print 10-digit timestamp\n");
  printf("-h          print (h)elp message\n");
  printf("-n          (n)ormal style, YYYY-mm-dd HH:MM:SS\n");
  printf("-u          (u)tc style\n");
  printf("-f <format> (f)ormatted form, accept strftime format\n");
  printf("\n");
}

int main(int argc, char **argv) {
  time_t t;
  struct tm *time_info;
  time(&t);
  time_info = localtime(&t);

  char buffer[100];

  switch (getopt(argc, argv, "hnuf:")) {
  case 'h':
    print_help_message();
    break;
  case 'n':
    strftime(buffer, 100, "%Y-%m-%d %H:%M:%S", time_info);
    printf("%s\n", buffer);
    break;
  case 'u':
    strftime(buffer, 100, "%Y-%m-%dT%H:%M:%S%z", time_info);
    printf("%s\n", buffer);
    break;
  case 'f':
    if (strftime(buffer, 100, optarg, time_info) == 0)
      printf("Bad format\n");
    else
      printf("%s\n", buffer);
    break;
  default:
    printf("%ld\n", t);
  }
}