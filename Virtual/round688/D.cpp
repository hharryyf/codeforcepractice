#include <iostream>
#include <vector>
#define lli int64_t
using namespace std;

int t;
lli k;
int main() {
	cin >> t;
	while (t--) {
		cin >> k;
		if (k % 2 == 1) {
			cout << -1 << endl;
			continue;
		}

		k /= 2;
		vector<int> ints;
		for (int shift = 0; shift < 62; shift++) {
			if (k & (1LL<<shift)) {
				ints.push_back(1);
				if (shift >= 1) {
					ints.push_back(1);
					for (int i = 1; i < shift; i++) {
						ints.push_back(0);
					}
				}
			}
		}

		cout << ints.size() << endl;
		for (int x : ints) cout << x << ' ';
		cout << endl;
	}
}
