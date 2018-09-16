#include <cstdio>

int n;
int g[100][100];
int v[100];

void dfs(int x) {
	for (int i = 0; i < n; i++) {
		if (v[i] == 0 && g[x][i] == 1) {
			v[i] = 1;
			dfs(i);
		}
	}
}


int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d ", &g[i][j]);
		}
	}
	
	
	for (int i = 0; i < n; i++) {
		dfs(i);
		for (int j = 0; j < n; j++) {
			printf("%d ", v[j]);
			v[j] = 0;
		}
		printf("\n");
	}

	return 0;
}