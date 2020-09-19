#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
ll t, a, b;

void solve() {
	if (a < b) {
		ll tmp = a;
		a = b;
		b = tmp;
	}
	if (a % b != 0) {
		cout << -1 << endl;
		return;
	}

	int shifts = 0;
	while (a > b && (a % 2 == 0)) {
		a >>= 1L;
		shifts += 1;
	}

	if (a != b) {
		cout << -1 << endl;
		return;
	}

	cout << ((shifts / 3) + (shifts % 3 == 0 ? 0 : 1)) << endl;
}

int main() {
	cin >> t;
	while (t--) {
		cin >> a >> b;
		solve();
	}
}
