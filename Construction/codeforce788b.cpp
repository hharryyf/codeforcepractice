#include <bits/stdc++.h>
#define MAX_SIZE 1000111
using namespace std;
typedef long long ll;
int f[MAX_SIZE];

int find(int x) {
    if (x == f[x]) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int a = find(x), b = find(y);
    f[a] = b;
}

int n, m;
vector<int> g[MAX_SIZE];
int active[MAX_SIZE];

int main() {
    int i;
    scanf("%d%d", &n, &m);
    if (m < 2) {
        printf("0\n");
        return 0;
    }

    int self_cycle = 0, pos = -1;
    for (i = 1; i <= n; ++i) {
        f[i] = i;
    }

    for (i = 1; i <= m; ++i) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        if (v1 == v2) {
            self_cycle++;
        } else {
            g[v1].push_back(v2);
            g[v2].push_back(v1);
            unionset(v1, v2);
        }
        active[v1] = 1;
        pos = v1;
    }

    for (i = 1; i <= n; ++i) {
        if (active[i] && find(i) != find(pos)) {
            printf("0\n");
            return 0;
        }
    }

    ll ans = 0;
    ans += 1ll * self_cycle * (self_cycle - 1) / 2 + 1ll * self_cycle * (m - self_cycle);
    for (i = 1; i <= n; ++i) {
        int deg = g[i].size();
        ans += 1ll * deg * (deg - 1) / 2;
    }

    printf("%I64d\n", ans);
    return 0;
}