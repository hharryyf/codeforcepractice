#include <bits/stdc++.h>
using namespace std;
#define MAX_SIZE 200011
// pair->first is the outdegree, pair->second is the id
set<pair<int, int>> s; 
int deg[MAX_SIZE];
unordered_set<int> g[MAX_SIZE];
int k, n, m;
int ans[MAX_SIZE], x[MAX_SIZE], y[MAX_SIZE];

void del(int id) {
    for (auto v : g[id]) {
        g[v].erase(id);
        s.erase(make_pair(deg[v], v));
        deg[v]--;
        if (deg[v] > 0) {
            s.insert(make_pair(deg[v], v));
        }
    }
    
    g[id].clear();
    s.erase(make_pair(deg[id], id));
    deg[id] = 0;
}

int main() {
    int i;
    scanf("%d%d%d", &n, &m, &k);
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x[i], &y[i]);
        g[x[i]].insert(y[i]), g[y[i]].insert(x[i]);
        deg[x[i]]++, deg[y[i]]++;
    }
    
    for (i = 1; i <= n; i++) {
        s.insert(make_pair(deg[i], i));
    }
    
    for (i = m; i >= 1; i--) {
        while (!s.empty()) {
            auto p = *s.begin();
            if (p.first >= k) {
                break;
            }
            
            del(p.second);
        }
        
        ans[i] = s.size();
        if (g[x[i]].find(y[i]) != g[x[i]].end()) {
	        g[x[i]].erase(y[i]), g[y[i]].erase(x[i]);
	        s.erase(make_pair(deg[x[i]], x[i]));
	        s.erase(make_pair(deg[y[i]], y[i]));
	        if (deg[x[i]] > 0) {
	            s.insert(make_pair(--deg[x[i]], x[i]));
	        }
	        
	        if (deg[y[i]] > 0) {
	            s.insert(make_pair(--deg[y[i]], y[i]));
	        }
		}
    }
    
    for (i = 1; i <= m; i++) printf("%d\n", ans[i]);
    return 0;
}
