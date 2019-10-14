#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

vector<vector<ll> > dp = vector<vector<ll> >(1 << 18, vector<ll>(100, -1));
string str;
int m;

ll dfs(int pos, int bi, int rem) {
	if (pos == (int) str.length()) return (rem == 0);
	if (dp[bi][rem] != -1) return dp[bi][rem];
	int i;
	ll ans = 0;
	for (i = 0 ; i < (int) str.length(); i++) {
		if ((bi & (1 << i)) == 0) {
			if (pos != 0 || str[i] - '0' != 0) {
				ans = ans + dfs(pos + 1, bi | (1 << i), (rem * 10 + (str[i] - '0')) % m);
			}
		}
	}
	
	return dp[bi][rem] = ans;
}

int main() {
	ll n;
	scanf("%lld%d", &n, &m);
	str = to_string(n);
	ll duplicate = 1ll;
	unordered_map<char, int> h;
	for (auto ch : str) {
		h[ch]++;
		duplicate = duplicate * (ll) h[ch];
	}
	
	cout << dfs(0, 0, 0) / duplicate << endl;
	return 0;
}
