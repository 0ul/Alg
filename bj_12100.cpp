#include <cstdio>
#include <vector>
using namespace std;

int N, ans = 0;
int map[20][20], cpy[20][20], seq[5];

void copy() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cpy[i][j] = map[i][j];
		}
	}
}

void left() {
	int j, idx;
	for (int i = 0; i < N; i++) {
		j = 0; idx = 1;
		while (j + idx < N) {		//0없애고
			while (j + idx < N && cpy[i][j] == 0) {
				if (cpy[i][j + idx] == 0)
					idx++;
				else {
					cpy[i][j] = cpy[i][j + idx];
					cpy[i][j + idx] = 0;
				}
			}
			j++;
		}

		for (j = 0; j < N - 1; j++) {	//합칠거합치고
			if (cpy[i][j] == 0)
				continue;
			if (cpy[i][j] == cpy[i][j + 1]) {
				cpy[i][j] *= 2;
				cpy[i][j + 1] = 0;
				j++;
			}
		}

		j = 0; idx = 1;
		while (j + idx < N) {		//0없애고
			while (j + idx < N && cpy[i][j] == 0) {
				if (cpy[i][j + idx] == 0)
					idx++;
				else {
					cpy[i][j] = cpy[i][j + idx];
					cpy[i][j + idx] = 0;
				}
			}
			j++;
		}
	}
}
void right() {
	int j, idx;
	for (int i = 0; i < N; i++) {
		j = N - 1; idx = 1;
		while (j - idx >= 0) {		//0없애고
			while (j - idx >= 0 && cpy[i][j] == 0) {
				if (cpy[i][j - idx] == 0)
					idx++;
				else {
					cpy[i][j] = cpy[i][j - idx];
					cpy[i][j - idx] = 0;
				}
			}
			j--;
		}

		for (j = N - 1; j > 0; j--) {	//합칠거합치고
			if (cpy[i][j] == 0)
				continue;
			if (cpy[i][j] == cpy[i][j - 1]) {
				cpy[i][j] *= 2;
				cpy[i][j - 1] = 0;
				j--;
			}
		}

		j = N - 1; idx = 1;
		while (j - idx >= 0) {			//0없애고
			while (j - idx >= 0 && cpy[i][j] == 0) {
				if (cpy[i][j - idx] == 0)
					idx++;
				else {
					cpy[i][j] = cpy[i][j - idx];
					cpy[i][j - idx] = 0;
				}
			}
			j--;
		}
	}
}
void down() {
	int j, idx;
	for (int i = 0; i < N; i++) {
		j = N - 1; idx = 1;
		while (j - idx >= 0) {		//0없애고
			while (j - idx >= 0 && cpy[j][i] == 0) {
				if (cpy[j - idx][i] == 0)
					idx++;
				else {
					cpy[j][i] = cpy[j - idx][i];
					cpy[j - idx][i] = 0;
				}
			}
			j--;
		}

		for (j = N - 1; j > 0; j--) {	//합칠거합치고
			if (cpy[j][i] == 0)
				continue;
			if (cpy[j][i] == cpy[j - 1][i]) {
				cpy[j][i] *= 2;
				cpy[j-1][i] = 0;
				j--;
			}
		}

		j = N - 1; idx = 1;
		while (j - idx >= 0) {		//0없애고
			while (j - idx >= 0 && cpy[j][i] == 0) {
				if (cpy[j - idx][i] == 0)
					idx++;
				else {
					cpy[j][i] = cpy[j - idx][i];
					cpy[j - idx][i] = 0;
				}
			}
			j--;
		}
	}
}
void up() {
	int j, idx;
	for (int i = 0; i < N; i++) {
		j = 0; idx = 1;
		while (j + idx < N) {		//0없애고
			while (j + idx < N && cpy[j][i] == 0) {
				if (cpy[j + idx][i] == 0)
					idx++;
				else {
					cpy[j][i] = cpy[j + idx][i];
					cpy[j + idx][i] = 0;
				}
			}
			j++;
		}
		for (j = 0; j < N - 1; j++) {	//합칠거합치고
			if (cpy[j][i] == 0)
				continue;
			if (cpy[j][i] == cpy[j + 1][i]) {
				cpy[j][i] *= 2;
				cpy[j + 1][i] = 0;
				j++;
			}
		}
		j = 0; idx = 1;
		while (j + idx < N) {		//0없애고
			while (j + idx < N && cpy[j][i] == 0) {
				if (cpy[j + idx][i] == 0)
					idx++;
				else {
					cpy[j][i] = cpy[j + idx][i];
					cpy[j + idx][i] = 0;
				}
			}
			j++;
		}
	}
}

void dfs(int cnt) {
	if (cnt == 5) {
		copy();
		for (int i = 0; i < 5; i++) {
			if (seq[i] == 0)
				left();
			else if (seq[i] == 1)
				right();
			else if (seq[i] == 2)
				up();
			else
				down();
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (ans < cpy[i][j])
					ans = cpy[i][j];
			}
		}
		return;
	}
	for (int i = 0; i < 4; i++) {
		seq[cnt] = i;
		dfs(cnt + 1);
	}
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);
		}
	}
	dfs(0);
	printf("%d\n", ans);
	return 0;
}

