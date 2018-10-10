// 2383. [모의 SW 역량테스트] 점심 식사시간
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

struct stairs {
	int y, x;
	int lng;
	int cnt;
	stairs(int a, int b, int c) {
		y = a;
		x = b;
		lng = c;
		cnt = 0;
	}
};
struct person {
	int y, x;
	int str;
	int dis[2] = { 0, };
	person(int a, int b) {
		y = a;
		x = b;
		str = 0;
	}
	void dist(stairs a, int n) {
		int i, j;
		if (a.x > x)	j = a.x - x;
		else if (a.x <= x)	j = x - a.x;
		if (a.y > y)	i = a.y - y;
		else if (a.y <= y)	i = y - a.y;

		dis[n] = i + j;
	}

};
int T, N, a, b, ans;
int map[10][10];
vector<person> p;
vector<stairs> s;
priority_queue< int, vector<int>, greater<int> > wait, wait1;
queue<int> on, on1;

void cal() {
	for (int i = 0; i < p.size(); i++) {
		if (p[i].str == 0)
			wait.push(p[i].dis[0]);
		else
			wait1.push(p[i].dis[1]);
	}

	int clock = 0, wtclock;

	while (clock < ans) {
		if (wait.empty() && wait1.empty() && on.empty() && on1.empty())
			break;

		clock++;
		while (!on.empty()) {
			if (on.front() != clock)
				break;
			on.pop();
			s[0].cnt--;
		}
		while (!on1.empty()) {
			if (on1.front() != clock)
				break;
			on1.pop();
			s[1].cnt--;
		}

		while (!wait.empty()) {
			if (wait.top() > clock)
				break;
			if (s[0].cnt >= 3)
				break;
			if (clock == wait.top())
				wtclock = 1;
			else
				wtclock = 0;
			wait.pop();
			s[0].cnt++;
			on.push(clock + s[0].lng + wtclock);
		}

		while (!wait1.empty()) {
			if (wait1.top() > clock)
				break;
			if (s[1].cnt >= 3)
				break;
			if (clock == wait1.top())
				wtclock = 1;
			else
				wtclock = 0;
			wait1.pop();
			s[1].cnt++;
			on1.push(clock + s[1].lng + wtclock);
		}
	}

	if (clock < ans)
		ans = clock;

	while (!on.empty())
		on.pop();
	while (!on1.empty())
		on1.pop();
	while (!wait.empty())
		wait.pop();
	while (!wait1.empty())
		wait1.pop();
	s[0].cnt = 0;
	s[1].cnt = 0;
}

void comb(int idx) {
	if (idx >= p.size()) {
		cal();
		return;
	}

	p[idx].str = 0;
	comb(idx + 1);
	p[idx].str = 1;
	comb(idx + 1);
}



int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d", &N);

		p.clear();
		s.clear();
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &map[i][j]);
				if (map[i][j] == 1) {
					person tmp(i, j);
					p.push_back(tmp);
				}
				else if (map[i][j] > 1) {
					stairs tmp(i, j, map[i][j]);
					s.push_back(tmp);
				}
			}
		}
		for (int i = 0; i < p.size(); i++) {
			for (int j = 0; j < 2; j++) {
				p[i].dist(s[j], j);
			}
		}
		ans = 1000000;
		comb(0);
		printf("#%d %d\n", tc, ans);
	}
	return 0;
}