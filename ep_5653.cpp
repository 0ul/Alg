// 5653. [���� SW �����׽�Ʈ] �ٱ⼼�����

#include <cstdio>
#include <queue>
using namespace std;


struct cell {
	int y;
	int x;
	int time;
	int life;

	cell(int i, int j, int t, int l) {
		y = i; x = j;
		time = t; life = l;
	}

	friend bool operator<(cell a, cell b) {
		if (a.time == b.time) //�ð� ������ ������ ū�� ���� �̱�
			return a.life < b.life;

		return a.time > b.time;	//�ð� ������ ���� �̱�
	}
};

int T, X, Y, K;
int map[800][800];	//400,400
int xx[4] = { 1,-1,0,0 };
int yy[4] = { 0,0,1,-1 };
priority_queue<cell> q, die;

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d %d", &Y, &X, &K);
		for (int i = 400; i < 400 + Y; i++) {
			for (int j = 400; j < 400 + X; j++) {
				scanf("%d", &map[i][j]);
				if (map[i][j] > 0) {
					cell c(i, j, map[i][j] + 1, map[i][j]);//��Ȱ�� x�ð� + Ȱ�� 1�ð�
					q.push(c);
				}
			}
		}
		int clock = 0, ny, nx;
		cell tmp(0, 0, 0, 0);

		while (clock <= K) {
			while (!q.empty()) {
				tmp = q.top();
				if (clock != tmp.time)
					break;

				//Ȱ��ȭ���� 1�ð�
				for (int i = 0; i < 4; i++) {
					ny = tmp.y + yy[i];
					nx = tmp.x + xx[i];
					if (map[ny][nx] == 0) {	//�������
						map[ny][nx] = tmp.life;	//����
						cell next(ny, nx, clock + tmp.life + 1, tmp.life);
						q.push(next);
					}
				}
				tmp.time = tmp.life - 1 + clock;	//x+x�ð��̸� �״µ� x+1�ð� ����
				die.push(tmp);
				q.pop();
			}

			while (!die.empty()) {
				tmp = die.top();
				if (clock != tmp.time)
					break;
				map[tmp.y][tmp.x] = -1;	//����
				die.pop();
			}

			clock++;
		}

		int ans = 0;
		for (int i = 0; i < 800; i++) {
			for (int j = 0; j < 800; j++) {
				if (map[i][j] > 0)
					ans++;
				map[i][j] = 0;
			}
		}
		while (!q.empty())
			q.pop();
		while (!die.empty())
			die.pop();
		printf("#%d %d\n", tc, ans);
	}
	return 0;
}