// 4014 활주로 건설

#include <cstdio>
#include <vector>
using namespace std;

int T, N, X, ans;
vector<vector<int>> map;	//입력 저장
vector<vector<int>> v, v1;	//경사로 건설했는지 아닌지

bool visit(int i, int j, int type, int dir) {	// type 가로세로 dir 오르막 내리막
	int idx = 0;
	if (type == 0 && dir == 0) {	//가로 검사하는데 오르막
		while (idx < X) {
			if (j - idx < 0)
				return false;
			if (v[i][j - idx] == 1)
				return false;
			idx++;
		}
		idx = 0;
		while (idx < X) {
			v[i][j - idx] = 1;
			idx++;
		}
		return true;
	}
	else if (type == 0 && dir == 1) {	//가로 검사하는데 내리막
		while (idx < X) {
			if (j + idx >= N)
				return false;
			if (v[i][j + idx] == 1)
				return false;
			idx++;
		}
		idx = 0;
		while (idx < X) {
			v[i][j + idx] = 1;
			idx++;
		}
		return true;
	}
	else if (type == 1 && dir == 0) {	//세로 검사하는데 오르막
		while (idx < X) {
			if (j - idx < 0)
				return false;
			if (v1[j - idx][i] == 1)
				return false;
			idx++;
		}
		idx = 0;
		while (idx < X) {
			v1[j - idx][i] = 1;
			idx++;
		}
		return true;
	}
	else {
		while (idx < X) {
			if (j + idx >= N)
				return false;
			if (v1[j + idx][i] == 1)
				return false;
			idx++;
		}
		idx = 0;
		while (idx < X) {
			v1[j + idx][i] = 1;
			idx++;
		}
		return true;
	}
}

void chk(int type) {	//type 0:가로검사 1:세로검사
	int can;
	if (type == 0) {
		for (int i = 0; i < N; i++) {
			can = 1;
			for (int j = 0; j < N - 1; j++) {
				if (map[i][j] == map[i][j + 1])
					continue;
				if (map[i][j] + 1 == map[i][j + 1]) {	//오르막
					if (!visit(i, j, 0, 0)) {
						can = 0;
						break;
					}
				}
				else if (map[i][j] - 1 == map[i][j + 1]) {	// 내리막
					if (!visit(i, j + 1, 0, 1)) {
						can = 0;
						break;
					}
				}
				else {
					can = 0;
					break;
				}
			}
			if (can == 1)
				ans++;
		}
	}
	else {
		for (int i = 0; i < N; i++) {
			can = 1;
			for (int j = 0; j < N - 1; j++) {
				if (map[j][i] == map[j + 1][i])
					continue;
				if (map[j][i] + 1 == map[j + 1][i]) {	//오르막
					if (!visit(i, j, 1, 0)) {
						can = 0;
						break;
					}
				}
				else if (map[j][i] - 1 == map[j + 1][i]) {	// 내리막
					if (!visit(i, j + 1, 1, 1)) {
						can = 0;
						break;
					}
				}
				else {
					can = 0;
					break;
				}
			}
			if (can == 1)
				ans++;
		}
	}
}

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		map.clear();	v.clear();	v1.clear();

		scanf("%d%d", &N, &X);
		for (int i = 0; i < N; i++) {
			vector<int> tmp(N);

			map.push_back(tmp);
			v.push_back(tmp);
			v1.push_back(tmp);
			for (int j = 0; j < N; j++) {
				scanf("%d", &map[i][j]);
			}
		}

		ans = 0;
		chk(0);
		chk(1);

		printf("#%d %d\n", tc, ans);
	}
	return 0;
}