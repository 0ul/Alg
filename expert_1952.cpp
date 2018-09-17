//수영장

#include <cstdio>
#include <vector>
using namespace std;

int T, D, M, TM, Y, pay;
int plan[12];
int month[12];

void dfs(int cur,int budget) {
	if (budget > pay)
		return;
	if (cur == 12) {
		if (budget < pay)
			pay = budget;
		return;
	}
	
	if (cur < 10) {
		int sum = 0;
		for (int i = 0; i < 3; i++) {
			sum += month[cur + i];
		}
		if (sum > TM)	//삼개월이 이득
			dfs(cur + 3, budget + TM);
		dfs(cur + 1, budget + month[cur]);	//삼개월 했을때도 돌려봐야 함. 다음 달 부터 삼개월이 이득일수도.
	}
	else	//세달 불가능
		dfs(cur + 1, budget + month[cur]);
}


int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d %d %d", &D, &M, &TM, &Y);
		for (int i = 0; i < 12; i++)
			scanf("%d", &plan[i]);

		pay = Y;	//초기값으로 일년값줘서 바로 비교
		for (int i = 0; i < 12; i++) {
			if (plan[i] * D < M)	//한달권보다 일일권이 나은지
				month[i] = plan[i] * D;
			else
				month[i] = M;
		}

		dfs(0, 0);


		printf("#%d %d\n", tc, pay);
	}
	return 0;
}