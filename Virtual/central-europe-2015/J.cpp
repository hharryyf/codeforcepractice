#include <bits/stdc++.h>
#define MAX_SIZE 4511
using namespace std;
typedef long long ll;
using namespace std;
const ll mod = 1000000009, base = 4511;
int cmpid[MAX_SIZE];
vector<pair<int, int>> g[MAX_SIZE];
int low[MAX_SIZE];
int visited[MAX_SIZE];
ll bitst[MAX_SIZE];
ll pw[MAX_SIZE];
int instack[MAX_SIZE], f[MAX_SIZE];
stack<int> s;
int N, M, cnt = 0, ans = 0;

void init() {
    cnt = 0;
    int i;
    for (i = 0; i < MAX_SIZE; ++i) {
        instack[i] = 0;
        low[i] = 0;
        cmpid[i] = 0;
        visited[i] = 0;
    }

    while (!s.empty()) s.pop();
}

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int a = find(x), b = find(y);
    f[a] = b;
}

void tarjan(int v, int pre, int bad) {
	 visited[v] = ++cnt;
	 low[v] = visited[v];
	 s.push(v);
	 instack[v] = 1;
	 for (auto np : g[v]) {
	 	 int nv = np.first;
         if (np.second == bad) continue;
	 	 if (nv != pre) {
		 	if (!visited[nv]) {
			    tarjan(nv, v, bad);
			    low[v] = min(low[v], low[nv]);
	        } else if (instack[nv]) {
			    low[v] = min(low[v], visited[nv]);
			} 
         }
	 }
	 
	 if (low[v] == visited[v]) {
	 	while (s.top() != v) {
	        cmpid[s.top()] = v;
			instack[s.top()] = 0;
			bitst[s.top()] += pw[bad] * v;
            bitst[s.top()] %= mod;
            s.pop(); 
	    }
	    
	    cmpid[s.top()] = v;
		instack[s.top()] = 0;
		bitst[s.top()] += pw[bad] * v;
        bitst[s.top()] %= mod;    
        s.pop();
	 }
}

int main() {
    int i, j;
    pw[0] = 1;
    for (i = 1; i < MAX_SIZE; ++i) {
        pw[i] = pw[i-1] * base;
        pw[i] %= mod;
        f[i] = i;
    }

    scanf("%d%d", &N, &M);
    for (i = 1; i <= M; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].emplace_back(v, i);
        g[v].emplace_back(u, i);
        unionset(u, v);
    }

    for (i = 1; i <= N; ++i) {
        for (j = i + 1; j <= N; ++j) {
            if (find(i) == find(j)) ans++;
        }
    }

    for (i = 1; i <= N; ++i) {
        if (!visited[i]) tarjan(i, 0, 0);
    }

    for (i = 1; i <= N; ++i) {
        for (j = i + 1; j <= N; ++j) {
            if (cmpid[i] == cmpid[j]) ans++;
        }
    }

    for (i = 1; i <= N; ++i) bitst[i] = 0;
    for (i = 1; i <= M; ++i) {
        init();
        for (j = 1; j <= N; ++j) {
            if (!visited[j]) {
                tarjan(j, 0, i);
            }
        }
    }

    for (i = 1; i <= N; ++i) {
        for (j = i + 1; j <= N; ++j) {
            if (bitst[i] == bitst[j]) ans++;
        }
    }

    printf("%d\n", ans);
    return 0;  
}