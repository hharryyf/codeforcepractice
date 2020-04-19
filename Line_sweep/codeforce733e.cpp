#include <bits/stdc++.h>
#define MAX_SIZE 1000111
typedef long long ll;
using namespace std;

char s[MAX_SIZE];
ll ans[MAX_SIZE];
int n;

void solve() {
	vector<ll> up, down;
	int i;
	for (i = n; i >= 1; --i) {
		if (s[i] == 'D') {
			if (down.empty()) {
				down.push_back(i);
			} else {
				down.push_back(down.back() + i);
			}
		}
	}
	
	for (i = 1; i <= n; ++i) {
		int sz1 = up.size(), sz2 = down.size();
		// up->down->up->down->up->...
		if (s[i] == 'U') {
			if (sz2 > sz1) {
				ans[i] = (down[sz2- 1] - ((sz2 - sz1 >= 2) ? down[sz2 - sz1 - 2] : 0)) * 2 - (sz1 != 0 ? up[sz1-1] * 2 : 0) - i;
			} else {
				ans[i] = (sz2 != 0 ? down[sz2-1] * 2 : 0) - ((sz1 != 0 ? up[sz1-1] : 0) - (sz2 != sz1 ? up[sz1 - sz2-1] : 0)) * 2 + n + 1 - i;
			}
			
			if (up.empty()) {
				up.push_back(i);
			} else {
				up.push_back(up.back() + i);
			}
		} else {
			down.pop_back();
			--sz2;
			if (sz1 > sz2) {
				ans[i] = (sz2 != 0 ? down[sz2 - 1] * 2 : 0) + n + i + 1 - (up[sz1 - 1] - ((sz1 - sz2 >= 2) ? up[sz1 - sz2 - 2] : 0)) * 2;
			} else {
				ans[i] = i - (sz1 != 0 ? up[sz1-1] * 2 : 0) + ((sz2 != 0 ? down[sz2-1] : 0) - (sz2 != sz1 ? down[sz2 - sz1-1] : 0)) * 2;
			}
		}
	}
}

void solve_down() {
	
}

int main() {
	int i;
	scanf("%d", &n);
	scanf("%s", s + 1);
	solve();
	for (i = 1; i <= n; ++i) printf("%I64d ", ans[i]);
	return 0;
}