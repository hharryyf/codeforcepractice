#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 100111

using namespace std;


struct edge {
    int v, c, id;
};

vector<edge> g[MAX_SIZE];
int visited[MAX_SIZE];
bool cycle = false;
int n, m;


vector<int> ret;
int ord[MAX_SIZE];
// top-sort on the graph, using only edges > c
// if cycle is found cycle = true
void dfs(int v, int c) {
    visited[v] = 1;
    for (auto np : g[v]) {
        int nv = np.v;
        if (np.c > c) {
            if (visited[nv] == 1) {
                cycle = true;
            }
            
            if (!visited[nv]) {
                dfs(nv, c);
            }
        }
    }
    
    ret.push_back(v);
    visited[v] = 2;
}

bool valid(int mid) {
    ret.clear();
    memset(visited, 0, sizeof(visited));
    int i;
    cycle = false;
    for (i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i, mid);
        }
    }
    
    if (cycle) return false;
    return true;
}

int main() {
    int i;
    scanf("%d%d", &n, &m);
    for (i = 0 ; i < m; i++) {
        int v1, v2, c;
        scanf("%d%d%d", &v1, &v2, &c);
        g[v1].push_back(edge{v2, c, i+1});
    }
    
    int low = 0, high = 1000000001;
    int ans = high;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (valid(mid)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    
    valid(ans);
    
    reverse(ret.begin(), ret.end());
    for (i = 0; i < ret.size(); i++) {
        ord[ret[i]] = i;
    }
    
    vector<int> sel;
    for (i = 1 ; i <= n; i++) {
        for (auto np : g[i]) {
            int nv = np.v;
            if (np.c <= ans && ord[i] > ord[nv]) {
                sel.push_back(np.id);
            }
        }
    }
    
    sort(sel.begin(), sel.end());
    printf("%d %d\n", ans, sel.size());
    for (auto s : sel) {
        printf("%d ", s);
    }
    printf("\n");
    return 0;
}
