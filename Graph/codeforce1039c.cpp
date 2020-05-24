#include <bits/stdc++.h>
#define MAX_SIZE 500011
typedef long long ll;
using namespace std;

const ll mod = 1e9+7;

int f[MAX_SIZE];
int sz[MAX_SIZE];
ll p2[MAX_SIZE];

int find(int x) {
    if (x == f[x]) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return;
    f[x] = y;
    sz[y] += sz[x];
}

void preprocess() {
    int i;
    p2[0] = 1;
    for (i = 0 ; i < MAX_SIZE; ++i) {
        f[i] = i;
        sz[i] = 1;
        if (i > 0) {
            p2[i] = p2[i-1] * 2;
            p2[i] %= mod;
        }
    }
}

map<ll, vector<pair<int, int>>> edg;
ll cod[MAX_SIZE];
int visited[MAX_SIZE];
vector<int> vc;
int n;
// the number of ways that would cause trouble if
// we use some x
ll calc(vector<pair<int, int>> &pr) {
    vc.clear();  
    int s = 0;
    for (auto &e : pr) {
        vc.push_back(e.first);
        vc.push_back(e.second);
        visited[e.first] = visited[e.second] = 0;
        f[e.first] = e.first, f[e.second] = e.second;
        sz[e.first] = sz[e.second] = 1;
    }

    for (auto &e : pr) {
        unionset(e.first, e.second);
    }

    int cnt = 0;
    for (auto v : vc) {
        if (find(v) == v && !visited[v]) {
            s += sz[v];
            visited[v] = 1;
            cnt++;
        } 
    }

    if (s == 0) return 0;
    // now we have n-s elements, if we select only
    // the complete components, no trouble is going to be caused
    return p2[n] - (p2[n-s] * p2[cnt]);
}

int main() {
    int i, m, k;
    preprocess();
    scanf("%d%d%d", &n, &m, &k);
    ll ans = (p2[n] * p2[k]) % mod;
    for (i = 1; i <= n; ++i) {
        scanf("%I64d", &cod[i]);
    }

    for (i = 0 ; i < m; ++i) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        edg[cod[v1] ^ cod[v2]].emplace_back(v1, v2);
    }

    auto iter = edg.begin();
    while (iter != edg.end()) {
        ans -= calc(iter->second);
        ans = ans % mod;
        ++iter;
    }
    
    cout << (((ans % mod) + mod) % mod) << endl;
    return 0;
}