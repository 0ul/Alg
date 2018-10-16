#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

struct xy {
	int y;
	int x;
	xy(int yy, int xx) {
		y = yy;
		x = xx;
	}
};
int X, Y, wall, ans, ny, nx;
int map[8][8], cpy[8][8];
int xx[4] = { 1,-1,0,0 };
int yy[4] = { 0,0,1,-1 };
vector<xy> virus, build;
queue<xy> q;

void copy() {
	for (int i = 0; i < Y; i++) {
		for (int j = 0; j < X; j++) {
			cpy[i][j] = map[i][j];
		}
	}
}

void bfs() {
	int cnt = 0;
	for (int i = 0; i < virus.size(); i++) {
		q.push(virus[i]);
	}
	while (!q.empty()) {
		xy tmp = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			ny = tmp.y + yy[i];
			nx = tmp.x + xx[i];
			if (ny < 0 || nx < 0 || ny >= Y || nx >= X)
				continue;
			if (cpy[ny][nx] == 0) {
				cpy[ny][nx] = 2;
				q.push({ ny,nx });
				cnt++;
			}
		}
	}
	if (ans > cnt)
		ans = cnt;
}

int main() {
	scanf("%d%d", &Y, &X);
	for (int i = 0; i < Y; i++) {
		for (int j = 0; j < X; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 2) {
				xy tmp(i, j);
				virus.push_back(tmp);
			}
			else if (map[i][j] == 1)
				wall++;
		}
	}

	copy();
	for (int i = 0; i < virus.size(); i++) {
		q.push(virus[i]);
	}
	while (!q.empty()) {
		xy tmp = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			ny = tmp.y + yy[i];
			nx = tmp.x + xx[i];
			if (ny < 0 || nx < 0 || ny >= Y || nx >= X)
				continue;
			if (cpy[ny][nx] == 0) {
				cpy[ny][nx] = 3;
				q.push({ ny,nx });
			}
		}
	}

	ans = 0;
	for (int i = 0; i < Y; i++) {
		for (int j = 0; j < X; j++) {
			if (cpy[i][j] == 3) {
				xy tmp(i, j);
				build.push_back(tmp);
				ans++;
			}
		}
	}
	for (int i = 0; i < build.size(); i++) {
		for (int j = i + 1; j < build.size(); j++) {
			for (int k = j + 1; k < build.size(); k++) {
				copy();
				cpy[build[i].y][build[i].x] = 1;
				cpy[build[j].y][build[j].x] = 1;
				cpy[build[k].y][build[k].x] = 1;
				bfs();
			}
		}
	}
	printf("%d\n", X*Y - ans - virus.size() - wall - 3);
	return 0;
}