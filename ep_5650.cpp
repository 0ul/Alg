//5650 핀볼 게임

#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

struct xy {
	int x;
	int y;

	xy() {
		x = -1; y = -1;
	}
	xy(int b, int a) {
		y = b; x = a;
	}

	friend bool operator == (xy i, xy j) {
		return bool(i.x == j.x && i.y == j.y);
	}
};

struct hole {
	xy a;
	xy b;
	xy go(xy from) {
		if (from == a)	//a들어오면 b로
			return b;
		else			//b들어오면 a로
			return a;
	}
	hole(){
		a = xy();
		b = xy();
	}
};

int T, N;
int map[100][100];
queue<xy> q;	//시작점 좌표
vector<hole> h(5);	//웜홀
xy start, cmp;
int temp, score, dir;

int meet(int blocknum) {	// 블록 만나면 방향 바꿔줌 v=1 >=2 ^=3 <=4
	switch (blocknum)
	{
	case 1:	
		if (dir == 1)	return 2;
		if (dir == 2)	return 4;
		if (dir == 3)	return 1;
		if (dir == 4)	return 3;
	case 2:	
		if (dir == 1)	return 3;
		if (dir == 2)	return 4;
		if (dir == 3)	return 2;
		if (dir == 4)	return 1;
	case 3:
		if (dir == 1)	return 3;
		if (dir == 2)	return 1;
		if (dir == 3)	return 4;
		if (dir == 4)	return 2;
	case 4:
		if (dir == 1)	return 4;
		if (dir == 2)	return 3;
		if (dir == 3)	return 1;
		if (dir == 4)	return 2;
	case 5:
		if (dir == 1)	return 3;
		if (dir == 2)	return 4;
		if (dir == 3)	return 1;
		if (dir == 4)	return 2;
	}
}

int move() {
	int scr = 0;
	int x = start.x;
	int y = start.y;
	if (dir == 1)
		y++;
	else if (dir == 2)
		x++;
	else if (dir == 3)
		y--;
	else
		x--;

	while (1) {
		if (dir == 1) {	//down
			while (y < N) {
				if (map[y][x] == -1 || (x == start.x && y == start.y))
					return scr;
				else if (map[y][x] > 5) {
					
					xy tmp(y, x);
					tmp = h[map[y][x] - 6].go(tmp);
					x = tmp.x;
					y = tmp.y;
				}
				else if (map[y][x] > 0) {
					scr++;
					dir = meet(map[y][x]);
					if (dir == 1)
						y++;
					else if (dir == 2)
						x++;
					else if (dir == 3)
						y--;
					else
						x--;
					break;
				}
				y++;
			}
			if (y == N) {
				scr++;
				y = N - 1;
				dir = 3;
			}
		}
		else if (dir == 2) {
			while (x < N) {
				if (map[y][x] == -1 || (x == start.x && y == start.y))
					return scr;
				else if (map[y][x] > 5) {
					xy tmp(y, x);
					tmp = h[map[y][x] - 6].go(tmp);
					x = tmp.x;
					y = tmp.y;
				}
				else if (map[y][x] > 0) {
					scr++;
					dir = meet(map[y][x]);
					if (dir == 1)
						y++;
					else if (dir == 2)
						x++;
					else if (dir == 3)
						y--;
					else
						x--;
					break;
				}
				x++;
			}
			if (x == N) {
				scr++;
				x = N - 1;
				dir = 4;
			}
		}
		else if (dir == 3) {	//up
			while (y >= 0 ) {
				if (map[y][x] == -1 || (x == start.x && y == start.y))
					return scr;
				else if (map[y][x] > 5) {
					xy tmp(y, x);
					tmp = h[map[y][x] - 6].go(tmp);
					x = tmp.x;
					y = tmp.y;
				}
				else if (map[y][x] > 0) {
					scr++;
					dir = meet(map[y][x]);
					if (dir == 1)
						y++;
					else if (dir == 2)
						x++;
					else if (dir == 3)
						y--;
					else
						x--;
					break;
				}
				y--;
			}
			if (y == -1) {
				scr++;
				y = 0;
				dir = 1;
			}
		}
		else {
			while (x >= 0) {
				if (map[y][x] == -1 || (x == start.x && y == start.y))
					return scr;
				else if (map[y][x] > 5) {
					xy tmp(y, x);
					tmp = h[map[y][x]-6].go(tmp);
					x = tmp.x;
					y = tmp.y;
				}
				else if (map[y][x] > 0) {
					scr++;
					dir = meet(map[y][x]);
					if (dir == 1)
						y++;
					else if (dir == 2)
						x++;
					else if (dir == 3)
						y--;
					else
						x--;
					break;
				}
				x--;
			}
			if (x == -1) {
				scr++;
				x = 0;
				dir = 2;
			}

		}
	}
}



int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {

		//init
		for (int i = 0; i < 5; i++) {
			h[i].a = xy(-1, -1);
			h[i].b = xy(-1, -1);
		}
		score = 0;
		

		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &map[i][j]);
				
				if (map[i][j] == 0) {	//시작 가능
					xy tmp(i, j);
					q.push(tmp);
				}
				if (map[i][j] > 5) {	//웜홀
					xy tmp(i, j);
					if (h[map[i][j] - 6].a == cmp)
						h[map[i][j] - 6].a = tmp;
					else {
						h[map[i][j] - 6].b = tmp;
					}
				}
			}
		}

		while (!q.empty()) {
			start = q.front();
			q.pop();
			for (int i = 1; i < 5; i++) {	//같은 출발지점이라도 방향 달리 해봐야
				dir = i;
				temp = move();
				if (score < temp)
					score = temp;
			}
		}

		printf("#%d %d\n", tc, score);
	}
}