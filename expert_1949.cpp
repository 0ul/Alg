#include <cstdio>
#include <vector>
#include <queue>
using namespace std;


struct xy {
	int x; int y; 
	xy(int b, int a) {
		y = b; x = a;
	}
};
int T, N, K, answer, high;
vector<vector<int>> v;
queue<xy> q;
int xx[4] = { 1,-1,0,0 };
int yy[4] = { 0,0,1,-1 };
int visit[8][8];

void bt(xy cur, int cnt, bool did) {
	int nx, ny;
	if (answer < cnt)
		answer = cnt;

	for (int i = 0; i < 4; i++) {
		ny = cur.y + yy[i];
		nx = cur.x + xx[i];
		if (nx < 0 || ny < 0 || nx >= N || ny >= N)	
			continue;	//범위확인
		if (visit[ny][nx] == 0) {
			if (v[ny][nx] < v[cur.y][cur.x]) {
				visit[ny][nx] = 1;
				xy next(ny, nx);
				bt(next, cnt + 1, did);
			}
			else if (did == false && (v[ny][nx] - K) < v[cur.y][cur.x]) {
				int temp = v[ny][nx];	
				v[ny][nx] = v[cur.y][cur.x] - 1;
				visit[ny][nx] = 1;
				xy next(ny, nx);
				bt(next, cnt + 1, true);
				v[ny][nx] = temp;
			}
			visit[ny][nx] = 0;
		}
	}
}


int main() {
	scanf("%d", &T);

	for (int i = 0; i < 8; i++) {
		vector<int> tmp(8);
		v.push_back(tmp);
	}	//이차원 벡터 생성

	for (int tc = 1; tc <= T; tc++) {
		//reset
		answer = high = 0;

		//input
		scanf("%d%d", &N, &K);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &v[i][j]);
				if (high < v[i][j])
					high = v[i][j];
			}
		}

		//가장 높은 봉우리 찾기
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (high == v[i][j]) {
					xy tmp(i, j);
					q.push(tmp);
				}
			}
		}

		while (!q.empty()) {
			xy cur = q.front();
			q.pop();
			visit[cur.y][cur.x] = 1;
			bt(cur, 1, false);
			visit[cur.y][cur.x] = 0;
		}
		printf("#%d %d\n", tc, answer);
	}
	return 0;
}