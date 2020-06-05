#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

struct edge {
    int from, to, id;
    double w, delta;
    bool select;
    bool operator < (edge other) const {
        return w + delta < other.w + other.delta;
    }

    bool critical() {
        return from == 1 || to == 1;
    }
};

edge edg[MAX_SIZE];
int n, m, k;
int f[MAX_SIZE];

int find(int x) {
    if (x == f[x]) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int a = find(x), b = find(y);
    f[a] = b;
}

int kruskal(double offset=1e5) {
    int i, tol = 0;
    // cout << offset << endl;
    for (i = 1; i <= n; ++i) {
        f[i] = i;
    }

    for (i = 1; i <= m; ++i) {
        if (edg[i].critical()) {
            edg[i].delta = offset;
        }
        edg[i].select = false;
    }

    sort(edg + 1, edg + 1 + m);

    for (i = 1; i <= m; ++i) {
        if (find(edg[i].from) != find(edg[i].to)) {
            if (tol + edg[i].critical() <= k) {
                tol += edg[i].critical();
                unionset(edg[i].from, edg[i].to);
                edg[i].select = true;
            }
        }
    }

    return tol;
}

int main() {
    int i, tol = 0;
    scanf("%d%d%d", &n, &m, &k);
    for (i = 1; i <= m; ++i) {
        scanf("%d%d%lf", &edg[i].from, &edg[i].to, &edg[i].w);
        edg[i].id = i;
        edg[i].select = false;
        edg[i].delta = 0.0;
        tol += edg[i].critical();
    }

    if (tol < k || (n > 1 && k == 0)) {
        printf("-1\n");
        return 0;
    }

    kruskal();

    tol = 0;
    for (i = 1; i <= m; ++i) {
        tol += edg[i].select;
    }

    if (tol != n - 1) {
        printf("-1\n");
        return 0;
    }

    double l = -1e5, r = 1e5;
    double ans = 0.0;
    for (i = 0 ; i < 50; ++i) {
        double mid = 0.5 * (l + r);
        if (kruskal(mid) < k) {
            r = mid;
        } else {
            l = mid;
            ans = mid;
            // cout << "update " << mid << " " << kruskal(mid) << endl;
        }
    }

    
    kruskal(ans);
    printf("%d\n", n - 1);
    for (i = 1; i <= m; ++i) {
        if (edg[i].select) {
            printf("%d ", edg[i].id);
        }
    }
    printf("\n");
    return 0;
}