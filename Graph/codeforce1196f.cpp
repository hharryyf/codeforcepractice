#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 811
#define MAXM 200011
typedef long long ll;
using namespace std;

const ll inf = 1e14;
ll dist[MAX_SIZE][MAX_SIZE];
pair<int, pair<int, int>> edg[MAXM];
vector<int> tmp;
vector<int> disc;
vector<ll> ans;

int main() {
    int i, n, m, k, j, p;
    scanf("%d%d%d", &n, &m, &k);
    for (i = 1; i <= m; ++i) {
        scanf("%d%d%d", &edg[i].second.first, &edg[i].second.second, &edg[i].first);
    }

    sort(edg + 1, edg + 1 + m);

    for (i = 1; i <= min(m, k); ++i) {
        tmp.push_back(edg[i].second.first);
        tmp.push_back(edg[i].second.second);
    }

    sort(tmp.begin(), tmp.end());

    for (i = 0 ; i < (int) tmp.size(); ++i) {
        if (i == 0 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
    }

    for (i = 1; i <= min(m, k); ++i) {
        int idx1 = lower_bound(disc.begin(), disc.end(), edg[i].second.second) - disc.begin();
        int idx2 = lower_bound(disc.begin(), disc.end(), edg[i].second.first) - disc.begin();
        dist[idx1][idx2] = dist[idx2][idx1] = edg[i].first;
    }
    int sz = disc.size();
    for (i = 0 ; i < sz; ++i) {
        for (j = 0 ; j < sz; ++j) {
            if (i != j && dist[i][j] == 0) dist[i][j] = inf;
        }
    }

    for (p = 0; p < sz; ++p) {
        for (i = 0 ; i < sz; ++i) {
            for (j = 0 ; j < sz; ++j) {
                dist[i][j] = min(dist[i][j], dist[i][p] + dist[p][j]);
            }
        }
    }

    for (i = 0; i < sz; ++i) {
        for (j = i + 1; j < sz; ++j) {
            ans.push_back(dist[i][j]);
        }
    }

    sort(ans.begin(), ans.end());

    printf("%I64d\n", ans[k-1]);
    return 0;
}