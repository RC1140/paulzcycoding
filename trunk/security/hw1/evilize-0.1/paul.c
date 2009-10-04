#include <stdio.h>

int main_good(int argc, char* argv[]) {
  printf("Be ware! Tomorrow is the deadline of homework!\n");
  return 0;
}

int main_evil(int argc, char* argv[]) {
  printf("I'll extend the deadline until next century!\n");
  return 0;
}
