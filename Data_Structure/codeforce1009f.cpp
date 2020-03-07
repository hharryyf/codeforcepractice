#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 1000011
typedef long long ll;
using namespace std;
// cnt->depth
set<pair<int, int> > st[MAX_SIZE];
// depth -> cnt
unordered_map<int, int> mp[MAX_SIZE];
int dep[MAX_SIZE], f[MAX_SIZE];
int ans[MAX_SIZE];
vector<int> g[MAX_SIZE];

void merge(int v1, int v2) {
	 int s1 = f[v1], s2 = f[v2];
	 if (mp[s1].size() < mp[s2].size()) {
	 	auto iter = mp[s1].begin();
	 	while (iter != mp[s1].end()) {
			int d = iter->first, ct = iter->second;
			int occ = mp[s2][d];
			mp[s2][d] = occ + ct;
			st[s2].erase(make_pair(occ, -d));
			st[s2].insert(make_pair(ct+occ, -d));
	        iter++; 
	    }
	 	f[v1] = s2;
	 } else {
	    auto iter = mp[s2].begin();
	 	while (iter != mp[s2].end()) {
			int d = iter->first, ct = iter->second;
			int occ = mp[s1][d];
			mp[s1][d] = occ + ct;
			st[s1].erase(make_pair(occ, -d));
			st[s1].insert(make_pair(ct+occ, -d));
	        iter++; 
	    }
	    f[v2] = s1;
	 }
}

void dfs(int v, int pre) {
	 dep[v] = dep[pre] + 1;
	 st[v].insert(make_pair(1, -dep[v]));
	 mp[v][dep[v]] = 1;
	 for (auto nv : g[v]) {
	 	 if (nv != pre) {
         	dfs(nv, v);
		 }
	 }
	 
	 for (auto nv : g[v]) {
	 	 if (nv != pre) {
         	merge(nv, v);
		 }
	 }
	 
	 auto p = *st[f[v]].rbegin();
	 ans[v] = -p.second - dep[v];
}

int main() {
	int i, n;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) f[i] = i;
	for (i = 1; i < n; ++i) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		g[v1].push_back(v2);
		g[v2].push_back(v1);
	}
	
	dfs(1, 0);
	
	for (i = 1; i <= n; i++) {
		printf("%d\n", ans[i]);
	}
	return 0;
}

