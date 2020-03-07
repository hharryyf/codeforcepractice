#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 100011
typedef long long ll;
using namespace std;
// ans of the node v
ll ans[MAX_SIZE];
// (cnt, color)
set<pair<int, int> > occ[MAX_SIZE];
// color->cnt 
unordered_map<int, int> mp[MAX_SIZE];
vector<int> g[MAX_SIZE];
// f[i] refers to which set actually representing i
int f[MAX_SIZE];  
ll sm[MAX_SIZE];

void merge(int v1, int v2) {
	 int s1 = f[v1], s2 = f[v2];
	 // merge the smaller to larger
	 if (mp[s1].size() < mp[s2].size()) {
	 	auto iter = mp[s1].begin();
	 	while (iter != mp[s1].end()) {
			int color = iter->first, cnt = iter->second;
			auto p = *occ[s2].rbegin();
			int oc = mp[s2][color];
			if (oc + cnt == p.first) {
			   ans[s2] += color;
			} else if (oc + cnt > p.first) {
               ans[s2] = color;
			} 
			occ[s2].erase(make_pair(oc, s2));
			occ[s2].insert(make_pair(oc + cnt, s2)); 
			mp[s2][color] = oc + cnt;
	        iter++; 
	    }
	    f[v1] = f[s2];
	 } else {
	    auto iter = mp[s2].begin();
	 	while (iter != mp[s2].end()) {
			int color = iter->first, cnt = iter->second;
			auto p = *occ[s1].rbegin();
			int oc = mp[s1][color];
			if (oc + cnt == p.first) {
			   ans[s1] += color;
			} else if (oc + cnt > p.first) {
               ans[s1] = color;
			} 
			occ[s1].erase(make_pair(oc, s1));
			occ[s1].insert(make_pair(oc + cnt, s1)); 
			mp[s1][color] = oc + cnt;
	        iter++; 
	    }
	    f[v2] = f[s1];
	 }
}

void dfs(int v, int pre) {
	 for (auto nv : g[v]) {
	 	 if (nv != pre) {
		 	dfs(nv, v); 
         }
	 }
	 
	 for (auto nv : g[v]) {
	 	 if (nv != pre) {
	 	 	merge(v, nv);	 
         }
	 }
	 sm[v] = ans[f[v]];
}

int main() {
	int i, n;
	for (i = 0 ; i < MAX_SIZE; i++) f[i] = i;
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		int c;
		scanf("%d", &c);
		occ[i].insert(make_pair(1, c));
		mp[i][c]++;
		ans[i] = c;
	}
	
	for (i = 1 ; i < n; i++) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		g[v1].push_back(v2);
		g[v2].push_back(v1);
	}
	
	dfs(1, 0);
	
	for (i = 1; i <= n; i++) {
		printf("%lld ", sm[i]);
	}
	printf("\n");
	return 0;
}

