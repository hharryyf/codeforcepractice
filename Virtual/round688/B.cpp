#include <iostream>
#define int int64_t
#define MAXN 200005
using namespace std;

int t, n, a[MAXN];
int32_t main() {
	cin >> t;
	while (t--) {
		cin >> n;
		for (int i = 1; i <= n; i++) cin >> a[i];
		int sum = 0;
		int bst = 0;
		for (int i = 1; i < n; i++) {
			sum += abs(a[i] - a[i+1]);
		}
		for (int i = 1; i <= n; i++) {
			int save = 0;
			if (i == 1) {
				save = abs(a[i] - a[i+1]);
			} else if (i == n) {
				save = abs(a[i-1] - a[i]);
			} else {
				save = (abs(a[i-1]-a[i]) + abs(a[i]-a[i+1])) - abs(a[i-1]-a[i+1]);
			}
			bst = max(bst, save);
		}
		cout << (sum-bst) << endl;
	}
}
