#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 200111
typedef long long ll;
using namespace std;

// the original graph
vector<int> g[MAX_SIZE];
// the point compressed forest
unordered_set<int> t[MAX_SIZE];
ll cost[MAX_SIZE];
ll weight[MAX_SIZE];
int cmpid[MAX_SIZE];
int low[MAX_SIZE];
int visited[MAX_SIZE];
stack<int> s;
int instack[MAX_SIZE];
int k = 1;
int src;
int n, m;

void tarjan(int v, int pre) {
    low[v] = visited[v] = k++;
    instack[v] = true;
    s.push(v);
    for (auto nv : g[v]) {
        if (nv != pre) {
            if (instack[nv]) {
                low[v] = min(low[v], visited[nv]);
            } else if (!visited[nv]){
                tarjan(nv, v);
                low[v] = min(low[v], low[nv]);
            }
        }
    }
    
    if (low[v] == visited[v]) {
        while (s.top() != v) {
            cmpid[s.top()] = v;
            instack[s.top()] = false;
            s.pop();
        }
        cmpid[s.top()] = v;
        instack[s.top()] = false;
        s.pop();
    }
}

int cmpsz[MAX_SIZE];
ll dp[MAX_SIZE];

void dfs2(int v, int pre) {
    dp[v] = weight[v];
    for (auto nv : t[v]) {
        if (nv != pre) {
            dfs2(nv, v);
            dp[v] = max(dp[v], dp[nv] + weight[v]);
        }
    }
}

void dfs1(int v, int pre) {
	 for (auto nv : t[v]) {
	 	 if (nv != pre) {
		    dfs1(nv, v);
			if (cmpsz[nv] > 1) {
			    cmpsz[v] += cmpsz[nv];
			    cmpsz[nv] = 0;
			    weight[v] += weight[nv];
			    weight[nv] = 0;
			}  
         }
	 }
}

int main() {
    scanf("%d%d", &n, &m);
    int i;
    for (i = 1; i <= n; i++) scanf("%lld", &cost[i]);
    
    for (i = 1; i <= m; i++) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        g[v1].push_back(v2);
        g[v2].push_back(v1);
    }
    
    for (i = 1; i <= n; i++) {
        if (!visited[i]) {
            tarjan(i, 0);
        }
    }
    
    for (i = 1; i <= n; i++) {
    	weight[cmpid[i]] += cost[i];
   		cmpsz[cmpid[i]] += 1;
        for (auto v : g[i]) {
        	if (cmpid[i] != cmpid[v]) {
               t[cmpid[i]].insert(cmpid[v]);
			}
        }
    }
    
    scanf("%d", &src);
    
    
    dfs1(cmpid[src], 0);
    dfs2(cmpid[src], 0);    
    printf("%lld\n", dp[cmpid[src]]);
    return 0;
}
