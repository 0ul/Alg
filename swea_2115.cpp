// 2115

#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct xy{
	int y;
	int x;
};
int T, N, M, C, ans;
int map[10][10];
vector<xy> v(2);
vector<int> honey, honey1;

int clac(int a) {
	return a * a;
}

void cal() {
	for (int i = 0; i < M; i++) {
		honey[i] = map[v[0].y][v[0].x + i];
		honey1[i] = map[v[1].y][v[1].x + i];
	}

	sort(honey.begin(), honey.end());
	sort(honey1.begin(), honey1.end());

	int idx, total, cnt;
	int budg[2] = { 0, };

	for (int i = M - 1; i >= 0; i--) {	//오름차순이므로 뒤에서부터 검사
		idx = i; total = 0; cnt = 0;
		while (idx >= 0 && cnt <= C) {
			if (cnt + honey[idx] <= C) {
				cnt += honey[idx];
				total += clac(honey[idx]);
			}
			idx--;
		}
		if (budg[0] < total)
			budg[0] = total;
		else
			break;
	}

	for (int i = M - 1; i >= 0; i--) {
		idx = i; total = 0; cnt = 0;
		while (idx >= 0 && cnt <= C) {
			if (cnt + honey1[idx] <= C) {
				cnt += honey1[idx];
				total += clac(honey1[idx]);
			}
			idx--;
		}
		if (budg[1] < total)
			budg[1] = total;
		else
			break;
	}
	if (ans < budg[0] + budg[1])
		ans = budg[0] + budg[1];
}

void dfs(int idx, int y, int x) {
	for (int i = 0; i < N; i++) {				//첫번째 벌꿀통 설정
		for (int j = 0; j <= N - M; j++) {
			v[0].y = i; v[0].x = j;		//y값하고 제일 처음 x값만 저장
			for (int ii = i; ii < N; ii++) {	//첫번째보다 뒤에 있는 것만 검사해주면됨
				for (int jj = 0; jj <= N - M; jj++) {
					if (ii == i && jj < j + M)	continue;
					v[1].y = ii; v[1].x = jj;
					cal();	//벌꿀통 설정해줬으면 소득 계산
				}
			}
		}
	}
}

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d%d%d", &N, &M, &C);

		honey.clear(); honey.resize(M);
		honey1.clear(); honey1.resize(M);

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &map[i][j]);
			}
		}

		ans = 0;
		dfs(0, 0, 0);
		
		printf("#%d %d\n", tc, ans);
	}
	return 0;
}