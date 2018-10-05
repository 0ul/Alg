// 3190 뱀

#include <cstdio>
#include <queue>
using namespace std;

struct xy {
	int y;
	int x;
	void set(int i, int j) {
		y = i;
		x = j;
	}
};
struct info {
	int t;
	int dir;	//0이면	반시계 1이면 시계방향
	info(int x, int y) {
		t = x;
		dir = y;
	}
};

int turn(int clockwise, int curdir) {
	if (clockwise == 0) {	//반시계
		if (curdir == 0)
			return 3;
		return curdir - 1;
	}
	else {					//시계방향
		if (curdir == 3)
			return 0;
		return curdir + 1;
	}
}

int N, K, L, a, b;
char c;
int map[102][102];
int xx[4] = { 1,0,-1,0 };
int yy[4] = { 0,1,0,-1 };
queue<info> q;
queue<xy> tail;

int main(){
	scanf("%d %d", &N, &K);
	for (int i = 0; i < K; i++) {
		scanf("%d %d", &a, &b);
		map[a][b] = 2;	//사과 : 2
	}
	
	scanf("%d", &L);
	for (int i = 0; i < L; i++) {
		scanf("%d %c", &a, &c);
		if (c == 'L')
			b = 0;
		else
			b = 1;
		info in(a, b);
		q.push(in);
	}

	for (int i = 0; i <= N; i++){
		map[0][i] = -1;		//벽
		map[N+1][i] = -1;
		map[i][0] = -1;
		map[i][N+1] = -1;
	}

	int clock = 0, ny = 1, nx = 1, curdir = 0, tx = 1, ty = 1;
	info next = q.front(); xy tt;
	map[1][1] = 1;
	while (1) {
		clock++;
		nx += xx[curdir];
		ny += yy[curdir];

		if (map[ny][nx] == 1 || map[ny][nx] == -1)	//자기자신이나 벽 만날 경우 종료
			break;
		
		tt.set(ny, nx);
		tail.push(tt);

		if (map[ny][nx] == 0) {	//사과 없을 경우 꼬리 없애기
			map[ty][tx] = 0;
			tt = tail.front();
			tail.pop();
			tx = tt.x;
			ty = tt.y;
		}
		
		map[ny][nx] = 1;

		if (clock == next.t) {
			curdir = turn(next.dir, curdir);
			q.pop();
			if (!q.empty()) {
				next = q.front();
			}
		}

	}
	
	printf("%d\n", clock);

	return 0;
}