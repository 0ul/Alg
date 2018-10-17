#include <cstdio>
#include <vector>
using namespace std;

struct info {
	int t;
	int p;
	info(int lng, int pay) {
		t = lng;
		p = pay;
	}
};
int N, a, b, ans = 0;
vector<info> date;

void dfs(int cnt, int idx) {
	if (idx > N)	return;
	if (ans < cnt)
		ans = cnt;
	for (int i = idx + 1; i <= N; i++) {
		dfs(cnt + date[i].p, i + date[i].t - 1);
	}
}

int main() {
	scanf("%d", &N);
	date.push_back(info(0, 0));
	for (int i = 0; i < N; i++) {
		scanf("%d%d", &a, &b);
		info tmp(a, b);
		date.push_back(tmp);
	}
	dfs(0, 0);
	printf("%d\n", ans);

	return 0;
}