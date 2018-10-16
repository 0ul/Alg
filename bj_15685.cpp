#include <cstdio>
#include<vector>
#include <math.h>
using namespace std;


int xx[4] = { 1,0,-1,0 };
int yy[4] = { 0,-1,0,1 };
int map[101][101] = { 0, };

struct xy {
	int x;
	int y;
	xy() {}
	xy(int a, int b) {
		x = a;
		y = b;
	}
};

struct curve {
	xy b;	//begin
	xy e;	//end
	int dir;
	int gen;
	curve() {}
	curve(int x, int y, int d, int g) {
		b.x = x;
		b.y = y;
		dir = d;
		gen = g;
	}
	void setend() {
		e.x = b.x + xx[dir];
		e.y = b.y + yy[dir];
	}
	void bydir() {
		int temp = -1 * b.y;
		b.y = b.x;
		b.x = temp;
	}
	void chk() {
		map[b.y][b.x] = 1;
	}
};

int N, x, y, d, g;
vector<curve> input, cv;


void makecurve(curve start) {
	cv.clear();
	cv.resize(pow(2, start.gen));
	curve temp = start;
	temp.setend();
	cv[0] = temp;
	cv[0].chk();
	int i;
	for (int g = 0; g < start.gen; g++) {
		i = pow(2, g);
		for (int j = pow(2, g) - 1; j >= 0; j--) {
			temp = cv[j];
			temp.b = cv[i - 1].e;
			temp.dir = (temp.dir + 1) % 4;
			temp.setend();
			temp.chk();
			cv[i] = temp;
			i++;
		}
	}
	map[temp.e.y][temp.e.x] = 1;
}


int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d%d%d%d", &x, &y, &d, &g);
		curve tmp(x, y, d, g);
		input.push_back(tmp);
	}
	for (int i = 0; i < N; i++) {
		makecurve(input[i]);
	}

	int total = 0;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (map[i][j] == 1 && map[i + 1][j] == 1 && map[i][j + 1] == 1 && map[i + 1][j + 1] == 1)
				total++;
		}
	}
	printf("%d\n", total);
	return 0;
}