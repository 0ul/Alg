#include <cstdio>
#include <vector>
using namespace std;

int xx[4] = { 0,1,0,-1 };
int yy[4] = { -1,0,1,0 };
int map[50][50];

struct info {
	int y;
	int x;
	int d;	// 0인 경우에는 북쪽을, 1인 경우에는 동쪽을, 2인 경우에는 남쪽을, 3인 경우에는 서쪽
	bool stop = false;
	void set(int yy, int xx, int dir) {
		y = yy;
		x = xx;
		d = dir;
	}
	void turn() {	//회전
		if (d == 0)
			d = 3;
		else
			d -= 1;
	}
	void backturn() {	//회전 복구
		if (d == 3)
			d = 0;
		else
			d += 1;
	}
	void move() {
		y += yy[d];
		x += xx[d];
	}
	void backmove() {	//움직임 복구
		y -= yy[d];
		x -= xx[d];
	}
	void cleanup() {
		map[y][x] = 2;
	}
};

int X, Y, a, b, c, ans = 0;
info robot;

int main() {
	scanf("%d %d", &Y, &X);
	scanf("%d %d %d", &a, &b, &c);
	robot.set(a, b, c);
	for (int i = 0; i < Y; i++) {
		for (int j = 0; j < X; j++) {
			scanf("%d", &map[i][j]);
		}
	}

	/*printf("-----------\n");
	for (int i = 0; i < Y; i++) {
	for (int j = 0; j < X; j++) {
	printf("%d ", map[i][j]);
	}printf("\n");
	}*/

	int cnt = 0;
	while (!robot.stop) {
		if (cnt == 0)
			robot.cleanup();	//현재 위치를 청소한다
		robot.turn();	//현재 위치에서 현재 방향을 기준으로 왼쪽방향부터 차례대로 탐색을 진행한다.
		robot.move();
		if (map[robot.y][robot.x] == 0) {	//왼쪽 방향에 아직 청소하지 않은 공간이 존재한다면
			cnt = 0;			//그 방향으로 회전한 다음 한 칸을 전진하고 1번부터 진행한다.
		}
		else {
			if (cnt == 4) {		//네 방향 모두 청소가 이미 되어있거나 벽인 경우에는, 
				robot.backmove();
				robot.backturn();
				robot.backmove();	//바라보는 방향을 유지한 채로 한 칸 후진을 하고 2번으로 돌아간다
				if (map[robot.y][robot.x] == 1)	//, 뒤쪽 방향이 벽이라 후진도 할 수 없는 경우에는 작동을 멈춘다.
					robot.stop = true;
				else
					cnt = 0;
			}
			else {			//왼쪽 방향에 청소할 공간이 없다면, 그 방향으로 회전하고 2번으로 돌아간다
				cnt++;
				robot.backmove();
			}
		}
	}
	for (int i = 0; i < Y; i++) {
		for (int j = 0; j < X; j++) {
			if (map[i][j] == 2)
				ans++;
		}
	}
	printf("%d\n", ans);
	return 0;
}