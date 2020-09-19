#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 500011
using namespace std;
typedef long long ll;

vector<int> g[MAX_SIZE];
vector<int> ord[MAX_SIZE];
int ans[MAX_SIZE], cnt = 1;
int color[MAX_SIZE], p[MAX_SIZE];

int main() {
    int n, m, i;
    scanf("%d%d", &n, &m);
    for (i = 0 ; i < m; ++i) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        g[v1].push_back(v2);
        g[v2].push_back(v1);
    }

    for (i = 1; i <= n; ++i) {
        scanf("%d", &color[i]);
        ord[color[i]].push_back(i);
    }

    for (i = 1; i <= n; ++i) {
        for (auto v : ord[i]) {
            p[cnt] = v;
            ans[v] = cnt++;
        }

        for (auto v : ord[i]) {
            set<int> st;
            for (auto nv : g[v]) {
                if (ans[nv] != 0) {
                    // cout << nv << " is not 0 " << " " << ans[nv] << endl; 
                    st.insert(color[nv]);
                }
            }

            if ((int) st.size() != i - 1 || (!st.empty() && *st.rbegin() >= i)) {
                // cout << "Fail st " << v << endl;
                // cout << st.size() << endl;
                // cout << *st.rbegin() << endl;
                printf("-1\n");
                return 0;
            }
        }
    }

    for (i = 1; i <= n; ++i) {
        printf("%d ", p[i]);
    }
    return 0;
}