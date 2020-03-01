#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 100111
typedef long long ll;
using namespace std;

int n, m;
int prefix[MAX_SIZE];
vector<int> g[MAX_SIZE];
unordered_set<int> g2[MAX_SIZE];
// run tarjan on g to construct the compressed graph
int cmpsz[MAX_SIZE];
int cmpid[MAX_SIZE];
int visited[MAX_SIZE], low[MAX_SIZE], instack[MAX_SIZE];
stack<int> st;
int cnt = 1;
int kcnt = 1;
void tarjan(int v, int pre) {
	low[v] = visited[v] = cnt;
	cnt++;
	st.push(v);
	instack[v] = 1;
	for (auto nv : g[v]) {
		if (nv != pre) {
		   if (!visited[nv]) {
		   	   tarjan(nv, v);
		   	   low[v] = min(low[v], low[nv]);
		   } else if (instack[nv]) {
		   	   low[v] = min(low[v], visited[nv]);
		   }
		}
	}	 	 
	
	if (low[v] == visited[v]) {
	   while (st.top() != v) {
	   		 instack[st.top()] = 0;
	   		 cmpid[st.top()] = kcnt;
	   		 st.pop();
	   }
	   instack[v] = 0;
	   st.pop();
	   cmpid[v] = kcnt++;
	}	 
}
// we use hld to solve this problem, just for practice
int id[MAX_SIZE], rid[MAX_SIZE], top[MAX_SIZE], son[MAX_SIZE];
int f[MAX_SIZE], sz[MAX_SIZE], wt[MAX_SIZE], dep[MAX_SIZE];
int c = 1;
void dfs1(int v, int pre) {
    f[v] = pre;
    dep[v] = dep[pre] + 1;
    sz[v] = 1;
    int max_child = 0;
    for (auto nv : g2[v]) {
		if (nv != pre) {
		   dfs1(nv, v);
		   sz[v] += sz[nv];
		   if (sz[nv] > max_child) {
		   	  max_child = sz[nv];
		   	  son[v] = nv;
		   }
		}
	}
}

void dfs2(int v, int tp) {
	top[v] = tp;
	id[v] = c++;
	rid[id[v]] = v;
	if (son[v]) {
	   dfs2(son[v], tp);
	}
	
	for (auto nv : g2[v]) {
		if (nv != f[v] && nv != son[v]) {
		   dfs2(nv, nv);
		}
	}
}

int hld(int x, int y) {
	int fx = top[x], fy = top[y];
	int ret = 0;
	while (fx != fy) {
		  if (dep[fx] >= dep[fy]) {
		  	 ret += prefix[id[x]] - prefix[id[fx] - 1];
		  	 x = f[fx], fx = top[x];
		  } else {
		  	 ret += prefix[id[y]] - prefix[id[fy] - 1];
		  	 y = f[fy], fy = top[y];
		  }
	}	
	
	if (id[x] <= id[y]) {
	   ret += prefix[id[y]] - prefix[id[x] - 1];
	} else {
	   ret += prefix[id[x]] - prefix[id[y] - 1];
	}
	return ret;
}

ll pow2(int p) {
	ll ret = 1;
	ll base = 2;
	while (p > 0) {
		  if (p % 2 == 0) {
		  	 base = (base * base) % MOD;
		  	 p /= 2;
		  } else {
		  	 ret = (ret * base) % MOD;
		  	 p--;
		  }
	}
	return ret;
}

int main() {
    scanf("%d%d", &n, &m);
    int i;
    for (i = 0 ; i < m; i++) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		g[v1].push_back(v2);
		g[v2].push_back(v1);
	}
	
	tarjan(1, 0);
	
	for (i = 1; i <= n; i++) {
		cmpsz[cmpid[i]]++;
	}
	
	for (i = 1; i < kcnt; i++) {
		wt[i] = (cmpsz[i] > 1);
	}
	
	for (i = 1; i <= n; i++) {
		for (auto v : g[i]) {
			if (cmpid[v] != cmpid[i]) {
			   g2[cmpid[v]].insert(cmpid[i]);
			   g2[cmpid[i]].insert(cmpid[v]);
			}
		}
	}
	
	dfs1(1, 0);
	dfs2(1, 1);
	
	for (i = 1; i < kcnt; i++) {
		prefix[i] = prefix[i-1] + wt[rid[i]];
	}
	
	int q;
	scanf("%d", &q);
	while (q > 0) {
		  int u, v;
		  scanf("%d%d", &u, &v);
		  printf("%lld\n", pow2(hld(cmpid[u], cmpid[v])));
		  q--;
	}
	return 0;
}


