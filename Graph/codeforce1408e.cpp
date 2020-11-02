#include <bits/stdc++.h>
#define MAX_SIZE 300011
using namespace std;
typedef long long ll;
vector<pair<int, pair<int, int>>> edg;
int a[MAX_SIZE], b[MAX_SIZE];
int f[MAX_SIZE];

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int xx = find(x), xy = find(y);
    f[xx] = xy;
}

int main() {
    int i, m, n;
    ll ans = 0;
    scanf("%d%d", &m, &n);
    for (i = 1; i <= m; ++i) scanf("%d", &a[i]);
    for (i = 1; i <= n; ++i) scanf("%d", &b[i]);
    for (i = 1; i <= m; ++i) {
        int si;
        scanf("%d", &si);
        while (si-- > 0) {
            int v;
            scanf("%d", &v);
            edg.push_back(make_pair(-a[i] - b[v], make_pair(i, v + m)));
            ans += a[i] + b[v];
        }
    }

    sort(edg.begin(), edg.end());
    for (i = 1; i < MAX_SIZE; ++i) f[i] = i;
    for (auto e : edg) {
        if (find(e.second.first) != find(e.second.second)) {
            unionset(e.second.first, e.second.second);
            ans += e.first;
        }
    }

    cout << ans << endl;
    return 0;
}