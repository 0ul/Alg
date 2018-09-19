//2117 Ȩ��� ����
#include <cstdio>;

int T, N, M, total, answer, maxK, cur;
int map[20][20];

int abs(int y, int num) {
	if (num < y)
		return y - num;
	return num - y;
}

int checkx(int y, int x, int k) {	//������ x������ 1 ���� Ȯ��
	int cnt = 0;
	for (int i = x - k; i <= x + k; i++) {
		if (i < 0 || i >= N)
			continue;
		if (map[y][i] == 1)
			cnt++;
	}
	return cnt;
}

int checky(int y, int x, int k) {	// x������ y����ŭ Ȯ��
	int cnt = 0;
	for (int i = y - k; i <= y + k; i++) {
		if (i < 0 || i >= N)
			continue;
		cnt += checkx(i, x, k - abs(y, i));	//abs�� y���� �󸶳� �������ִ��� Ȯ���ؼ� k���� ������
	}
	return cnt;
}
	

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		total = 0; answer = 1; maxK = 0;	//k�� ������ k���� 1�۰� ������
		scanf("%d%d", &N, &M);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &map[i][j]);
				if (map[i][j] == 1)
					total++;
			}
		}

		int cal = total * M;	//�ִ� ���� ���� �� ã��
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