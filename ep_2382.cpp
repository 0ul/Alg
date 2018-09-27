//2382. [모의 SW 역량테스트] 미생물 격리
#include <cstdio>
#include <vector>
using namespace std;

struct info {
	int x;
	int y;
	int dir;
	int num;
	info(int a, int b, int c, int d) {
		y = a;
		x = b;
		num = c;
		dir = d;
	}
	friend bool operator!=(info a, info b) {
		return (a.dir != b.dir || a.num != b.num);
	}
};
int T, N, M, K;
int a, b, c, d;
int yy[5] = { 0,-1,1,0,0 };	//상하좌우
int xx[5] = { 0,0,0,-1,1 };
info null(0, 0, 0, 0);
vector<info> v;
int map[100][100];

int nextdir(int dir) {
	if (dir == 1)
		return 2;
	else if (dir == 2)
		return 1;
	else if (dir == 3)
		return 4;
	else
		return 3;
}

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		v.clear();

		scanf("%d%d%d", &N, &M, &K);
		for (int i = 0; i < K; i++) {
			scanf("%d%d%d%d", &a, &b, &c, &d);
			info nfo(a, b, c, d);
			v.push_back(nfo);
		}

		int clock = 0;
		while (clock < M) {
			clock++;

			for (int i = 0; i < v.size(); i++) {
				if (v[i].num != 0) {//살아있으면
					v[i].y += yy[v[i].dir];
					v[i].x += xx[v[i].dir];

					if (v[i].y == 0 || v[i].x == 0 || v[i].y == N - 1 || v[i].x == N - 1) {	//약
						v[i].num = v[i].num / 2;
						v[i].dir = nextdir(v[i].dir);
					}
					map[v[i].y][v[i].x]++;
				}
			}

			for (int i = 1; i < N - 1; i++) {
				for (int j = 1; j < N - 1; j++) {
					if (map[i][j] == 0)	//빈 자리
						continue;

					if (map[i][j] > 1) {	//군집이 두개 이상만났을경우
						info tmp(i, j, 0, 0);
						int highnum = 0;
						for (int k = 0; k < v.size(); k++) {
							if (v[k].num == 0)
								continue;
							if (v[k].y == i && v[k].x == j) {
								if (v[k].num > highnum) {
									highnum = v[k].num;
									tmp.dir = v[k].dir;
								}
								tmp.num += v[k].num;
								v[k].num = 0;
							}
						}
						v.push_back(tmp);	//합쳐진 군집
					}
					map[i][j] = 0;
				}
			}
		}

		int answer = 0;
		for (int i = 0; i < v.size(); i++)
			answer += v[i].num;

		printf("#%d %d\n", tc, answer);
	}

	return 0;
}