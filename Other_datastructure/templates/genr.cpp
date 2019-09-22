#include <bits/stdc++.h>

using namespace std;

void edgecases() {
	// edge cases 1
	cout << 2 << endl;
	cout << 1111111111 << endl;
	cout << 9999999999 << endl;
	// edge cases 2
	cout << 3 << endl;
	cout << 0 << endl;
	cout << 9999999999 << endl;
	cout << 1 << endl;
	// edge cases 3
	cout << 4 << endl;
	cout << 1111111111 << endl;
	cout << 999999999 << endl;
	cout << 8988888888 << endl;
	cout << 8088888880 << endl;
	cout << 8088888889 << endl;
	// edge cases 4
	cout << 5 << endl;
	cout << 1123456789 << endl;
	cout << 8976543210 << endl;
	cout << 10000000000 << endl;
	cout << 12345678 << endl;
	cout << 99999999999 << endl;
}

int main() {
	int T = 95;
	int n;
	srand(time(0));
	while (T > 0) {
		n = rand() % 1000;
		cout << n << endl;
		while (n > 0) {	
			long long v1 = rand();
			cout << v1 << endl;
			n--;
		}
		T--;
	}
	
	edgecases();
	return 0;
}
