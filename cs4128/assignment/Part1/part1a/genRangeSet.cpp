#include <bits/stdc++.h>

using namespace std;

int main() {
	srand(time(NULL));
	int n = 12 + rand() % 1000;
	int q = 20 + rand() % 2000;
	if (q > n * n) {
		q = n * n;
	}
	
	if (q < n) {
		q = n;
	}
	
	cout << n << " " << q << endl;
	int t = n;
	while (t > 0) {
		cout << -50 + rand() % 50 << endl;
		t--;
	}
	
	while (q > 0) {
		int l = 1 + rand() % n;
		int r = 1 + rand() % n;
		if (l > r) {
			cout << r << " " << l << endl;
		} else {
			cout << l << " " << r << endl;
		}
		q--;
	}
	return 0;
}
