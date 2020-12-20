#include <iostream>
#define lli int64_t
using namespace std;

int t, a, b, c;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> t;
	while (t--) {
		cin >> a >> b >> c;
		if ((a+b+c)%9 != 0) {
			cout << "NO" << endl;
		} else {
			lli cycles = (a+b+c)/9;
			if (a<cycles||b<cycles||c<cycles) {
				cout << "NO" << endl;
			} else {
				cout << "YES" << endl;
			}
		}
	}
}
