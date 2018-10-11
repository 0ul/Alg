// 15683 °¨½Ã

#include <cstdio>
#include <vector>
using namespace std;

struct camera {
	int y;
	int x;
	int type;
};
int X, Y, ans;
vector<vector<int>> map, visit, cpy;
vector<camera> cctv;
vector<int> sequence;
int xx[4] = { 1,-1,0,0 }; //r0 l1 u2 d3
int yy[4] = { 0,0,-1,1 };
int direction[4][4][3] = { { { 0 },{ 1 },{ 2 },{ 3 } } ,{ { 0,1 },{ 2,3 },{ 0,1 },{ 2,3 } } ,//type, dir
{ { 0,2 },{ 0,3 },{ 1,2 },{ 1,3 } } ,{ { 0,1,2 },{ 1,2,3 },{ 2,3,0 },{ 3,0,1 } } };

void camera5(camera c) {
	int ny, nx;
	for (int dir = 0; dir < 4; dir++) {
		ny = c.y;	nx = c.x;
		while (0 <= ny && ny < Y && 0 <= nx && nx < X) {
			visit[ny][nx] = 1;
			if (map[ny][nx] == 6)
				break;
			ny += yy[dir];
			nx += xx[dir];
		}
	}
}

void chk() {
	int ny, nx, typ, dir, num;
	for (int i = 0; i < cctv.size(); i++) {
		typ = cctv[i].type;
		dir = sequence[i];
		if (typ == 1)
			num = 1;
		else if (typ == 4)
			num = 3;
		else
			num = 2;
		typ--;

		for (int j = 0; j < num; j++) {
			ny = cctv[i].y;	nx = cctv[i].x;
			while (0 <= ny && ny < Y && 0 <= nx && nx < X) {
				cpy[ny][nx] = 1;
				if (map[ny][nx] == 6)
					break;
				ny += yy[direction[typ][dir][j]];
				nx += xx[direction[typ][dir][j]];
			}
		}
	}
	int cnt = 0;
	for (int i = 0; i < Y; i++) {
		for (int j = 0; j < X; j++) {
			if (cpy[i][j] == 0)
				cnt++;
		}
	}
	if (cnt < ans)
		ans = cnt;
}

void dfs(int idx) {
	if (ans == 0)
		return;
	if (idx == cctv.size()) {
		cpy = visit;
		chk();
		return;
	}
	for (int i = 0; i < 4; i++) {
		sequence[idx] = i;
		dfs(idx + 1);
	}

}

int main() {
	scanf("%d %d", &Y, &X);
	for (int i = 0; i < Y; i++) {
		vector<int> tmp(X);
		map.push_back(tmp);
		for (int j = 0; j < X; j++) {
			scanf("%d", &ans);
			if (ans == 6)
				map[i][j] = 6;
			else if (ans > 0)
				cctv.push_back({ i,j, ans });
		}
	}

	visit = map;
	for (int i = 0; i < cctv.size(); i++) {
		if (cctv[i].type == 5) {
			camera5(cctv[i]);
			cctv.erase(cctv.begin() + i);
			i--;
		}
	}
	
	sequence.clear();
	sequence.resize(cctv.size());

	ans = 65;
	dfs(0);

	printf("%d\n", ans);

	return 0;
}