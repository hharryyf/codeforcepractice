#include <bits/stdc++.h>
#define MAX_SIZE 500111
using namespace std;

vector<int> in[MAX_SIZE];
int dp[MAX_SIZE][20];
const int maxn = 500000;

int main() {
	int n, m, i, j;
	scanf("%d%d", &n, &m);
	set<int> st;
	for (i = 1; i <= n; ++i) {
		int l, r;
		scanf("%d%d", &l, &r);
		in[l].push_back(r);
	}
	
	for (i = 0; i <= maxn; ++i) {
		for (auto v : in[i]) st.insert(v);
		if (st.empty()) dp[i][0] = -1;
		else {
			dp[i][0] = *st.rbegin();
		}
		
		st.erase(i);
	}
	
	for (j = 1; j <= 19; ++j) {
		for (i = 0 ; i <= maxn; ++i) {
			if (dp[i][j-1] == -1) {
				dp[i][j] = -1;
			} else {
				dp[i][j] = dp[dp[i][j-1]][j-1];
			}
		}
	}
	
	while (m > 0) {
		int l, r, ans = 0;
		scanf("%d%d", &l, &r);
		for (i = 19; i >= 0; --i) {
			if (dp[l][i] < r && dp[l][i] >= 0) {
				ans = ans + (1 << i);
				l = dp[l][i];
			}
		}
		
		if (dp[l][0] >= r) ans++;
		else {
			ans = -1;
		}
		printf("%d\n", ans);
		m--;
	}
	return 0;
}