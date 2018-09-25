//#include <cstdio>
//
//int N, S, ans(100000);
//int g[100000];
//
//int main() {
//	scanf("%d %d", &N, &S);
//	for (int i = 0; i < N; i++) {
//		scanf("%d", &g[i]);
//		if (g[i] >= S) {
//			printf("1\n");
//			return 0;
//		}
//	}
//
//	int L(0), R(0);
//	int sum = g[0];
//
//	while (L <= R && R<N) {
//		if (sum < S) {
//			R++;
//			sum += g[R];
//		}
//		else {
//			if (ans > R - L + 1)
//				ans = R - L + 1;
//			sum -= g[L];
//			L++;
//		}
//	}
//
//	if (ans == 100000)
//		printf("0\n");
//	else
//		printf("%d\n", ans);
//
//	return 0;
//}