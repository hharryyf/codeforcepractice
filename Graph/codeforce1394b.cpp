#include <bits/stdc++.h>
#define MAX_SIZE 200111
typedef long long ll;
using namespace std;
const ll base = 200111;
const ll mod = 19260817;
vector<pair<int, int>> g[MAX_SIZE];

ll sm = 0;
ll pw[MAX_SIZE];
ll in[10][10], out[10][10];
int n, m, k, ans = 0;
vector<int> curr;
void dfs(int idx) {
    int i;
    if (idx == k) {
        ll cid = 0, cod = 0;
        for (i = 0 ; i < k; ++i) {
            cid += in[i][curr[i]];
            cid %= mod;
            cod += out[i][curr[i]];
            cod %= mod;
        }      
        //for (i = 0 ; i < k; ++i) {
        //    cout << curr[i] << " ";
        //}
        //cout << cid << " " << cod << " -> " << sm << endl;
        if (cid == sm && cod == sm) ans++; 
        return;
    }

    for (i = 0 ; i <= idx; ++i) {
        curr[idx] = i;
        dfs(idx + 1);
    }
}

int main() {
    int i, j;
    scanf("%d%d%d", &n, &m, &k);
    pw[0] = 1;
    curr.resize(k);
    for (i = 1; i < MAX_SIZE; ++i) {
        pw[i] = pw[i-1] * base;
        pw[i] %= mod;
    }

    for (i = 1; i <= m; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g[u].emplace_back(w, v);        
    }

    for (i = 1; i <= n; ++i) {
        sort(g[i].begin(), g[i].end());
        int sz = g[i].size();
        for (j = 0 ; j < sz; ++j) {
            in[sz-1][j] += pw[i];
            out[sz-1][j] += pw[g[i][j].second];
            in[sz-1][j] %= mod;
            out[sz-1][j] %= mod;
        }
        sm += pw[i];
        sm %= mod;
    }

    dfs(0);   
    printf("%d\n", ans);
    return 0;
}