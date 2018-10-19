//using prev_permutation 
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int X, Y, K, a, b, idx, ans = -1;
vector<vector<int>> map;
vector<pair<int, int>> canmake;
vector< pair<int, int>> back(4);

bool isright() {
	int cury, curx;
	for (int i = 1; i <= X; i++) {
		cury = 1; curx = i;
		while (cury < Y + 1) {
			if (map[cury][curx] == 1)
				curx++;
			else if (map[cury][curx] == -1)
				curx--;
			cury++;
		}
		if (i != curx)
			return false;
	}
	return true;
}

int main() {
	scanf("%d%d%d", &X, &K, &Y);
	for (int i = 0; i <= Y + 1; i++) {
		vector<int> tmp(X + 1);
		map.push_back(tmp);
	}
	for (int i = 0; i < K; i++) {
		scanf("%d %d", &a, &b);
		map[a][b] = 1;
		map[a][b+1] = -1;
	}

	for (int i = 1; i <= Y; i++) {
		for (int j = 1; j < X; j++) {
			if (map[i][j] == 0 && map[i][j + 1] == 0)
				canmake.push_back(make_pair(i, j));
		}
	}

	if (isright())
		ans = 0;
	else if(!canmake.empty()){
		vector<int> seq(canmake.size());
		for (int i = 1; i < 4; i++) {
			seq[i - 1] = 1;
			do {
				idx = 0;
				for (int j = 0; j < seq.size(); j++) {
					if (seq[j] == 1) {
						map[canmake[j].first][canmake[j].second] = 1;
						map[canmake[j].first][canmake[j].second + 1] = -1;
						back[idx] = make_pair(canmake[j].first, canmake[j].second);
						idx++;
					}
				}
				if (isright()) {
					ans = i;
					break;
				}
				while (idx > 0) {
					idx--;
					map[back[idx].first][back[idx].second] = 0;
					map[back[idx].first][back[idx].second + 1] = 0;
				}
			} while (prev_permutation(seq.begin(), seq.end()));
			if (ans > 0)
				break;
		}
	}
	printf("%d\n", ans);
	return 0;
}