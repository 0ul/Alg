//1953 Å»ÁÖ¹ü °Ë°Å

#include<cstdio>
#include<queue>
using namespace std;

int T, N, M, R, C, L;
int m[50][50];
int v[50][50];
int xx[7][4] = { { 1,-1,0,0 },{ 0,0,0,0 },{ 1,-1,0,0 },{ 1,0,0,0 },{ 0,1,0,0 },{ -1,0,0,0 } ,{ -1,0,0,0 } };
int yy[7][4] = { { 0,0,1,-1 },{ 1,-1,0,0 },{ 0,0,0,0 },{ 0,-1,0,0 },{ 1,0,0,0 },{ 0,1,0,0 },{ 0,-1,0,0 } };
queue<int> qx, qy;

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d%d%d%d%d", &N, &M, &R, &C, &L);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				v[i][j] = 0;
				scanf("%d", &m[i][j]);
			}
		}

		while (!qx.empty()) {
			qx.pop();
		}
		while (!qy.empty()) {
			qy.pop();
		}

		v[R][C] = 1;
		qy.push(R);
		qx.push(C);

		int x, y, nx, ny, typ;
		while (!qy.empty()) {
			y = qy.front();
			x = qx.front();
			typ = m[y][x] - 1;
			qy.pop(); qx.pop();
			if (v[y][x] > L)
				break;
			for (int i = 0; i < 4; i++) {
				nx = x + xx[typ][i];
				ny = y + yy[typ][i];

				if (ny < 0 || nx < 0 || ny >= N || nx >= M)
					continue;

				if (v[ny][nx] == 0) {
					if (xx[typ][i] == 1) {
						if (m[ny][nx] == 1 || m[ny][nx] == 3 || m[ny][nx] == 6 || m[ny][nx] == 7) {
							v[ny][nx] = v[y][x] + 1;
							qy.push(ny);
							qx.push(nx);
						}
					}
					if (xx[typ][i] == -1) {
						if (m[ny][nx] == 1 || m[ny][nx] == 3 || m[ny][nx] == 4 || m[ny][nx] == 5) {
							v[ny][nx] = v[y][x] + 1;
							qy.push(ny);
							qx.push(nx);
						}
					}
					if (yy[typ][i] == -1) {
						if (m[ny][nx] == 1 || m[ny][nx] == 2 || m[ny][nx] == 5 || m[ny][nx] == 6) {
							v[ny][nx] = v[y][x] + 1;
							qy.push(ny);
							qx.push(nx);
						}
					}
					if (yy[typ][i] == 1) {
						if (m[ny][nx] == 1 || m[ny][nx] == 2 || m[ny][nx] == 4 || m[ny][nx] == 7) {
							v[ny][nx] = v[y][x] + 1;
							qy.push(ny);
							qx.push(nx);
						}
					}
				}
			}
		}

		int cnt = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (v[i][j] > 0 && v[i][j] <= L)
					cnt++;
			}
		}

		printf("#%d %d\n", tc, cnt);
	}
	return 0;
}