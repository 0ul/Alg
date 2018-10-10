// 2477. [���� SW �����׽�Ʈ] ���� �����

#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

struct customer {
	int at;	// a �����ð�
	int an; // a â����ȣ
	int bn; // b â����ȣ
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
vector<int>a, b;	// �ɸ��� �ð� ����
vector<int>aa, bb, awho;	// �������ð� , ���� ����ϰ� �ִ���
vector<customer> v;

int isfull(int typ) {
	if (typ == 0) {	//aa ��á���� üũ
		for (int i = 1; i <= N; i++) {
			if (aa[i] == 0)
				return i;
		}
		return 0;
	}
	else { //bb ��á���� üũ
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
		int curA = 1;	//���� aâ���� ������� ����ȣ
		int idx;	//��� â���� ���� �޴� ����
		int pass = 0;	//���â�� ����� ��
		priority_queue<customer> curB;	//bâ�� ������� ����ȣ

		while (curA <= K || pass < K) {
			for (int i = 1; i <= N; i++) {
				if (tiktok == aa[i] && tiktok != 0) {	//����ð��� ��� ����
					aa[i] = 0;
					customer tmp(tiktok, i, awho[i]);	//b�� �����ϴ� �ð�, ����� a��ȣ, ����ȣ
					curB.push(tmp);
				}
			}
			while (curA <= K && v[curA].at <= tiktok) {	//��� ���� ���� ���Ұ�, �����ϴ� �ð��� ���� ���
				idx = isfull(0);
				if (idx == 0)	//���� ���� ����
					break;
				aa[idx] = a[idx] + tiktok;	//���� ����� a�� ����ð� ����
				v[curA].an = idx;	//�� ������ ����
				awho[idx] = curA;	//����� ����ȣ ����
				curA++;
			}

			for (int i = 1; i <= M; i++) {
				if (tiktok == bb[i])	//����ð��� ��� ����
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