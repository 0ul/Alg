// 2105. [모의 SW 역량테스트] 디저트 카페

#include <cstdio>
#include <vector>
using namespace std;

int T, N, ans;
int map[20][20];
int xx[4] = { 1,1,-1,-1 };
int yy[4] = { -1,1,1,-1 };
vector<int> desert;

void dfs(int dir, int cnt, int y, int x, int sy, int sx) {
	if (dir >= 4) {
		if (y == sy && x == sx) {
			if (ans < cnt)
				ans = cnt;
		}
		return;
	}

	int ny = y, nx = x;
	ny += yy[dir];
	nx += xx[dir];
	if (ny < 0 || nx < 0 || ny >= N || nx >= N)
		return;
	if (dir == 3 && ny == sy && nx == sx)
		dfs(4, cnt + 1, ny, nx, sy, sx);
	if (desert[map[ny][nx]] == 1)
		return;
	desert[map[ny][nx]] = 1;
	dfs(dir, cnt + 1, ny, nx, sy, sx);
	dfs(dir + 1, cnt + 1, ny, nx, sy, sx);
	desert[map[ny][nx]] = 0;
}

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &map[i][j]);
			}
		}

		desert.clear(); desert.resize(101);
		ans = -1;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (i == 0 || i == N - 1 || j == N - 1)
					continue;
				desert[map[i][j]] = 1;
				dfs(0, 0, i, j, i, j);
				desert[map[i][j]] = 0;
			}
		}
		printf("#%d %d\n", tc, ans);
	}
	return 0;
}