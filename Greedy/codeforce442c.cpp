#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

vector<int> st;
ll ans = 0;

int main() {
	int i, n;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) {
		int v;
		scanf("%d", &v);
		int sz = st.size();
		while (sz >= 2) {
			if (st[sz-1] <= v && st[sz-1] <= st[sz-2]) {
				ans += 1ll * min(st[sz-2], v);
				st.pop_back();
				sz--;
			} else {
				break;
			}
		}
		st.push_back(v);
	}
	
	sort(st.begin(), st.end());
	
	for (i = 0 ; i < (int) st.size() - 2; ++i) {
		ans += 1ll * st[i];
	}
	
	printf("%I64d\n", ans);
	return 0;
}