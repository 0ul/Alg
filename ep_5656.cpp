// 5656. [���� SW �����׽�Ʈ] ���� ����

#include <cstdio>
#include <vector>
using namespace std;

int T, X, Y, N;
vector<vector<int>> map;	//�� ó�� �Է¹��� ����
vector<vector<int>> cpy;
vector<int> seq;
int xx[4] = { 1,-1,0,0 }; //0�� 1�� 2�� 3��
int yy[4] = { 0,0,-1,1 };
int non[12];
int ans;
bool empt;

void del(int y, int x, int n) {//��ǥ, ������ ����
	int ny, nx, tmp;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < n; j++) {
			ny = y + yy[i] * j;
			nx = x + xx[i] * j;
			if (ny < 0 || nx < 0 || ny >= Y || nx >= X)
				continue;
			if (cpy[ny][nx] != 0) {
				tmp = cpy[ny][nx];
				cpy[ny][nx] = 0;
				del(ny, nx, tmp);
			}
		}
	}
}

void nospace() {	//�����޲�
	int idx;
	for (int j = 0; j < X; j++) {
		idx = 0;
		for (int i = Y - 1; i > 0; i--) {
			if (cpy[i][j] == 0) {
				while (1) {
					if (i - 1 - idx < 0)
						break;

					if (cpy[i - 1 - idx][j] == 0)
						idx++;
					else {
						cpy[i][j] = cpy[i - 1 - idx][j];
						cpy[i - 1 - idx][j] = 0;
						break;
					}
				}
			}
		}
	}
}

int chk() {	//���� ���� ����
	int scr = 0;
	for (int i = 0; i < Y; i++) {
		for (int j = 0; j < X; j++) {
			if (cpy[i][j] != 0)
				scr++;
		}
	}
	return scr;
}

void isempty() {	//������� ���̻� ������ʿ����
	for (int i = 0; i < Y; i++) {
		for (int j = 0; j < X; j++) {
			if (cpy[i][j] != 0)
				return;
		}
	}
	empt = true;
	return;
}

void bt(int n, vector<int> sequenc) {	//n��° ���� 
	if (n >= N) {//���� N��������� ����
		int scr = chk();
		if (ans > scr)
			ans = scr;
		return;
	}

	int x = sequenc[n];
	for (int i = 0; i < Y; i++) {
		if (cpy[i][x] != 0) {
			del(i, x, cpy[i][x]);
			break;
		}
	}
	nospace();

	bt(n + 1, sequenc);
}

void makeseq(int n) {	//���� ����
	if (n == N) {
		if (empt != true) {
			cpy = map;
			bt(0, seq);
			isempty();
		}
		return;
	}

	for (int i = 0; i < X; i++) {
		seq[n] = i;
		makeseq(n + 1);
	}
	
}



int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d%d%d", &N, &X, &Y);
		seq.clear();
		seq.resize(N);
		map.clear();
		empt = false;

		for (int i = 0; i < Y; i++) {
			vector<int> spc(X);
			map.push_back(spc);

			for (int j = 0; j < X; j++) {
				scanf("%d", &map[i][j]);
			}
		}

		ans = 200;
		makeseq(0);
		

		printf("#%d %d\n", tc, ans);
	}
	return 0;
}