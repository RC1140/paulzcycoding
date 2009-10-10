#include <stdio.h>

void function(int a, int b, int c){
  char buffer1[5];
  char buffer2[10];
  int *r;
  r = buffer1 + 0x18;
  (*r) += 7;
}

int main(){
  int x = 0;
  function(1,2,3);
  x = 1;
  printf("x = %d\n", x);
}
