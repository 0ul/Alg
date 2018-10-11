#include <cstdio>

struct xy {
	int y;
	int x;
	xy(int a, int b) {
		y = a;
		x = b;
	}
};

int X, Y, K, xx, yy, ans;
int map[32][11] = { 0, };

bool chk() {
	for (int i = 1; i <= X; i++) {
		xy cur(1, i);
		while (cur.y <= Y) {
			if (map[cur.y][cur.x] == 1)
				cur.x++;
			else if (map[cur.y][cur.x] == -1)
				cur.x--;
			cur.y++;
		}
		if (cur.x != i)
			return false;
	}
	return true;
}

void dfs(int cnt, int x, int y) {
	if (cnt > 3 || cnt >= ans)	return;
	if (x > X || y > Y)	return;
	if (chk()) {
		if (cnt < ans)
			ans = cnt;
		return;
	}

	for (int i = y; i <= Y; i++) {
		for (int j = 1; j < X; j++) {
			if (i == y && j <= x)	//나보다 위에 생긴건 알 필요없다
				continue;
			if (map[i][j] == 0 && map[i][j + 1] == 0) {
				map[i][j] = 1;	map[i][j + 1] = -1;
				dfs(cnt + 1, j, i);
				map[i][j] = 0;	map[i][j + 1] = 0;
			}
		}
	}
}

int main() {
	scanf("%d%d%d", &X, &K, &Y);
	for (int i = 0; i < K; i++) {
		scanf("%d%d", &yy, &xx);
		map[yy][xx] = 1;
		map[yy][xx + 1] = -1;
	}
	ans = 4;
	
	dfs(0, 1, 1);

	if (ans == 4)
		ans = -1;
	printf("%d\n", ans);
	return 0;
}