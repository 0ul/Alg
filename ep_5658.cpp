//5658 보물상자 비밀번호

#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int T, N, K, index, cnt;
char input;
int ch[28], temp[7];
vector<int> v;

bool cmp(int a, int b) {
	return a > b;
}

int stoh(int c[], int n) {	//16진수 계산
	int sum = 0;
	for (int i = n - 1; i >= 0; i--) {
		sum += c[i]*pow(16, n - 1 - i);
	}
	return sum;
}


int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d%d", &N, &K);
		
		for (int i = 0; i < N; i++) {
			scanf(" %c", &input);
			if (input - '0' < 10)
				ch[i] = input - '0';
			else
				ch[i] = input - 'A' + 10;
		}

		v.clear();

		//총 만들수 있는 비밀번호 개수 무조건 N개 0,1,2 / 1,2,3 /... /  9,10,11 / 10,11,0 / 11,0,1
		for (int a = 0; a < N; a++) {	
			for (int b = 0; b < N / 4; b++) {
				if (a + b < N)
					temp[b] = ch[a + b];
				else	// 11,0,1 이런 경우 체크
					temp[b] = ch[a + b - N];
			}
			int tmp = stoh(temp, N / 4);
			v.push_back(tmp);
		}

		sort(v.begin(), v.end(), cmp);

		index = 0; cnt = 1;
		while (cnt < K) {
			if (v[index] != v[index + 1])
				cnt++;
			index++;
		}


		printf("#%d %d\n", tc, v[index]);
	}
}


