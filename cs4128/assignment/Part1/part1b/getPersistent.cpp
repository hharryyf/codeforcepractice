#include <bits/stdc++.h>

using namespace std;

int main() {
	srand(time(NULL));
	int n, q;
	int vs = 1;
	n = 1000 + rand() % 1000;
	q = n + rand() % n;
	cout << n << " " << q << endl;
	while (q > 0) {
		int t = rand() % 2;
		int l = 1 + rand() % n, r = 1 + rand() % n;
		if (l > r) swap(l, r);
		if (l == r) {
			r++;
		}
		if (t == 1) {
			int val = -500 + rand() % 10007;
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
