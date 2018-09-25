//#include <cstdio>
//#include <queue>
//
//using namespace std;
//
//struct xy {
//	int x, y, brk;
//	xy(int b, int a, int c) {
//		y = b; x = a;
//		brk = c;
//	}
//	bool operator < (xy b)const {
//		return brk > b.brk;
//	}
//};
//
//priority_queue< xy > q;	//min heap
//int X,Y, answer(100);
//int xx[4] = { 1,-1,0,0 };
//int yy[4] = { 0,0,1,-1 };
//int g[101][101];
//int v[101][101];
//
//int main() {
//	scanf("%d%d", &X, &Y);
//	for (int i = 1; i <= Y; i++) {
//		for (int j = 1; j <= X; j++) {
//			scanf("%1d", &g[i][j]);
//		}
//	}
//
//	xy cur(1, 1, 0);
//	v[1][1] = 1;
//	q.push(cur);
//	int ny, nx;
//
//	while (!q.empty()) {
//		cur = q.top();
//		q.pop();
//		if (cur.x == X && cur.y == Y) {
//			printf("%d\n", cur.brk);
//			return 0;
//		}
//
//		for (int i = 0; i < 4; i++) {
//			ny = cur.y + yy[i];
//			nx = cur.x + xx[i];
//			if (ny<1 || nx<1 || nx>X || ny>Y)
//				continue;
//			if (v[ny][nx] == 0) {
//				v[ny][nx] = 1;
//
//				if (g[ny][nx] == 0)
//					q.push({ ny,nx,cur.brk });
//				else
//					q.push({ ny,nx,cur.brk + 1 });
//			}
//		}
//	}
//
//	return 0;
//}