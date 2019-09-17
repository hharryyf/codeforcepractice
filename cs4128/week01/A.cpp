#include <vector>
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	int n, i, ans = 0;
	scanf("%d", &n);
	for (i = 1; i * (i + 1) <= 2 * n; i++) {
		if ((2 * n) % i == 0) {
			if (i % 2 == 1) {
				ans++;
			} else {
				if (((2 * n) / i) % 2 == 1) ans++;
			}
		}
	}
	
	cout << ans << endl;
	return 0;
}
