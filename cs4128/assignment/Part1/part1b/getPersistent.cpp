#include <bits/stdc++.h>

using namespace std;

int main() {
	srand(time(NULL));
	int n, q;
	int vs = 1;
	n = 50000 + rand() % 50000;
	q = 50000 + rand() % 50000;
	cout << n << " " << q << endl;
	while (q > 0) {
		int t = rand() % 2;
		int l = rand() % n, r = 1 + rand() % n;
		if (l > r) swap(l, r);
		if (l == r) {
			r++;
		}
		if (t == 1) {
			int val = 1 + rand() % 10000;
			cout << 'U' << " " << l << " " << r << " " << val << endl;
			vs++;
		} else {
			cout << 'Q' << " ";
			cout << rand() % vs << " " << l << " " << r << endl;;
		}
		q--;
	}
	return 0;
}
