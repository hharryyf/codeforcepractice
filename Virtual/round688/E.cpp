#include <bits/stdc++.h>
#define MAX_SIZE 200011
typedef long long ll;
using namespace std;

vector<int> g[MAX_SIZE];
int dp[MAX_SIZE];
int N, ans;

void dfs(int v, int p, int d) {
	dp[v] = d;
	vector<int> ret;
	for (auto nv : g[v]) {
		if (nv != p) {
			dfs(nv, v, d + 1);
			ret.push_back(dp[nv]);
		}
	}

	sort(ret.begin(), ret.end());
	if ((int) ret.size() > 1 && v != 1) {
		ans = max(ans, ret.back() - d + 1);
	}

	if ((int) ret.size() > 1 && v == 1) {
		ans = max(ans, ret[(int) ret.size() - 2] - d + 1);
	}

	if (!ret.empty()) {
		dp[v] = ret.front();
		ans = max(ans, ret.back() - d);
	}
}

int main() {
	int T, i;
	scanf("%d", &T);
	while (T-- > 0) {
		scanf("%d", &N);
		ans = 0;
		for (i = 1; i <= N; ++i) {
			dp[i] = 0;
			g[i].clear();
		}

		for (i = 0 ; i < N - 1; ++i) {
			int u, v;
			scanf("%d%d", &u, &v);
			g[u].push_back(v);
			g[v].push_back(u);
		}

		dfs(1, 0, 0);
		// cout << dp[1] << endl;
		printf("%d\n", ans);
	}
	return 0;
}