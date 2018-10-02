// 5656. [모의 SW 역량테스트] 벽돌 깨기

#include <cstdio>
#include <vector>
using namespace std;

int T, X, Y, N;
vector<vector<int>> map;	//맨 처음 입력받은 지도
vector<vector<int>> cpy;
vector<int> seq;
int xx[4] = { 1,-1,0,0 }; //0왼 1오 2위 3아
int yy[4] = { 0,0,-1,1 };
int non[12];
int ans;
bool empt;

void del(int y, int x, int n) {//좌표, 벽돌의 숫자
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

void nospace() {	//공간메꿈
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

int chk() {	//남은 벽돌 개수
	int scr = 0;
	for (int i = 0; i < Y; i++) {
		for (int j = 0; j < X; j++) {
			if (cpy[i][j] != 0)
				scr++;
		}
	}
	return scr;
}

void isempty() {	//비었으면 더이상 계산할필요없음
	for (int i = 0; i < Y; i++) {
		for (int j = 0; j < X; j++) {
			if (cpy[i][j] != 0)
				return;
		}
	}
	empt = true;
	return;
}

void bt(int n, vector<int> sequenc) {	//n번째 구슬 
	if (n >= N) {//구슬 N번쐈을경우 종료
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

void makeseq(int n) {	//순서 생성
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