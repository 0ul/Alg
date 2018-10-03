// 15685 치킨 배달
#include <cstdio>
#include <vector>
using namespace std;

struct xy {
	int x;
	int y;
	xy(int b, int a) {
		y = b; x = a;
	}
};

int T, N, M, ans;
int map[50][50];
vector<xy> home;
vector<xy> chik;
vector<vector<int>> des;	//des[집][치킨집]
vector<int> comb;

int sub(int a, int b) {	//절대값구하기
	if (a > b)
		return a - b;
	return b - a;
}

void cal() {	//각 집을 기준으로 치킨집까지의 거리 전부 구함
	int x, y;
	des.clear();


	for (int i = 0; i < home.size(); i++) {
		vector<int> tmp(chik.size());
		des.push_back(tmp);

		for (int j = 0; j < chik.size(); j++) {
			des[i][j] += sub(chik[j].x, home[i].x);
			des[i][j] += sub(chik[j].y, home[i].y);
		}
	}
}

int mindes() {	//조합 구해졌을 때 그 조합에서의 최소 거리 구함
	int total = 0, tmp = 0;
	for (int i = 0; i < home.size(); i++) {
		tmp = 2501;
		for (int j = 0; j < M; j++) {	//치킨집개수
			if (comb[j] == -1)
				continue;
			if (tmp > des[i][comb[j]])	//i번 집에서 최소거리
				tmp = des[i][comb[j]];
		}
		total += tmp;
	}

	return total;
}

void dfs(int n, int idx) {	//n현재까지 조합에 포함된 개수,
							//idx현재 치킨집 번호
	if (idx >= chik.size() || n >= M) {
		if (n == 0)
			return;
		int cur = mindes();
		if (ans > cur)
			ans = cur;
		return;
	}

	comb[n] = idx;
	dfs(n + 1, idx + 1);

	comb[n] = -1;
	dfs(n, idx + 1);
}


int main() {
	scanf("%d%d", &N, &M);

	home.clear(); chik.clear();
	comb.clear();
	comb.resize(M, -1);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 1)
				home.push_back({ i,j });
			else if (map[i][j] == 2)
				chik.push_back({ i,j });
		}
	}
	ans = 1000000;

	cal();
	dfs(0, 0);


	printf("%d\n", ans);
	return 0;
}
