#include <bits/stdc++.h>
#define MAX_SIZE 101111
#define INF 1000000000000000

typedef long long ll;

using namespace std;

/*
	This problem could be divided into two parts.
	1. determine the w[i] and d[i] for each day
	2. solve the original dp problem based on the w[i] and d[i]
	
	The first subproblem given k ranges [s, t], 1 <= s <= t <= n, 
	each range has a w[i] and a d[i], we need to find the maximum(w[i], d[i]) pair
	for each day 1 <= day <= n.
	
	we store 2 vectors, the first one is the start vector, the second vector
	is the end vector, then the process is a standard line sweeping procedure.
	
	The second part would be a dp problem, given  
	
*/

vector<pair<ll, int> > inq[MAX_SIZE], leave[MAX_SIZE];
multiset<pair<ll, int> > s;
int n, m, k;

ll dp[2][MAX_SIZE];

// the w,d pair for each day
pair<ll, int> days[MAX_SIZE];

int main() {
	scanf("%d%d%d", &n, &m, &k);
	int i, j;
	for (i = 0 ; i < k; i++) {
		int st,ed,dd;
		ll w;
		scanf("%d%d%d%lld", &st, &ed, &dd, &w);
		inq[st].emplace_back(w, dd);
		leave[ed].emplace_back(w, dd);
	}
	
	for (i = 1; i <= n; i++) {
		for (auto p : inq[i]) {
			s.insert(p);
		}
		
		if (s.empty()) {
			days[i].first = 0ll;
			days[i].second = 0;
		} else {
			days[i].first = s.rbegin()->first;
			days[i].second = s.rbegin()->second;
		}
		
		for (auto p : leave[i]) {
			s.erase(s.find(p));
		}
	}
	
	/*
		dp[i][j] refers to the minimum number of coins the person can get
		with at most i optimal disturb and use day [j:n]
		dp[i][j] = min(dp[i-1][j+1], dp[i][days[j].second + 1] + days[j].first)
	*/
	 
	for (i = n; i >= 1; i--) {
		dp[0][i] = dp[0][days[i].second + 1] + days[i].first;
		if (days[i].first == 0 && dp[0][i] == 0) {
			dp[0][i] = dp[0][i+1];
		}
	}
	
	for (i = 1; i <= m; i++) {
		for (j = n; j >= 1; j--) {
			dp[i % 2][j] = min(dp[(i-1) % 2][j+1], dp[i % 2][days[j].second + 1] + days[j].first);
			if (dp[i % 2][j] == 0 && days[j].first == 0) {
				dp[i % 2][j] = dp[i % 2][j + 1];
			} else if (days[j].first == 0) {
				dp[i % 2][j] = min(dp[i % 2][j + 1], dp[i % 2][j]);
			}
		}
	}
	
	printf("%lld\n", dp[m % 2][1]);
	return 0;
}
