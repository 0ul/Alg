//14500 테트로미노

#include <cstdio>

int tet32[8][3][2] = { { { 1,0 },{ 1,0 },{ 1,1 } },{ { 0,1 },{ 0,1 },{ 1,1 } },
{ { 1,1 },{ 1,0 },{ 1,0 } },{ { 1,1 },{ 0,1 },{ 0,1 } },
{ { 1,0 },{ 1,1 },{ 0,1 } },{ { 0,1 },{ 1,1 },{ 1,0 } },
{ { 1,0 },{ 1,1 },{ 1,0 } },{ { 0,1 },{ 1,1 },{ 0,1 } } };

int tet23[8][2][3] = { { { 1,0,0 },{ 1,1,1 } },{ { 1,1,1 },{ 1,0,0 } },
{ { 1,1,1 },{ 0,0,1 } },{ { 0,0,1 },{ 1,1,1 } },
{ { 1,1,0 },{ 0,1,1 } },{ { 0,1,1 },{ 1,1,0 } },
{ { 1,1,1 },{ 0,1,0 } },{ { 0,1,0 },{ 1,1,1 } } };

int X, Y;
int map[500][500];

int main() {
	scanf("%d %d", &Y, &X);
	for (int i = 0; i < Y; i++) {
		for (int j = 0; j < X; j++) {
			scanf("%d", &map[i][j]);
		}
	}

	int ans = 0; int tmp = 0;
	for (int i = 0; i < Y; i++) {	//1x4
		for (int j = 0; j < X - 3; j++) {
			tmp = map[i][j] + map[i][j + 1] + map[i][j + 2] + map[i][j + 3];
			if (tmp > ans)
				ans = tmp;
		}
	}
	for (int i = 0; i < X; i++) {	//4x1
		for (int j = 0; j < Y - 3; j++) {
			tmp = map[j][i] + map[j + 1][i] + map[j + 2][i] + map[j + 3][i];
			if (tmp > ans)
				ans = tmp;
		}
	}
	for (int i = 0; i < Y - 1; i++) {	//2x2
		for (int j = 0; j < X - 1; j++) {
			tmp = map[i][j] + map[i][j + 1] + map[i + 1][j] + map[i + 1][j + 1];
			if (tmp > ans)
				ans = tmp;
		}
	}


	for (int i = 0; i < Y - 2; i++) {	//3x2
		for (int j = 0; j < X - 1; j++) {
			for (int type = 0; type < 8; type++) {
				tmp = map[i][j] * tet32[type][0][0] + map[i][j + 1] * tet32[type][0][1]
					+ map[i + 1][j] * tet32[type][1][0] + map[i + 1][j + 1] * tet32[type][1][1]
					+ map[i + 2][j] * tet32[type][2][0] + map[i + 2][j + 1] * tet32[type][2][1];
				if (tmp > ans)
					ans = tmp;
			}
		}
	}

	for (int i = 0; i < Y - 1; i++) {	//2x3
		for (int j = 0; j < X - 2; j++) {
			for (int type = 0; type < 8; type++) {
				tmp = map[i][j] * tet23[type][0][0] + map[i][j + 1] * tet23[type][0][1] + map[i][j + 2] * tet23[type][0][2]
					+ map[i + 1][j] * tet23[type][1][0] + map[i + 1][j + 1] * tet23[type][1][1] + map[i + 1][j + 2] * tet23[type][1][2];
				if (tmp > ans)
					ans = tmp;
			}
		}
	}


	printf("%d\n", ans);
	return 0;

}