#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

struct xy {
	int y;
	int x;
	void set(int yy, int xx) {
		y = yy;
		x = xx;
	}
	friend bool operator==(xy a, xy b) {
		return (a.x == b.x) && (a.y == b.y);
	}
};
int X, Y;
char c;
vector<vector<int>> map;
xy r, b, hole;
queue<pair<xy, xy>> q;
queue<int> cnt;

bool left() {
	int cr = r.x, cb = b.x;
	while (cr > 0) {
		if (map[r.y][cr - 1] != 1 && map[r.y][cr - 1] != 5)
			cr--;
		else if (map[r.y][cr - 1] == 5) {
			cr--;
			break;
		}
		else	
			break;
	}
	while (cb > 0) {
		if (map[b.y][cb - 1] != 1 && map[b.y][cb - 1] != 5)
			cb--;
		else if (map[b.y][cb - 1] == 5) {
			cb--;
			break;
		}
		else
			break;
	}
	if (r.y == b.y && cr == cb && map[r.y][cr] != 5) {
		if (r.x < b.x)
			cb++;
		else
			cr++;
	}
	if (r.x == cr && b.x == cb)
		return false;
	r.x = cr;	b.x = cb;
	return true;
}
bool right() {
	int cr = r.x, cb = b.x;
	while (cr < X - 1) {
		if (map[r.y][cr + 1] != 1 && map[r.y][cr + 1] != 5)
			cr++;
		else if (map[r.y][cr + 1] == 5) {
			cr++;
			break;
		}
		else
			break;
	}
	while (cb < X - 1) {
		if (map[b.y][cb + 1] != 1 && map[b.y][cb + 1] != 5)
			cb++;
		else if (map[b.y][cb + 1] == 5) {
			cb++;
			break;
		}
		else
			break;
	}
	if (r.y == b.y && cr == cb && map[r.y][cr] != 5) {
		if (r.x > b.x)
			cb--;
		else
			cr--;
	}
	if (r.x == cr && b.x == cb)
		return false;
	r.x = cr;	b.x = cb;
	return true;
}
bool down() {
	int cr = r.y, cb = b.y;
	while (cr < Y - 1) {
		if (map[cr + 1][r.x] != 1 && map[cr + 1][r.x] != 5)
			cr++;
		else if (map[cr + 1][r.x] == 5) {
			cr++;
			break;
		}
		else
			break;
	}
	while (cb < Y - 1) {
		if (map[cb + 1][b.x] != 1 && map[cb + 1][b.x] != 5)
			cb++;
		else if (map[cb + 1][b.x] == 5) {
			cb++;
			break;
		}
		else
			break;
	}
	if (r.x == b.x && cr == cb && map[cb][b.x] != 5) {
		if (r.y > b.y)
			cb--;
		else
			cr--;
	}
	if (r.y == cr && b.y == cb)
		return false;
	r.y = cr;	b.y = cb;
	return true;
}
bool up() {
	int cr = r.y, cb = b.y;
	while (cr > 0) {
		if (map[cr - 1][r.x] != 1 && map[cr - 1][r.x] != 5)
			cr--;
		else if (map[cr - 1][r.x] == 5) {
			cr--;
			break;
		}
		else	
			break;
	}
	while (cb > 0) {
		if (map[cb - 1][b.x] != 1 && map[cb - 1][b.x] != 5)
			cb--;
		else if (map[cb - 1][b.x] == 5) {
			cb--;
			break;
		}
		else
			break;
	}
	if (r.x == b.x && cr == cb && map[cb][b.x] != 5) {
		if (r.y < b.y)
			cb++;
		else
			cr++;
	}
	if (r.y == cr && b.y == cb)
		return false;
	r.y = cr;	b.y = cb;
	return true;
}
bool move(int n) {
	if (n == 0)
		return right();
	else if (n == 1)
		return down();
	else if (n == 2)
		return left();
	else
		return up();
}


int main() {
	scanf("%d%d", &Y, &X);
	for (int i = 0; i < Y; i++) {
		vector<int> tmp(X);
		map.push_back(tmp);
		for (int j = 0; j < X; j++) {
			scanf(" %c", &c);
			if (c == '#')
				map[i][j] = 1;
			else if (c == 'R')
				r.set(i, j);
			else if (c == 'B')
				b.set(i, j);
			else if (c == 'O') {
				map[i][j] = 5;
				hole.set(i, j);
			}
		}
	}

	int ans = 11, curcnt = 0, find = 0;
	q.push(make_pair(r, b));
	cnt.push(0);
	pair<xy, xy> cur;
	while (!q.empty() && curcnt < 10) {
		curcnt = cnt.front();	cnt.pop();
		cur = q.front();		q.pop();
		for (int i = 0; i < 4; i++) {
			r = cur.first;	b = cur.second;
			if (!move(i)) {
				map[r.y][r.x] = 0;
				map[b.y][b.x] = 0;
				continue;
			}
			if (b == hole)
				;
			else if (r == hole) {
				ans = curcnt + 1;
				find = 1;
			}
			else {
				cnt.push(curcnt + 1);
				q.push(make_pair(r, b));
			}
			if (find == 1)
				break;
		}
		if (find == 1)
			break;
	}
	if (ans == 11)
		ans = -1;
	printf("%d\n", ans);
	return 0;
}
