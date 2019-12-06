#include <bits/stdc++.h>
#define MAX_SIZE 101111

typedef long long ll;

using namespace std;

ll dp[MAX_SIZE][2];

vector<pair<int, ll> > g[MAX_SIZE];

int n, k;

static bool cmp(const pair<ll, pair<int, ll> > &a, const pair<ll, pair<int, ll> > &b) {
	return a.first > b.first;
}


void dfs(int v, int pre) {
	vector<pair<ll, pair<int, ll> > > child;
	
	for (auto nd : g[v]) {
		if (nd.first != pre) {
			dfs(nd.first, v);
			child.emplace_back(nd.second + dp[nd.first][0], make_pair(nd.first, nd.second));
		}
	}
	
	sort(child.begin(), child.end(), cmp);
	
	for (int i = 0 ; i < k - 1 && i < (int) child.size(); i++) {
		dp[v][0] += child[i].first;
	}
	
	for (int i = 0 ; i < (int) child.size(); i++) {
		if (i < k - 1) {
			dp[v][1] = max(dp[v][1], dp[v][0] - child[i].first 
									 + dp[child[i].second.first][1] 
									 + child[i].second.second + ((int) child.size() >= k ? child[k-1].first : 0));
		} else {
			dp[v][1] = max(dp[v][1], dp[v][0] + dp[child[i].second.first][1]  + child[i].second.second);
		}
	}
}

int main() {
	scanf("%d%d", &n, &k);
	int i;
	for (i = 0 ; i < n - 1; i++) {
		int v1, v2;
		ll w;
		scanf("%d%d%lld", &v1, &v2, &w);
		g[v1].push_back(make_pair(v2, w));
		g[v2].push_back(make_pair(v1, w));
	}
	
	dfs(0, -1);
	
	
	printf("%lld\n", max(dp[0][0], dp[0][1]));
	return 0;
}
