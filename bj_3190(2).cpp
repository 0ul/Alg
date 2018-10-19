//using deque
#include <cstdio>
#include <deque>
using namespace std;

int N, K, L, a, b;
char c;
int map[100][100];
int xx[4] = { 1,0,-1,0 };
int yy[4] = { 0,1,0,-1 };
deque<pair<int, int>> inst;
deque<pair<int, int>> snake;

int main() {
	scanf("%d%d", &N, &K);
	for (int i = 0; i < K; i++) {
		scanf("%d%d", &a, &b);
		map[a - 1][b - 1] = 2;
	}
	scanf("%d", &L);
	for (int i = 0; i < L; i++) {
		scanf("%d %c", &a, &c);
		if (c == 'D')	b = 0;	//오른쪽 0
		else b = 1;
		inst.push_back(make_pair(a, b));
	}
	snake.push_back(make_pair(0, 0));
	map[0][0] = 1;
	int clock = 0; int ny, nx, dir = 0;
	
	while (1) {
		clock++;
		ny = snake.front().first + yy[dir];
		nx = snake.front().second + xx[dir];
		if (ny < 0 || nx < 0 || ny >= N || nx >= N || map[ny][nx] == 1)
			break;
		if (map[ny][nx] == 0) {	//사과
			map[snake.back().first][snake.back().second] = 0;
			snake.pop_back();
		}
		map[ny][nx] = 1;
		snake.push_front(make_pair(ny, nx));
		
		if (!inst.empty() && inst.front().first == clock) {
			if (inst.front().second == 0)
				dir = (dir + 1) % 4;
			else {
				dir -= 1;
				if (dir == -1)
					dir = 3;
			}
			inst.pop_front();
		}
	}
	printf("%d\n", clock);
}