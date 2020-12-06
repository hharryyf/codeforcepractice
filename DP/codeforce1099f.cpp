#include <bits/stdc++.h>
#define MAX_SIZE 100111
typedef long long ll;
using namespace std;

ll tree[MAX_SIZE][2];
vector<int> disc;
int xi[MAX_SIZE], ti[MAX_SIZE];
int tmp[MAX_SIZE];
ll profit[MAX_SIZE];
vector<pair<int, int>> g[MAX_SIZE];
int N, SZ;
ll T;

int shift(int x) {
    return x & (-x);
}

void update(int index, int x, int t, int sgn) {
    if (index == 0) return;
    while (index <= SZ) {
        tree[index][1] += 1ll * sgn * x;
        tree[index][0] += 1ll * sgn * x * t;
        index += shift(index);
    }
}

pair<ll, ll> query(int index) {
    pair<ll, ll> ret = {0, 0};
    while (index > 0) {
        ret.first += tree[index][0];
        ret.second += tree[index][1];
        index -= shift(index);
    }
    return ret;
}

void dfs(int v, ll dep) {
    ll rem = T - dep * 2;
    if (rem <= 0) return;
    int idx = upper_bound(disc.begin(), disc.end(), ti[v]) - disc.begin();
    update(idx, xi[v], ti[v], 1);
    int L = 0, R = SZ;
    auto curr = query(SZ);
    if (curr.first <= rem) {
        profit[v] = curr.second;
    } else {
        int low = 1, high = SZ;
        while (low <= high) {
            int mid = (low + high) / 2;
            curr = query(mid);
            if (curr.first <= rem) {
                low = mid + 1;
                L = mid;
            } else {
                high = mid - 1;
            }
        }

        low = 1, high = SZ;
        while (low <= high) {
            int mid = (low + high) / 2;
            curr = query(mid);
            if (curr.first > rem) {
                high = mid - 1;
                R = mid;
            } else {
                low = mid + 1;
            }
        }

        auto v1 = query(L);
        // cout << "vertex " << v << " L= " << L << " R= " << R << endl;
        profit[v] = v1.second + (rem - v1.first) / disc[R-1];
    }
    
    for (auto np : g[v]) {
        dfs(np.first, dep + np.second);
    }
    update(idx, xi[v], ti[v], -1);
    // cout << v << " profit= " << profit[v] << endl;
}

ll calc(int v) {
    if (g[v].empty()) return profit[v];
    vector<ll> cost;
    // cost.push_back(profit[v]);
    for (auto nv : g[v]) {
        cost.push_back(calc(nv.first));
    }

    sort(cost.begin(), cost.end());
    cost.pop_back();
    if (cost.empty()) return profit[v];
    return max(cost.back(), profit[v]);
}

int main() {
    int i;
    scanf("%d%I64d", &N, &T);
    for (i = 1; i <= N; ++i) scanf("%d", &xi[i]);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &ti[i]);
        tmp[i] = ti[i];
    }

    sort(tmp + 1, tmp + 1 + N);
    for (i = 1; i <= N; ++i) {
        if (i == 1 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
    }

    SZ = (int) disc.size();
    for (i = 2; i <= N; ++i) {
        int p, c;
        scanf("%d%d", &p, &c);
        g[p].emplace_back(i, c);
    }   

    dfs(1, 0);

    ll ans = profit[1];
    for (auto v : g[1]) {
        ans = max(ans, calc(v.first));
    }

    printf("%I64d\n", ans);
    return 0;
}