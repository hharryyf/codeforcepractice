#include <bits/stdc++.h>
#define MAX_SIZE 42
typedef long long ll;
using namespace std;

vector<int> g[MAX_SIZE];
int n;
pair<ll, ll> ans[MAX_SIZE];
int dx[4] = {1, 0, 0, -1}, dy[4] = {0, 1, -1, 0};

void dfs(int v, int pre, ll x, ll y, int weight, int preid) {
    ans[v].first = x, ans[v].second = y;
    int i = 0;
    for (auto nv : g[v]) {
        if (nv != pre) { 
            if (preid != -1 && dx[preid] + dx[i] == 0 && dy[preid] + dy[i] == 0) ++i;
            dfs(nv, v, x + 1ll * (1ll << weight) * dx[i], y + 1ll * (1ll << weight) * dy[i], weight - 1, i);
            ++i;
        }
    }
}

int main() {
    int i;
    scanf("%d", &n);
    for (i = 0 ; i < n - 1; ++i) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        g[v1].push_back(v2), g[v2].push_back(v1);
    }

    for (i = 1; i <= n; ++i) {
        if ((int) g[i].size() > 4) {
            printf("NO\n");
            return 0;
        }
    }

    printf("YES\n");
    dfs(1, 0, 0, 0, 30, -1);

    for (i = 1; i <= n; ++i) {
        printf("%I64d %I64d\n", ans[i].first, ans[i].second);
    }
    return 0;
}