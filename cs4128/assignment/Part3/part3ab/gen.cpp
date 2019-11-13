#include <bits/stdc++.h>

using namespace std;

int main() {
	srand(time(NULL));
	int n = 20 + rand() % 50000;
	int m = 2 * n + rand() % n;
	int q = m + rand() % n;
	cout << n << " " << m << endl;
	cout << q << endl;
	while (m > 0) {
		int v1 = 1 + rand() % n;
		int v2 = 1 + rand() % n;
		int ti = 1 + rand() % (2 * n);
		cout << v1 << " " << v2 << " " << ti << endl;
		m--;
	}
	
	while (q > 0) {
		int ti = 1 + rand() % (2 * n);
		int ci = 1 + rand() % n;
		cout << ti << " " << ci << endl;
		q--;
	}
	return 0;
}
