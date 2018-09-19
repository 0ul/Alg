//2117 홈방범 서비스
#include <cstdio>;

int T, N, M, total, answer, maxK, cur;
int map[20][20];

int abs(int y, int num) {
	if (num < y)
		return y - num;
	return num - y;
}

int checkx(int y, int x, int k) {	//마름모 x범위에 1 개수 확인
	int cnt = 0;
	for (int i = x - k; i <= x + k; i++) {
		if (i < 0 || i >= N)
			continue;
		if (map[y][i] == 1)
			cnt++;
	}
	return cnt;
}

int checky(int y, int x, int k) {	// x범위를 y번만큼 확인
	int cnt = 0;
	for (int i = y - k; i <= y + k; i++) {
		if (i < 0 || i >= N)
			continue;
		cnt += checkx(i, x, k - abs(y, i));	//abs는 y에서 얼마나 떨어져있는지 확인해서 k범위 정해줌
	}
	return cnt;
}
	

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		total = 0; answer = 1; maxK = 0;	//k를 문제의 k보다 1작게 생각함
		scanf("%d%d", &N, &M);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &map[i][j]);
				if (map[i][j] == 1)
					total++;
			}
		}

		int cal = total * M;	//최대 감시 영역 수 찾기
		while (maxK*maxK + (maxK + 1)*(maxK + 1) <= cal) {
			maxK++;
		}

		for (int k = maxK - 1; k > 0; k--) {
			cal = k * k + (k + 1)*(k + 1);
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					cur = checky(i, j, k);
					if (cur*M >= cal && answer < cur) {
						answer = cur;
					}
					if (answer == total)
						break;
				}
				if (answer == total)
					break;
			}
			if (answer == total)
				break;
		}

		printf("#%d %d\n", tc, answer);
	}
}