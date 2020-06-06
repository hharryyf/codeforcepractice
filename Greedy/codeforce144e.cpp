#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 111111
using namespace std;
// ((c, r), id) 
pair<pair<int, int>, int> g[MAX_SIZE]; 
set<int> st;
vector<int> ans;

int main() {
    int i, n, m;
    scanf("%d%d", &n, &m);
    // the spots are (i, n + 1 - i)
    for (i = 1; i <= n; ++i) st.insert(i);
    for (i = 1; i <= m; ++i) {
        scanf("%d%d", &g[i].first.second, &g[i].first.first);
        g[i].second = i;
    }

    sort(g + 1, g + 1 + m);

    for (i = 1; i <= m; ++i) {
        if (st.empty()) continue;
            //  n + 1 - i <= p.second and i <= x
        auto p = g[i];
        int x = p.first.second, y = p.first.first;
        auto iter = st.lower_bound(n + 1 - x);
        if (iter != st.end() && *iter <= y) {
            ans.push_back(p.second);
            st.erase(*iter);
        }
    }

    printf("%d\n", (int) ans.size());
    for (auto p : ans) {
        printf("%d ", p);
    }
    printf("\n");
    return 0;
}