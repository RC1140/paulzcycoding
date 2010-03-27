/*
 * main.c
 *
 *  Created on: Mar 27, 2010
 *      Author: XTOg
 */

#include <stdio.h>
#include <string.h>

#define MAXH 20
#define MAXW 20

void dfs(int x, int y, int *l, int w, int h, char map[MAXH][MAXW + 1],
		int visited[MAXH][MAXW]) {
	static const int dx[] = { 0, 1, 0, -1 }, dy[] = { 1, 0, -1, 0 };
	int i;
	int nx, ny;
	for (i = 0; i < 4; ++i) {
		nx = x + dx[i];
		ny = y + dy[i];
		if (nx < 0 || nx >= h || ny < 0 || ny >= w || visited[nx][ny]
				|| map[nx][ny] == '#') {
			continue;
		}
		visited[nx][ny] = 1;
		(*l) += 1;
		dfs(nx, ny, l, w, h, map, visited);
	}
}

int main(void) {
	int w, h;
	char map[MAXH][MAXW + 1];
	int visited[MAXH][MAXW];
	int i, j;
	int x, y;
	int l;

	while (1) {
		scanf("%d%d", &w, &h);
		if (!w) {
			break;
		}

		for (i = 0; i < h; ++i) {
			scanf("%s", map[i]);
			for (j = 0; j < w; ++j) {
				if (map[i][j] == '@') {
					x = i;
					y = j;
					break;
				}
			}
		}

		memset(visited, 0, sizeof(visited));
		visited[x][y] = 1;
		l = 1;
		dfs(x, y, &l, w, h, map, visited);

		printf("%d\n", l);
	}
	return 0;
}
