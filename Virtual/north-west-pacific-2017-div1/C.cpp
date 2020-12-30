#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 1000011
using namespace std;

int main() {
	ll i, j, l, r, ans = 0;
	cin >> l >> r;
	for (i = 1; i <= 1000000; ++i) {
		ll low = l / i * i;
		if (low < l) low += i;
		for (j = low; j <= r; j = j + i) {
			if (i * i < j) {
				ans = ans + i;
				ans += j / i;
			} else if (i * i == j) {
				ans += i;
			}
		}
	}

	cout << ans << endl;
	return 0;
}