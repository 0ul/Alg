#include <queue>
#include <cstdio>
using namespace std;

struct cell {
	int y;
	int x;
	int life;
	int time;
	cell(int yy, int xx, int c, int t) {
		y = yy; x = xx; life = c; time = t;
	}
	friend bool operator<(cell a, cell b) {
		if (a.time == b.time)
			return a.life < b.life;
		return a.time > b.time;
	}
};
int map[800][800];
int T, X, Y, K;
int xx[4] = { 0,0,-1,1 };
int yy[4] = { -1,1,0,0 };
priority_queue<cell> q;

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d%d%d", &Y, &X, &K);
		for (int i = 400; i < 400 + Y; i++) {
			for (int j = 400; j < 400 + X; j++) {
				scanf("%d", &map[i][j]);
				if (map[i][j] > 0) {
					cell tmp(i, j, map[i][j], map[i][j] + 1);
					q.push(tmp);
				}
			}
		}
		int clock = 0, ny, nx;
		while (clock <= K) {
			while (!q.empty() && q.top().time == clock) {
				ny = q.top().y;
				nx = q.top().x;
				if (q.top().life > 0) {
					for (int i = 0; i < 4; i++) {
						ny += yy[i];	nx += xx[i];
						if (map[ny][nx] == 0) {
							map[ny][nx] = q.top().life;
							cell tmp(ny, nx, map[ny][nx], clock + map[ny][nx] + 1);
							q.push(tmp);
						}
						ny -= yy[i];	nx -= xx[i];
					}
					cell tmp(ny, nx, 0, clock + q.top().life - 1);
					q.push(tmp);
				}
				else {
					map[ny][nx] = -1;
				}
				q.pop();
			}
			clock++;
		}
		int ans = 0;
		for (int i = 0; i < 800; i++) {
			for (int j = 0; j < 800; j++) {
				if (map[i][j] == 0)	continue;
				if (map[i][j] != -1)
					ans++;
				map[i][j] = 0;
			}
		}
		while(!q.empty())
			q.pop();
		printf("#%d %d\n", tc, ans);
	}
	return 0;
}