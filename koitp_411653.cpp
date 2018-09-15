#include <cstdio>
#include <queue>
using namespace std;

int t, n, m, k, a, b, cur, cnt;
int map[1001][1001];
int visit[1001];
queue<int> q;

int main() {
	scanf("%d", &t);
	for (int tc = 1; tc <= t; tc++) {
		//초기화
		for (int i = 1; i <= n; i++) {
			visit[i] = 0;
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				map[i][j] = 0;
			}
		}
		while (!q.empty()) {
			q.pop();
		}
		cnt = 0;

		//입력
		scanf("%d%d%d", &n, &m, &k);
		for (int i = 0; i < m; i++) {
			scanf("%d%d", &a,&b);
			map[a][b] = 1;
		}

		//bfs
		q.push(1);
		while (!q.empty()) {
			cur = q.front();
			cnt++;
			q.pop();
			for (int i = 1; i <= n; i++) {
				if (visit[i] == 0 && map[cur][i] == 1) {
					visit[i] = visit[cur] + 1;
					//printf("%d  > %d\n", cur, i);
					q.push(i);
				}
				if (visit[n] != 0)
					break;
			}

			if (visit[n] != 0)
				break;
		}
		
		if (visit[n] > k || visit[n] == 0)
			printf("#%d -1\n", tc);
		else
			printf("#%d %d\n", tc, visit[n]);
	}
	return 0;
}