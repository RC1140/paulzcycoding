/*
 * main.c
 *
 *  Created on: Apr 1, 2010
 *      Author: XTOg
 */

#include <stdio.h>
#include <string.h>

#define MAXN 100

void dfs(int x, int y, int n, int m, char map[MAXN][MAXN + 1],
		int visited[MAXN][MAXN]) {
	static const int dx[] = {1, 0, -1, 0, 1, 1, -1, -1}, dy[] = {0, 1, 0,
		-1, 1, -1, 1, -1};
	int nx, ny;
	int i;

	for (i = 0; i < 8; ++i) {
		nx = x + dx[i];
		ny = y + dy[i];
		if (nx < 0 || ny < 0 || nx == n || ny == m) {
			continue;
		}
		if (map[nx][ny] != '@' || visited[nx][ny]) {
			continue;
		}
		visited[nx][ny] = 1;
		dfs(nx, ny, n, m, map, visited);
	}

}

int main(void) {
	int n, m;
	char map[MAXN][MAXN + 1];
	int visited[MAXN][MAXN];
	int i, j;
	int sum;
	while (1) {
		scanf("%d%d", &n, &m);
		if (n == 0) {
			break;
		}
		for (i = 0; i < n; ++i) {
			scanf("%s", map[i]);
		}

		memset(visited, 0, sizeof(visited));

		sum = 0;
		for (i = 0; i < n; ++i) {
			for (j = 0; j < m; ++j) {
				if (map[i][j] == '@' && !visited[i][j]) {
					visited[i][j] = 1;
					dfs(i, j, n, m, map, visited);
					++sum;
				}
			}
		}

		printf("%d\n", sum);
	}
	return 0;
}
