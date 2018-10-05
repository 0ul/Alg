// 4012. [모의 SW 역량테스트] 요리사

#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

int T, N, ans, tmp;
int map[16][16];
int comb[16];

int cal() {
	int s1(0), s2(0);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (comb[i] == 0 && comb[j] == 0) {
				s1 += map[i][j];
			}
			if (comb[i] == 1 && comb[j] == 1) {
				s2 += map[i][j];
			}
		}
	}
	if (s1 > s2)
		return s1 - s2;
	return s2 - s1;
}

void combination(int n, int idx) {	//조합 생성	
	if (idx >= N || n > N / 2) {
		if (n == N / 2) {
			tmp = cal();
			if (ans > tmp)
				ans = tmp;
		}
		return;
	}
	comb[idx] = 1;
	combination(n + 1, idx + 1);

	comb[idx] = 0;
	combination(n, idx + 1);
}

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &map[i][j]);
			}
		}

		ans = 1000000;
		for (int i = 0; i < N; i++)
			comb[i] = 0;

		combination(0, 0);


		printf("#%d %d\n", tc, ans);
	}
}