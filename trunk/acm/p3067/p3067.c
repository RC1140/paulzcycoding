#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAXN = 1000, MAXM = 1000;

typedef struct {
  int east, west;
} Highway;

int comparor(const void *, const void *);

int main(int argc, char* argv[]) {
  int t, T;
  long long sum;
  Highway highways[MAXN * MAXM];
  int n, m;
  int k;

  int map[MAXM + 1];
  int i, j, w;

  scanf("%d", &T);

  for (t = 1; t <= T; ++t) {
    sum = 0;
    scanf("%d %d %d", &n, &m, &k);
    for (i = 0; i < k; ++i) {
      scanf("%d %d", &highways[i].east, &highways[i].west);
    }

    qsort(highways, k, sizeof(Highway), comparor);
    memset(map, 0, sizeof(map));

    for (i = 0, j = 0; i < k; i = j) {
      for (j = i; j < k && highways[j].east == highways[i].east; ++j) {
	for (w = highways[j].west - 1; w > 0; w -= (w & -w)) {
	  sum += map[w];
	}
	for (w = highways[j].west; w <= m; w += (w & -w)) {
	  ++map[w];
	}
      }
    }

    printf("Test case %d: %I64d\n", t, sum);
  }

  return 0;
}

int comparor(const void* a, const void* b) {
  const Highway *p = (const Highway *)a;
  const Highway *q = (const Highway *)b;
  if (p->east > q->east) {
    return -1;
  } else if (p->east < q->east) {
    return 1;
  } else {
    return q->west - p->west;
  }
}
