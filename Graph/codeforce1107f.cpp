#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

namespace MCF {
    #define MAXN 1111
    #define MAXM 800010
    #define wint ll
    #define cint ll
    const wint wEPS = 0;
    const wint wINF = 1e15;
    const cint cEPS = 0;
    const cint cINF = 1e15;
    int n, m, ptr[MAXN], next[MAXM], zu[MAXM];
    wint capa[MAXM], tof;
    cint cost[MAXM], toc, d[MAXN], pot[MAXN];
    int vis[MAXN], pree[MAXN];
    void init(int _n) {
        n = _n; m = 0; memset(ptr, ~0, n << 2);
    }
    void ae(int u, int v, wint w, cint c) {
        next[m] = ptr[u]; ptr[u] = m; zu[m] = v; capa[m] = w; cost[m] = +c; ++m;
        next[m] = ptr[v]; ptr[v] = m; zu[m] = u; capa[m] = 0; cost[m] = -c; ++m;
    }
    bool spRep(int src, int ink, wint flo = wINF) {
        wint f;
        cint c, cc;
        int i, u, v;
        memset(pot, 0, n * sizeof(cint));
        for (bool cont = 1; cont; ) {
            cont = 0;
            for (u = 0; u < n; ++u) for (i = ptr[u]; ~i; i = next[i]) if (capa[i] > wEPS) {
                if (pot[zu[i]] > pot[u] + cost[i] + cEPS) {
                    pot[zu[i]] = pot[u] + cost[i]; cont = 1;
                }
            }
        }
        for (toc = 0, tof = 0; tof + wEPS < flo; ) {
            typedef pair<cint,int> node;
            priority_queue< node,vector<node>,greater<node> > q;
            for (u = 0; u < n; ++u) { d[u] = cINF; vis[u] = 0; }
            for (q.push(make_pair(d[src] = 0, src)); !q.empty(); ) {
                c = q.top().first; u = q.top().second; q.pop();
                if (vis[u]++) continue;
                for (i = ptr[u]; ~i; i = next[i]) if (capa[i] > wEPS) {
                    cc = c + cost[i] + pot[u] - pot[v = zu[i]];
                    if (d[v] > cc) { q.push(make_pair(d[v] = cc, v)); pree[v] = i; }
                }
            }
            if (!vis[ink]) return 0;
            f = flo - tof;
            for (v = ink; v != src; v = zu[i ^ 1]) { i = pree[v]; f = min(f,capa[i]); }
            for (v = ink; v != src; v = zu[i ^ 1]) { i = pree[v]; capa[i] -= f; capa[i ^ 1] += f; }
            tof += f;
            toc += f * (d[ink] - pot[src] + pot[ink]);
            for (u = 0; u < n; ++u) pot[u] += d[u];
        }
        return 1;
    }
}

struct plan {
    int a, b, ki;
};

plan p[511];

int main() {
    int n, i, j;
    scanf("%d", &n);
    MCF::init(2 * n + 14);
    int src = 0, target = 2 * n + 11;
    for (i = 1; i <= n; ++i) scanf("%d%d%d", &p[i].a, &p[i].b, &p[i].ki);
    for (i = 1; i <= n; ++i) {
        MCF::ae(src, i, 1, 0);
        MCF::ae(i + n, target, 1, 0);
        for (j = 1; j <= n; ++j) {
            int tol = min(n - j, p[i].ki);
            ll cost = max(0ll, 1ll * p[i].a - 1ll * p[i].b * tol);
            MCF::ae(i, j + n, 1, -cost);
        }
    }

    MCF::spRep(src, target);
    cout << -MCF::toc << endl;
    return 0;
}