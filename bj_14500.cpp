#include <cstdio>
#include <vector>
using namespace std;

int map[500][500];
int v[500][500];
int X, Y, ans;
int xx[4] = { 1,0,-1,0 };
int yy[4] = { 0,-1,0,1 };	

void dfs(int cnt, int score, int y, int x) {
	if (cnt >= 4) {
		if (ans < score)
			ans = score;
		return;
	}
	int ny, nx;
	for (int i = 0; i < 4; i++) {
		ny = y + yy[i];
		nx = x + xx[i];
		if (nx < 0 || ny < 0 || ny >= Y || nx >= X)
			continue;
		if (v[ny][nx] == 0) {
			v[ny][nx] = 1;
			dfs(cnt + 1, score + map[ny][nx], ny, nx);
			v[ny][nx] = 0;
		}
	}
}

int main() {
	scanf("%d %d", &Y, &X);
	for (int i = 0; i < Y; i++) {
		for (int j = 0; j < X; j++) {
			scanf("%d", &map[i][j]);
		}
	}
	
	for (int i = 0; i < Y; i++) {
		for (int j = 0; j < X; j++) {
			v[i][j] = 1;
			dfs(1, map[i][j], i, j);
			v[i][j] = 0;
		}
	}

	int cnt = 0;
	for (int i = 0; i < Y - 1; i++) {
		for (int j = 0; j < X - 2; j++) {
			cnt = map[i][j] + map[i][j + 1] + map[i][j + 2] + map[i + 1][j + 1];	//ぬ
			if (ans < cnt)
				ans = cnt;
			cnt = map[i+1][j] + map[i+1][j + 1] + map[i+1][j + 2] + map[i][j + 1];	//で
			if (ans < cnt)
				ans = cnt;
		}
	}
	for (int i = 0; i < Y - 2; i++) {
		for (int j = 0; j < X - 1; j++) {
			cnt = map[i][j] + map[i + 1][j] + map[i + 1][j + 1] + map[i + 2][j];	//た
			if (ans < cnt)
				ans = cnt;
			cnt = map[i][j + 1] + map[i + 1][j + 1] + map[i + 2][j + 1] + map[i + 1][j];	//っ
			if (ans < cnt)
				ans = cnt;
		}
	}

	printf("%d\n", ans);
	return 0;
}