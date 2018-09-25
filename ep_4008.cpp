//4008.[모의 SW 역량테스트] 숫자 만들기
#include <cstdio>

int T, N, x, minn, maxx;
int num[12];
int opr[4];

void dfs(int idx, int sum, int a, int s, int m, int d) {
	if (idx == N) {
		if (sum > maxx)
			maxx = sum;
		if (sum < minn)
			minn = sum;
		return;
	}
	if (a < opr[0])
		dfs(idx + 1, sum + num[idx], a + 1, s, m, d);

	if (s < opr[1])
		dfs(idx + 1, sum - num[idx], a, s + 1, m, d);

	if (m < opr[2])
		dfs(idx + 1, sum * num[idx], a, s, m + 1, d);

	if (d < opr[3])
		dfs(idx + 1, sum / num[idx], a, s, m, d + 1);

}


int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		minn = 100000001, maxx = -100000001;

		scanf("%d", &N);
		for (int i = 0; i < 4; i++) {
			scanf("%d", &opr[i]);
		}

		for (int i = 0; i < N; i++)
			scanf("%d", &num[i]);

		dfs(1, num[0], 0, 0, 0, 0);



		printf("#%d %d\n", tc, maxx - minn);
	}

	return 0;
}