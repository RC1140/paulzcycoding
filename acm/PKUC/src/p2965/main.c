#include <stdio.h>

int mat[16][16] = {
  1,1,1,1,1,0,0,0,1,0,0,0,1,0,0,0,
  1,1,1,1,0,1,0,0,0,1,0,0,0,1,0,0,
  1,1,1,1,0,0,1,0,0,0,1,0,0,0,1,0,
  1,1,1,1,0,0,0,1,0,0,0,1,0,0,0,1,
  1,0,0,0,1,1,1,1,1,0,0,0,1,0,0,0,
  0,1,0,0,1,1,1,1,0,1,0,0,0,1,0,0,
  0,0,1,0,1,1,1,1,0,0,1,0,0,0,1,0,
  0,0,0,1,1,1,1,1,0,0,0,1,0,0,0,1,
  1,0,0,0,1,0,0,0,1,1,1,1,1,0,0,0,
  0,1,0,0,0,1,0,0,1,1,1,1,0,1,0,0,
  0,0,1,0,0,0,1,0,1,1,1,1,0,0,1,0,
  0,0,0,1,0,0,0,1,1,1,1,1,0,0,0,1,
  1,0,0,0,1,0,0,0,1,0,0,0,1,1,1,1,
  0,1,0,0,0,1,0,0,0,1,0,0,1,1,1,1,
  0,0,1,0,0,0,1,0,0,0,1,0,1,1,1,1,
  0,0,0,1,0,0,0,1,0,0,0,1,1,1,1,1
};

int main(int argc, char *argv) {
  int i, j, k;
  int a[16], b[16];
  char c;

  for (i = 0; i < 16; ++i) {
    b[i] = 0;
    while (1) {
      c = getchar();
      if (c == '+') {
	a[i] = 1;
	break;
      } else if (c == '-') {
	a[i] = 0;
	break;
      }
    }
  }

  for (i = 0; i < 16; ++i) {
    for (j = 0; j < 16; ++j) {
      b[i] += mat[i][j] * a[j];
    }
  }

  int sum = 0;
  for (i = 0; i < 16; ++i) {
    if (b[i] %= 2) {
      ++sum;
    }
  }
  printf("%d\n", sum);

  for (i = 0; i < 16; ++i) {
    if (b[i]) {
      printf("%d %d\n", i / 4 + 1, i % 4 + 1);
    }
  }

  return 0;
}
