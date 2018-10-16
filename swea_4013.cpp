#include <cstdio>
#include <math.h>

struct info {
	int magnum;
	int dir;
};
int T, K, a, b;
int magnet[4][8];
int score[4];
info seq[20];	//회전 정보
void fst(int dir);
void snd(int dir);
void trd(int dir);
void fth(int dir);

void move(int mag, int dir) {
	if (dir == 1) {// 시계방향
		int tmp = magnet[mag][7];
		for (int i = 7; i >= 0; i--) {
			magnet[mag][i] = magnet[mag][i - 1];
		}
		magnet[mag][0] = tmp;
	}
	else {
		int tmp = magnet[mag][0];
		for (int i = 0; i < 7; i++) {
			magnet[mag][i] = magnet[mag][i + 1];
		}
		magnet[mag][7] = tmp;
	}
}


void fst(int dir) {
	if (magnet[0][2] != magnet[1][6]) {
		if (magnet[1][2] != magnet[2][6]) {
			if (magnet[2][2] != magnet[3][6]) {
				move(3, -1 * dir);
			}
			move(2, dir);
		}
		move(1, -1 * dir);
	}
	move(0, dir);
}

void snd(int dir) {
	if (magnet[1][6] != magnet[0][2]) {
		move(0, -1 * dir);
	}
	if (magnet[1][2] != magnet[2][6]) {
		if (magnet[2][2] != magnet[3][6]) {
			move(3, dir);
		}
		move(2, -1 * dir);
	}
	move(1, dir);
}

void trd(int dir) {
	if(magnet[2][2] != magnet[3][6])
		move(3, -1 * dir);
	if (magnet[2][6] != magnet[1][2]) {
		if (magnet[1][6] != magnet[0][2]) {
			move(0, dir);
		}
		move(1, -1 * dir);
	}
	move(2, dir);
}

void fth(int dir) {
	if (magnet[2][2] != magnet[3][6]) {
		if (magnet[1][2] != magnet[2][6]) {
			if (magnet[0][2] != magnet[1][6]) {
				move(0, -1 * dir);
			}
			move(1, dir);
		}
		move(2, -1 * dir);
	}
	move(3, dir);
}

void func(info mag) {
	if (mag.magnum == 1) {
		fst(mag.dir);
	}
	else if (mag.magnum == 2) {
		snd(mag.dir);
	}
	else if (mag.magnum == 3) {
		trd(mag.dir);
	}
	else {
		fth(mag.dir);
	}
}


int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d", &K);
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 8; j++) {
				scanf("%d", &magnet[i][j]);
			}
		}
		for (int x = 0; x < K; x++) {
			scanf("%d %d", &a, &b);
			seq[x].magnum = a;
			seq[x].dir = b;
			func(seq[x]);
			/*printf("--- x ---\n", x);
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 8; j++) {
					printf("%d ", magnet[i][j]);
				}printf("\n");
			}*/
		}

		int total = 0;
		for (int i = 0; i < 4; i++) {
			if (magnet[i][0] == 1)
				total += pow(2, i);
		}

		/*for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 8; j++) {
				printf("%d ", magnet[i][j]);
			}printf("\n");
		}*/
		printf("#%d %d\n", tc, total);
	}
}

//#include <iostream>
//
//using namespace std;
//
//void first(int side);
//void second(int side);
//void third(int side);
//void forth(int side);
//void clock(int *x);
//void unclock(int *x);
//int score(int score);
//
//int a[8] = { 0, };
//int b[8] = { 0, };
//int c[8] = { 0, };
//int d[8] = { 0, };
//
//int main() {
//
//	int i(0), j(0), total(0);
//	int k(0), totalscore(0);
//	int num(0), side(0);
//
//	cin >> total;	//총 테스트 개수
//
//	for (i = 1; i < total + 1; i++) {
//		cin >> k;	//자석 회전 횟수
//
//		for (j = 0; j < 8; j++) {	//자석 정보 입력
//			cin >> a[j];
//		}
//		for (j = 0; j < 8; j++) {
//			cin >> b[j];
//		}
//		for (j = 0; j < 8; j++) {
//			cin >> c[j];
//		}
//		for (j = 0; j < 8; j++) {
//			cin >> d[j];
//		}
//
//		for (j = 0; j < k; j++) {	//회전시키기
//			cin >> num;
//			cin >> side;
//
//			switch (num) {
//			case 1: first(side); break;
//			case 2: second(side); break;
//			case 3: third(side); break;
//			case 4: forth(side); break;
//			}
//
//		}
//
//		totalscore = score(totalscore);	//점수 구하기
//
//		cout << "#" << i << " " << totalscore << endl;	//출력
//
//		totalscore = 0;
//
//	}
//
//	return 0;
//}
//
//void first(int side) {
//	switch (side) {
//	case 1:
//		if (a[2] != b[6]) {
//			if (b[2] != c[6]) {
//				if (c[2] != d[6])
//					unclock(d);
//				clock(c);
//			}
//			unclock(b);
//		}
//		clock(a);
//		break;
//	case -1:
//		if (a[2] != b[6]) {
//			if (b[2] != c[6]) {
//				if (c[2] != d[6])
//					clock(d);
//				unclock(c);
//			}
//			clock(b);
//		}
//		unclock(a);
//
//		break;
//	}
//}
//
//void second(int side) {
//	switch (side) {
//	case 1:
//		if (a[2] != b[6]) {
//			unclock(a);
//		}
//		if (b[2] != c[6]) {
//			if (c[2] != d[6])
//				clock(d);
//			unclock(c);
//		}
//		clock(b);
//		break;
//	case -1:
//		if (a[2] != b[6]) {
//			clock(a);
//		}
//		if (b[2] != c[6]) {
//			if (c[2] != d[6])
//				unclock(d);
//			clock(c);
//		}
//		unclock(b);
//		break;
//	}
//}
//
//void third(int side) {
//	switch (side) {
//	case 1:
//		if (b[2] != c[6]) {
//			if (a[2] != b[6])
//				clock(a);
//			unclock(b);
//		}
//		if (c[2] != d[6])
//			unclock(d);
//		clock(c);
//		break;
//	case -1:
//		if (b[2] != c[6]) {
//			if (a[2] != b[6])
//				unclock(a);
//			clock(b);
//		}
//		if (c[2] != d[6])
//			clock(d);
//		unclock(c);
//		break;
//	}
//}
//
//void forth(int side) {
//	switch (side) {
//	case 1:
//		if (c[2] != d[6]) {
//			if (b[2] != c[6]) {
//				if (a[2] != b[6])
//					unclock(a);
//				clock(b);
//			}
//			unclock(c);
//		}
//		clock(d);
//		break;
//	case -1:
//		if (c[2] != d[6]) {
//			if (b[2] != c[6]) {
//				if (a[2] != b[6])
//					clock(a);
//				unclock(b);
//			}
//			clock(c);
//		}
//		unclock(d);
//		break;
//	}
//}
//
//
//void clock(int *x) {
//	int temp = x[7];
//	x[7] = x[6];
//	x[6] = x[5];
//	x[5] = x[4];
//	x[4] = x[3];
//	x[3] = x[2];
//	x[2] = x[1];
//	x[1] = x[0];
//	x[0] = temp;
//}
//
//void unclock(int *x) {
//	int temp = x[0];
//	x[0] = x[1];
//	x[1] = x[2];
//	x[2] = x[3];
//	x[3] = x[4];
//	x[4] = x[5];
//	x[5] = x[6];
//	x[6] = x[7];
//	x[7] = temp;
//}
//
//int score(int score) {
//	if (a[0] == 1)
//		score += 1;
//	if (b[0] == 1)
//		score += 2;
//	if (c[0] == 1)
//		score += 4;
//	if (d[0] == 1)
//		score += 8;
//
//	return score;
//}