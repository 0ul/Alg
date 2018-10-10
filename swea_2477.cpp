// 2477. [모의 SW 역량테스트] 차량 정비소

#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

struct customer {
	int at;	// a 도착시간
	int an; // a 창구번호
	int bn; // b 창구번호
	customer() {}
	customer(int att, int ann, int bnn) {
		at = att;
		an = ann;
		bn = bnn;
	}

	friend bool operator< (customer b, customer a) {
		if (b.at == a.at)
			return b.an > a.an;
		return b.at > a.at;
	}
};

int N, M, A, B, K, T, ans, tiktok;
vector<int>a, b;	// 걸리는 시간 저장
vector<int>aa, bb, awho;	// 사용종료시간 , 누가 사용하고 있는지
vector<customer> v;

int isfull(int typ) {
	if (typ == 0) {	//aa 꽉찼는지 체크
		for (int i = 1; i <= N; i++) {
			if (aa[i] == 0)
				return i;
		}
		return 0;
	}
	else { //bb 꽉찼는지 체크
		for (int i = 1; i <= M; i++) {
			if (bb[i] == 0)
				return i;
		}
		return 0;
	}
}
int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d%d%d%d%d", &N, &M, &K, &A, &B);
		a.clear(); b.clear(); v.clear(); aa.clear(); bb.clear();  awho.clear();
		a.resize(N + 1); b.resize(M + 1); v.resize(K + 1); aa.resize(N + 1); bb.resize(M + 1); awho.resize(N + 1);
		for (int i = 1; i <= N; i++)
			scanf("%d", &a[i]);
		for (int i = 1; i <= M; i++)
			scanf("%d", &b[i]);
		for (int i = 1; i <= K; i++)
			scanf("%d", &v[i].at);

		ans = tiktok = 0;
		int curA = 1;	//현재 a창구에 대기중인 고객번호
		int idx;	//몇번 창구로 들어갈지 받는 변수
		int pass = 0;	//모든창구 통과한 고객
		priority_queue<customer> curB;	//b창구 대기중인 고객번호

		while (curA <= K || pass < K) {
			for (int i = 1; i <= N; i++) {
				if (tiktok == aa[i] && tiktok != 0) {	//종료시간일 경우 종료
					aa[i] = 0;
					customer tmp(tiktok, i, awho[i]);	//b에 들어가야하는 시간, 사용한 a번호, 고객번호
					curB.push(tmp);
				}
			}
			while (curA <= K && v[curA].at <= tiktok) {	//대기 중인 고객이 남았고, 들어가야하는 시간이 지난 경우
				idx = isfull(0);
				if (idx == 0)	//현재 꽉찬 상태
					break;
				aa[idx] = a[idx] + tiktok;	//지금 사용할 a의 종료시간 저장
				v[curA].an = idx;	//고객 정보에 저장
				awho[idx] = curA;	//사용한 고객번호 저장
				curA++;
			}

			for (int i = 1; i <= M; i++) {
				if (tiktok == bb[i])	//종료시간일 경우 종료
					bb[i] = 0;
			}
			while (!curB.empty()) {
				if (curB.top().at <= tiktok) {
					idx = isfull(1);
					if (idx == 0)
						break;
					customer tp = curB.top();
					bb[idx] = b[idx] + tiktok;
					v[tp.bn].bn = idx;
					curB.pop();
					pass++;
				}
			}

			tiktok++;
		}


		for (int i = 1; i <= K; i++) {
			if (v[i].an == A && v[i].bn == B)
				ans += i;
		}

		if (ans == 0)
			ans = -1;

		printf("#%d %d\n", tc, ans);
	}
	return 0;
}