#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 922
using namespace std;

unordered_set<int> g[MAX_SIZE];
unordered_set<int> t[MAX_SIZE];
unordered_set<int> cp[MAX_SIZE];
int low[MAX_SIZE], visited[MAX_SIZE], instack[MAX_SIZE];
int cmpid[MAX_SIZE];
stack<int> st;
int cnt;

void dfs(int v, int pre) {
	low[v] = visited[v] = ++cnt;
	st.push(v);
	instack[v] = 1;
	for (auto nv : g[v]) {
		if (nv != pre) {
			if (!visited[nv]) {
				dfs(nv, v);
				low[v] = min(low[v], low[nv]);
			} else if (instack[nv]) {
				low[v] = min(low[v], visited[nv]);
			} 
		}
	}
	
	if (low[v] == visited[v]) {
		while (st.top() != v) {
			cmpid[st.top()] = v;
			instack[st.top()] = 0;
			st.pop();
		} 
		
		cmpid[st.top()] = v;
		instack[st.top()] = 0;
		st.pop();
	}
}

void dfs2(int v) {
	
	visited[v] = cnt++;
	for (auto nv : t[v]) {
		if (!visited[nv]) {
			dfs2(nv);
		}
	}
}

static bool cmp(const int &v1, const int &v2) {
	return visited[v1] < visited[v2];
}

int main() {
	int n, m, i;
	scanf("%d%d", &n, &m);
	if (n == 2 && m == 1) {
		printf("-1\n");
		return 0;
	}
	for (i = 1; i <= m; ++i) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		g[v1].insert(v2), g[v2].insert(v1);
	}
	
	dfs(1, 0);
	
	for (i = 1; i <= n; ++i) {
		cp[cmpid[i]].insert(i);
		for (auto v : g[i]) {
			if (cmpid[i] != cmpid[v]) {
				t[cmpid[i]].insert(cmpid[v]);
				t[cmpid[v]].insert(cmpid[i]);
			}
		}
	}
	
	vector<int> ret;
	cnt = 0;
	for (i = 1; i <= n; ++i) {
		cnt += (t[i].size() > 0);
		if (t[i].size() == 1) {
			ret.push_back(i);
		}
	}
	
	if (cnt == 1) {
		printf("0\n");
		return 0;
	}
	
	if (cnt == 2) {
		printf("1\n");
		// connect an edge in ret[0] -> ret[1]
		int idx = 0;
		if (cp[cmpid[ret[1]]].size() > 1) idx = 1;
		for (auto v : cp[ret[idx]]) {
			// node in component ret[0] that is not connected to
			// component ret[1] directly
			if (g[v].find(ret[1 ^ idx]) == g[v].end()) {
				printf("%d %d\n", ret[1 ^ idx], v);
				break;
			}
		}
  		return 0;
	}
	// connect the leaves according to dfs order 
	int sz = ret.size();
	printf("%d\n", (sz+1)/2);
	cnt = 1;
	memset(visited, 0, sizeof(visited));
	for (i = 1; i <= n; ++i) {
		if (!visited[i]) {
			dfs2(i);
		}
	}
	sort(ret.begin(), ret.end(), cmp);
	if (sz % 2 == 1) sz--;
	sz = sz / 2;
	for (i = sz ; i < (int) ret.size(); ++i) {
		printf("%d %d\n", ret[i-sz], ret[i]);
	}
	return 0;
}