#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 1000111
#define REP(i,a,b) for(i=a;i<=b;++i)
using namespace std;

multiset<int> st[MAX_SIZE];
vector<int> g[MAX_SIZE];
int deg[MAX_SIZE];
int dep[MAX_SIZE];
int f[MAX_SIZE];
int k;

void merge(int v1, int v2) {
	int d = dep[v2];
	int s1 = f[v1], s2 = f[v2];
	if (st[s1].size() < st[s2].size()) {
		// merge s1 to s2
		// condition for a merge is depth[s1_i]  + dep[s2_i] <= k + 2 * d
		// dep[s2_i] <= k + 2 * d - depth[s1_i]
		// we find the prev of upper_bound of k + 2 * d - depth[s1_i]
		// if the element exists we insert eliminate the element 
		// and insert max(dep[s1_i], element) into s2
		// otherwise, we directly insert dep[s1_i] to s2
		for (auto v : st[s1]) {
			auto iter = st[s2].upper_bound(k + 2 * d - v);
			if (iter == st[s2].begin()) {
				st[s2].insert(v);
			} else {
				iter = prev(iter);
				int nv = max(*iter, v);
				st[s2].erase(iter);
				st[s2].insert(nv);
			}
		}
		f[v1] = s2;
	} else {
		// merge s2 to s1
		for (auto v : st[s2]) {
			auto iter = st[s1].upper_bound(k + 2 * d - v);
			if (iter == st[s1].begin()) {
				st[s1].insert(v);
			} else {
				iter = prev(iter);
				int nv = max(*iter, v);
				st[s1].erase(iter);
				st[s1].insert(nv);
			}
		}
		f[v2] = s1;
	}
}

void dfs(int v, int pre) {
	dep[v] = dep[pre] + 1;
	if (deg[v] == 1) {
		st[f[v]].insert(dep[v]);
		return;
	}
	
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
}

int main() {
	int i, n;
	scanf("%d%d", &n, &k);
	REP (i,1,n-1) {
		f[i] = i;
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		g[v1].push_back(v2);
		g[v2].push_back(v1);
		++deg[v1], ++deg[v2];
	}
	
	f[n] = n;
	
	REP (i, 1, n) {
		if (deg[i] > 1) {
			dfs(i, 0);
			printf("%d\n", (int) st[f[i]].size());
			break;
		}
	}
	return 0;
}