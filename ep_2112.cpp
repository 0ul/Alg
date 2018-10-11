// 2112. [���� SW �����׽�Ʈ] ��ȣ �ʸ�

#include <cstdio>
#include <vector>
using namespace std;

int T, X, Y, K, ans;
int map[13][20];
vector<int> treat;	// 1�̸�A 2�� B

bool chk() {
	int cnt, cur, idx;
	for (int i = 0; i < X; i++) {
		cnt = 0;
		for (int j = 0; j <= Y - K; j++) {
			cnt = 0;
			idx = j;
			if (treat[j] == 0)	//��ǰó�� X
				cur = map[j][i];
			else				//��ǰó�� O
				cur = treat[j] - 1;
			
			while (cnt < K) {
				if (treat[idx] == 0) {
					if (cur == map[idx][i]) {
						cnt++;
						idx++;
					}
					else
						break;
				}
				else {
					if (cur == treat[idx] - 1) {
						cnt++;
						idx++;
					}
					else
						break;
				}
			}
			if (cnt == K)
				break;
		}
		if (cnt < K)
			return false;
	}
	return true;
}

void dfs(int cnt, int y) {	//��ǰó�� Ƚ��, y index
	if (cnt >= ans)	return;
	if (chk()) {
		ans = cnt;
		return;
	}

	for (int i = y; i < Y; i++) {
		treat[i] = 1;
		dfs(cnt + 1, i + 1);
		treat[i] = 2;
		dfs(cnt + 1, i + 1);
		treat[i] = 0;
	}
}

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d%d%d", &Y, &X, &K);
		for (int i = 0; i < Y; i++) {
			for (int j = 0; j < X; j++) {
				scanf("%d", &map[i][j]);
			}
		}

		treat.clear(); treat.resize(Y);
		ans = K;

		dfs(0, 0);

		printf("#%d %d\n", tc, ans);
	}
	return 0;
}