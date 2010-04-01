/*
 * main.c
 *
 *  Created on: Mar 31, 2010
 *      Author: XTOg
 */

#include <stdio.h>

#define MAXN 64
#define MAXL 15

typedef struct node *nodeptr;
typedef struct node node_t;
struct node {
	char name[MAXL + 1];
	nodeptr next;
};

int main(void) {
	int n;
	int i, j;
	int w, s;
	node_t child[MAXN];
	nodeptr p;

	scanf("%d", &n);
	for (i = 0; i < n; ++i) {
		scanf("%s", child[i].name);
		child[i].next = child + (i + 1) % n;
	}
	scanf("%d,%d", &w, &s);

	p = child + (w - 1 + n - 1) % n;
	for (i = 0; i < n; ++i) {
		for (j = 0; j < s - 1; ++j) {
			p = p->next;
		}
		printf("%s\n", p->next->name);
		p->next = p->next->next;
	}
	return 0;
}

