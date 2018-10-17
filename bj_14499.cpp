#include <cstdio>
#include <vector>
using namespace std;

int xx[4] = { 1,-1,0,0 };
int yy[4] = { 0,0,-1,1 };
int X, Y, K, a, b;
int map[20][20];

struct xy{
	int y, x;
	int a;//¸Ç À§
	int b, c, d, e;
	int f;//¹Ù´Ú
	void set(int yy, int xx) {
		y = yy;
		x = xx;
	}
	void east() {
		int tmp = a;
		a = d;
		d = f;
		f = c;
		c = tmp;
	}
	void west() {
		int tmp = a;
		a = c;
		c = f;
		f = d;
		d = tmp;
	}
	void north() {
		int tmp = a;
		a = e;
		e = f;
		f = b;
		b = tmp;
	}
	void south() {
		int tmp = a;
		a = b;
		b = f;
		f = e;
		e = tmp;
	}
	void move(int dir) {
		x += xx[dir];
		y += yy[dir];
		if (x < 0 || y < 0 || x >= X || y >= Y) {
			x -= xx[dir];
			y -= yy[dir];
			return;
		}
		if (dir == 0)
			east();
		else if (dir == 1)
			west();
		else if (dir == 2)
			south();
		else
			north();
		if (map[y][x] == 0)
			map[y][x] = f;
		else {
			f = map[y][x];
			map[y][x] = 0;
		}
		printf("%d\n", a);
	}
};
xy dice;

int main() {
	scanf("%d%d%d%d%d", &Y, &X, &a, &b, &K);
	dice.set(a,b);
	for (int i = 0; i < Y; i++) {
		for (int j = 0; j < X; j++) {
			scanf("%d", &map[i][j]);
		}
	}
	for (int i = 0; i < K; i++) {
		scanf("%d", &a);
		dice.move(a - 1);
	}
	return 0;
}