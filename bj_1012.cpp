#include <cstdio>

int N, M, x, a, b, T;
int G[50][50];
int v[50][50];
int cnt = 0;
int xx[4] = { 1,-1,0,0 };
int yy[4] = { 0,0,1,-1 };

void dfs(int y, int x) {
	int nx, ny;
	v[y][x] = 1;
	for (int i = 0; i < 4; i++) {
		nx = x + xx[i];
		ny = y + yy[i];
		if (nx >= 0 && ny >= 0 && nx < M&&ny < N) {
			if (v[ny][nx] == 0 && G[ny][nx] == 1) {
				dfs(ny, nx);
			}
		}
	}
}
int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d %d", &M, &N, &x);

		for (int i = 0; i < x; i++) {
			scanf("%d %d", &a, &b);
			G[b][a] = 1;
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (v[i][j] == 0 && G[i][j] == 1) {
					cnt++;
					dfs(i, j);
				}
			}
		}

		printf("%d\n", cnt);

		//reset
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				G[i][j] = 0;
				v[i][j] = 0;
			}
		}
		cnt = 0;
	}

	return 0;
}