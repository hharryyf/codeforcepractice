#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 200011
using namespace std;

map<int, int> st;
vector<pair<int, int>> disc;
pair<ll, int> a[MAX_SIZE];
pair<ll, int> b[MAX_SIZE];
int n, k;

int main() {
	int i;
	scanf("%d%d", &n, &k);
	for (i = 1; i <= n; ++i) {
		int v;
		scanf("%d", &v);
		st[v]++;
	}
	
	auto iter = st.begin();
	while (iter != st.end()) {
		disc.emplace_back(iter->first, iter->second);
		++iter;
	}
	
	int sz = disc.size();
	if (sz == 1) {
		printf("0\n");
		return 0;
	}
	for (i = 0 ; i < sz; ++i) {
		if (i == 0) {
			a[i] = {0, disc[i].second};
		} else {
			a[i] = {a[i-1].first + 1ll * (disc[i].first - disc[i-1].first) * a[i-1].second, a[i-1].second + disc[i].second};
		}
	}
	
	for (i = sz - 1; i >= 0; --i) {
		if (i == sz - 1) {
			b[i] = {0, disc[i].second};
		} else {
			b[i] = {b[i+1].first + 1ll * (-disc[i].first+disc[i+1].first) * b[i+1].second, b[i+1].second + disc[i].second};
		}
	}
	
	ll ans = 100000000000000000ll;
	for (i = 0 ; i < sz; ++i) {
		ll cL = (i == 0 ? 0 :  a[i-1].first + 1ll * a[i-1].second * (disc[i].first - disc[i-1].first - 1));
		ll cR = (i == sz-1 ? 0 : b[i+1].first + 1ll * b[i+1].second * (disc[i+1].first - disc[i].first - 1));
		int L = (i == 0 ? 0 : a[i-1].second), R = (i == sz-1 ? 0 : b[i+1].second);
		int delta = k - disc[i].second;
		if (disc[i].second >= k) {
			ans = 0;
		} else {
			if (L < delta && R < delta) {
				ans = min(ans, cL + cR + delta);
			} else if (L < delta) {
				ans = min(ans, cR + delta);
			} else if (R < delta) {
				ans = min(ans, cL + delta);
			} else {
				ans = min(ans, min(cL, cR) + delta);
			}
		}
		// cout << delta << endl;
		// cout << i << " (" << cL << ", " << L << ") " << "(" << cR << ", " << R << ")" << ans << endl;
	}
	
	printf("%I64d\n", ans);
	return 0;
}