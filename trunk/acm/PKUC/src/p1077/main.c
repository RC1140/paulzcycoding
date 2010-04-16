/*
 * main.c
 *
 *  Created on: Apr 12, 2010
 *      Author: XTOg
 */

#include <stdio.h>

#define U u(state);
#define D d(state);
#define L l(state);
#define R r(state);

#define ROTATE L L U U R R D D
#define ROTATE_B U L L D R R
#define ROTATE_R U U L D D R
#define ROTATE_C L U R D

typedef struct {
	int x[9], y[9];
	int num[3][3];
} state_t;

typedef state_t *state_p;

void setxy(int i, int num, state_p state) {
	state->x[num] = i / 3;
	state->y[num] = i % 3;
	state->num[i / 3][i % 3] = num;
}

#ifdef DEBUG
void print_state(state_p state) {
	int i, j;
	printf("-----\n");
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j) {
			printf("%d ", state->num[i][j]);
		}
		printf("\n");
	}
	printf("-----\n");
}
#endif

void swap(state_p state, int x1, int y1, int x2, int y2) {
	int n1 = state->num[x1][y1];
	int n2 = state->num[x2][y2];

	state->num[x1][y1] = n2;
	state->num[x2][y2] = n1;
	state->x[n1] = x2;
	state->y[n1] = y2;
	state->x[n2] = x1;
	state->y[n2] = y1;
}

void u(state_p state) {
	swap(state, state->x[0], state->y[0], state->x[0] - 1, state->y[0]);
#ifdef DEBUG
	print_state(state);
#else
	putchar('u');
#endif
}

void d(state_p state) {
	swap(state, state->x[0], state->y[0], state->x[0] + 1, state->y[0]);
#ifdef DEBUG
	print_state(state);
#else
	putchar('d');
#endif
}

void r(state_p state) {
	swap(state, state->x[0], state->y[0], state->x[0], state->y[0] + 1);
#ifdef DEBUG
	print_state(state);
#else
	putchar('r');
#endif
}

void l(state_p state) {
	swap(state, state->x[0], state->y[0], state->x[0], state->y[0] - 1);
#ifdef DEBUG
	print_state(state);
#else
	putchar('l');
#endif
}

int main(void) {
	char c;
	int i, j, sum, appeared[10];;
	state_t state_data;
	state_p state = &state_data;

	for (i = 0; i <= 9; ++i) {
		appeared[i] = 0;
	}

	for (i = 0; i < 9; ++i) {
		while ((c = getchar()) == ' ') {
		}
		switch (c) {
		case 'x':
			setxy(i, 0, state);
			break;
		default:
			setxy(i, c - '0', state);
			for (j = c - '0' + 1; j <= 9; ++j) {
				if (appeared[j]) {
					++sum;
				}
				appeared[j] = 1;
			}
		}
	}
#ifdef DEBUG
	print_state(state);
#endif

	if (sum % 2) {
		printf("unsolvable\n");
		return 0;
	}

	if (state->num[2][2] != 0) {
		while (state->x[0] != 2) {
			D
		}
		while (state->y[0] != 2) {
			R
		}
	}

	if (state->num[0][0] != 1) {
		if (state->num[1][1] == 1) {
			ROTATE_B
		}
		while (state->num[0][0] != 1) {
			ROTATE
		}
	}

	if (state->num[0][1] != 2) {
		while (state->y[2] == 0) {
			ROTATE_B
		}
		while (state->num[0][1] != 2) {
			ROTATE_R
		}
	}

	if (state->num[0][2] != 3) {
		while (state->num[1][2] != 3) {
			ROTATE_B
		}
		L L U U R R D L U L D R R D
	}

	while (state->num[1][0] != 4) {
		ROTATE_B
	}

	if (state->num[2][0] == 5) {
		L L U R D R U L L D R U R D
	} else {
		while (state->num[1][1] != 5) {
			ROTATE_C
		}
	}

	if (state->num[1][2] != 6) {
		L L U R D R
		while (state->num[1][1] != 6) {
			ROTATE_C
		}
		ROTATE_B
	}

#ifdef DEBUG
#else
	putchar('\n');
#endif
	return 0;
}
