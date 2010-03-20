#include <stdio.h>

int main(int argc, char* argv[]) {
	double sum = 1;
	double fac = 1.;
	int i = 0;
	printf("n e\n- -----------\n");
	printf("0 1\n");
	for (i = 1; i <= 9; ++i) {
		fac *= i;
		sum += 1 / fac;
		printf("%d %.10g\n", i, sum);
	}
	return 0;
}
