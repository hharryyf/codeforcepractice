#include <bits/stdc++.h>
#define MAX_SIZE 211
using namespace std;

int dist[MAX_SIZE];
const int inf = 400000000;
int n;

struct edge {
    int from, to, w;
};

vector<edge> edg;

int in(int v) {
    return v * 2 - 1;
}

int out(int v) {
    return v * 2;
}

bool check(int st) {
    int i;
    for (i = in(1); i <= out(n); ++i) {
        dist[i] = inf;
    }

    dist[in(1)] = -st;
    for (i = 1; i <= n; ++i) {
        for (auto e : edg) { 
            if (dist[e.from] <= 0) {
                dist[e.to] = min(dist[e.from] + e.w, dist[e.to]);
            }
        }
    }

    return dist[in(n)] <= 0;
}

int x[MAX_SIZE], y[MAX_SIZE], d;

int main() {
    int i, j;
    scanf("%d%d", &n, &d);
    edg.push_back(edge{in(1), out(1), 0});
    edg.push_back(edge{in(n), out(n), 0});
    for (i = 2; i <= n - 1; ++i) {
        int w;
        scanf("%d", &w);
        edg.push_back(edge{in(i), out(i), -w});
    }
    for (i = 1; i <= n; ++i) scanf("%d%d", &x[i], &y[i]);
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= n; ++j) {
            if (i == j) continue;
            int w = abs(x[i] - x[j]) + abs(y[i] - y[j]);
            edg.push_back(edge{out(i), in(j), w * d});
        }
    }

    int low = 0, high = inf, ans = inf;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (check(mid)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    printf("%d\n", ans);
    return 0;
}