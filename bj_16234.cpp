#include <cstdio>
#include <cstdlib>
#include <deque>
using namespace std;

int map[50][50], v[50][50];
int xx[4] = { 0,1,0,-1 };
int yy[4] = { -1,0,1,0 };
int N, L, R, cx, cy, nx, ny;
bool is;
deque<pair<int, int>> un, mv;

int main() {
	//freopen("input.txt", "r", stdin);

	scanf("%d%d%d", &N, &L, &R);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			scanf("%d", &map[i][j]);
	}

	int cnt = 0, cmp;
	while (1) {
		cmp = 1;
		for (int i = 0; i < N; i++) {		//인구이동 가능한 나라 찾기
			for (int j = 0; j < N; j++) {
				if (v[i][j] != 0)
					continue;
				un.push_back(make_pair(i, j));
				is = false;
				while (!un.empty()) {
					cy = un.front().first;
					cx = un.front().second;
					for (int k = 0; k < 4; k++) {
						ny = cy + yy[k];
						nx = cx + xx[k];
						if (ny < 0 || nx < 0 || ny >= N || nx >= N || v[ny][nx] != 0)
							continue;
						int tmp = abs(map[ny][nx] - map[cy][cx]);
						if (L <= tmp && tmp <= R) {
							is = true;
							v[ny][nx] = cmp;
							un.push_back(make_pair(ny, nx));
						}
					}
					un.pop_front();
				}
				if (is) {
					v[i][j] = cmp;
					cmp++;
				}
			}
		}
		/*for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				printf("%d ", v[i][j]);
			}
			printf("\n");
		}*/
		int sum;
		is = false;
		for (int i = 0; i < N; i++) {		//인구이동
			for (int j = 0; j < N; j++) {
				if (v[i][j] == 0)
					continue;
				is = true;
				un.push_back(make_pair(i, j));
				mv.push_back(make_pair(i, j));
				sum = map[i][j];
				cmp = v[i][j];
				v[i][j] = 0;
				while (!un.empty()) {
					cy = un.front().first;
					cx = un.front().second;
					for (int k = 0; k < 4; k++) {
						ny = cy + yy[k];
						nx = cx + xx[k];
						if (ny < 0 || nx < 0 || ny >= N || nx >= N)
							continue;
						if (v[ny][nx] == cmp) {
							v[ny][nx] = 0;
							sum += map[ny][nx];
							un.push_back(make_pair(ny, nx));
							mv.push_back(make_pair(ny, nx));
						}
					}
					un.pop_front();
				}
				
				sum /= mv.size();
				while (!mv.empty()) {
					map[mv.front().first][mv.front().second] = sum;
					mv.pop_front();
				}

			}
		}
		if (!is)
			break;
		cnt++;
		/*printf("---- %d ----\n", cnt);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				printf("%d ", map[i][j]);
			}
			printf("\n");
		}
		printf("\n");*/
	}

	printf("%d\n", cnt);
	return 0;
}