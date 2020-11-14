#include <bits/stdc++.h>
#define MAX_SIZE 500011
typedef long long ll;
using namespace std;

ll c[MAX_SIZE];
vector<int> g[MAX_SIZE];

int main() {
    int T, i, n, m;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d%d", &n, &m);
        for (i = 1; i <= n; ++i) {
            scanf("%I64d", &c[i]);
            g[i].clear();
        } 
        
        for (i = 1; i <= m; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            g[v].push_back(u);
        }

        for (i = 1; i <= n; ++i) {
            sort(g[i].begin(), g[i].end());
        }

        map<vector<int>, ll> mp;
        for (i = 1; i <= n; ++i) {
            if (!g[i].empty()) {
                mp[g[i]] += c[i];
                // cout << c[i] << endl;
            }
        }

        ll g = 0;
        for (auto v : mp) {
            if (v.second == 0) continue;
            g = __gcd(g, v.second);
        }

        printf("%I64d\n", g);
    }
    return 0;
}