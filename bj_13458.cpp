#include <iostream>
#include <vector>
using namespace std;

long long N, B, C;
long long a[1000000];

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> a[i];
	}
	cin >> B >> C;

	long long total(0);
	for (int i = 0; i < N; i++) {
		if (a[i] <= B)
			total++;
		else {
			a[i] -= B;
			if (a[i] % C == 0) {
				total += (a[i] / C + 1);
			}
			else {
				total += (a[i] / C + 2);
			}
		}
	}
	cout << total << "\n";
}