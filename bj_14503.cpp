#include <cstdio>
#include <vector>
using namespace std;

int xx[4] = { 0,1,0,-1 };
int yy[4] = { -1,0,1,0 };
int map[50][50];

struct info {
	int y;
	int x;
	int d;	// 0�� ��쿡�� ������, 1�� ��쿡�� ������, 2�� ��쿡�� ������, 3�� ��쿡�� ����
	bool stop = false;
	void set(int yy, int xx, int dir) {
		y = yy;
		x = xx;
		d = dir;
	}
	void turn() {	//ȸ��
		if (d == 0)
			d = 3;
		else
			d -= 1;
	}
	void backturn() {	//ȸ�� ����
		if (d == 3)
			d = 0;
		else
			d += 1;
	}
	void move() {
		y += yy[d];
		x += xx[d];
	}
	void backmove() {	//������ ����
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
			robot.cleanup();	//���� ��ġ�� û���Ѵ�
		robot.turn();	//���� ��ġ���� ���� ������ �������� ���ʹ������ ���ʴ�� Ž���� �����Ѵ�.
		robot.move();
		if (map[robot.y][robot.x] == 0) {	//���� ���⿡ ���� û������ ���� ������ �����Ѵٸ�
			cnt = 0;			//�� �������� ȸ���� ���� �� ĭ�� �����ϰ� 1������ �����Ѵ�.
		}
		else {
			if (cnt == 4) {		//�� ���� ��� û�Ұ� �̹� �Ǿ��ְų� ���� ��쿡��, 
				robot.backmove();
				robot.backturn();
				robot.backmove();	//�ٶ󺸴� ������ ������ ä�� �� ĭ ������ �ϰ� 2������ ���ư���
				if (map[robot.y][robot.x] == 1)	//, ���� ������ ���̶� ������ �� �� ���� ��쿡�� �۵��� �����.
					robot.stop = true;
				else
					cnt = 0;
			}
			else {			//���� ���⿡ û���� ������ ���ٸ�, �� �������� ȸ���ϰ� 2������ ���ư���
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