//5644. [모의 SW 역량테스트] 무선 충전

#include <cstdio>

struct xy {
	int y;
	int x;
	xy(int b, int a) {
		y = b; x = a;
	}
	friend bool operator==(xy a, xy b) {
		return (a.x == b.x && a.y == b.y);
	}
};

int T, TIME, BC;
int y, x, c, p;
int map[10][10][8];
int mx[4] = { 1,1,-1,-1 };
int my[4] = { 1,-1,1,-1 };
int move[2][100];
int xx[5] = { 0,0,1,0,-1 };
int yy[5] = { 0,-1,0,1,0 };
int isuse[2][8], idx[2];
int perf[8];

void makespcae(int y, int x, int coverage, int performance, int bcnum) {	//무선 충전 영역 설정
	int ny, nx;
	for (int i = 0; i <= coverage; i++) {
		for (int j = 0; j <= coverage - i; j++) {
			for (int k = 0; k < 4; k++) {
				ny = y + my[k] * i;
				nx = x + mx[k] * j;
				if (ny < 0 || nx < 0 || ny>9 || nx>9)
					continue;
				map[ny][nx][bcnum] = 1;
			}
		}
	}
}


int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d", &TIME, &BC);
		for (int i = 0; i < TIME; i++) {
			scanf("%d", &move[0][i]);
		}
		for (int i = 0; i < TIME; i++) {
			scanf("%d", &move[1][i]);
		}
		for (int i = 0; i < BC; i++) {
			scanf("%d %d %d %d", &x, &y, &c, &p);
			makespcae(y - 1, x - 1, c, p, i);
			perf[i] = p;
		}

		xy cur[2] = { { 0,0 } ,{ 9,9 } };	//초기 위치 설정
		int clock = 0, total = 0, tmp = 0;

		while (clock <= TIME) {
			int high;
			high = idx[0] = idx[1] = 0;

			for (int i = 0; i < BC; i++) {
				if (map[cur[0].y][cur[0].x][i] != 0) {
					isuse[0][idx[0]] = i;
					idx[0]++;
				}
				if (map[cur[1].y][cur[1].x][i] != 0) {
					isuse[1][idx[1]] = i;	//사용가능한지
					idx[1]++;
				}
			}
			if (idx[0] == 0) {
				for (int i = 0; i < idx[1]; i++) {
					if (perf[isuse[1][i]] > high)
						high = perf[isuse[1][i]];
				}
			}
			else if (idx[1] == 0) {
				for (int i = 0; i < idx[0]; i++) {
					if (perf[isuse[0][i]] > high)
						high = perf[isuse[0][i]];
				}
			}
			else {
				for (int i = 0; i < idx[0]; i++) {
					for (int j = 0; j < idx[1]; j++) {
						if (isuse[0][i] == isuse[1][j]) {	//동시에 쓸 경우
							tmp = perf[isuse[0][i]];
						}
						else {
							tmp = perf[isuse[0][i]] + perf[isuse[1][j]];
						}
						if (tmp > high)
							high = tmp;
					}
				}
			}
			total += high;

			for (int i = 0; i < 2; i++) {	//위치 갱신
				cur[i].x += xx[move[i][clock]];
				cur[i].y += yy[move[i][clock]];
			}
			clock++;
		}

		printf("#%d %d\n", tc, total);
		for (int k = 0; k < BC; k++) {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					map[i][j][k] = 0;
				}
			}
		}
	}
	return 0;
}