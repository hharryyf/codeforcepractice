#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;
typedef long long ll;

int f[MAX_SIZE];
int sz[MAX_SIZE];
int n;

struct edge {
    int from, to, w, id;
    bool operator <(edge other) const {
        return w < other.w;
    }
};

edge edg[MAX_SIZE];

int find(int x) {
    if (x == f[x]) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int a = find(x), b = find(y);
    if (a == b) return;
    sz[a] = sz[a] + sz[b];
    f[b] = a;
}

// the sparse graph created by the weights
// from->(to, id)
map<int, vector<pair<int, int>>> mp;
int visited[MAX_SIZE];
ll ans[MAX_SIZE];
int tol[MAX_SIZE];
vector<int> disc;

void dfs1(int v, int pre) {
    tol[v] = sz[find(v)];
    visited[v] = 1;
    for (auto np : mp[v]) {
        if (np.first != pre) {
            dfs1(np.first, v);
            tol[v] += tol[np.first];
        }
    }
    // cout << v << " " << tol[v] << endl;
}

void dfs2(int rt, int v, int pre) {
    for (auto np : mp[v]) {
        if (np.first != pre) {
            ans[np.second] = 1ll * (tol[rt] - tol[np.first]) * tol[np.first];
            dfs2(rt, np.first, v);
        }
    }
}



int main() {
    int i, j, k;
    for (i = 0 ; i < MAX_SIZE; ++i) {
        f[i] = i;
        sz[i] = 1;
    }

    scanf("%d", &n);  
    for (i = 1; i <= n - 1; ++i) {
        scanf("%d%d%d", &edg[i].from, &edg[i].to, &edg[i].w);
        edg[i].id = i;
    }

    sort(edg + 1, edg + n);

    for (i = 1; i <= n - 1; ++i) {
        if (i == 1 || edg[i].w != edg[i-1].w) disc.push_back(edg[i].w);
    }

    // cout << "disc= " << disc.size() << endl;
    for (i = 0, j = 1; i < (int) disc.size(); ++i) {
        vector<int> nd;
        mp.clear();
        // cout << "current weight= " << disc[i] << endl;
        while (j <= n - 1 && edg[j].w <= disc[i]) {
            nd.push_back(find(edg[j].from));
            visited[nd.back()] = 0;
            tol[nd.back()] = 0;
            nd.push_back(find(edg[j].to));
            visited[nd.back()] = 0;
            tol[nd.back()] = 0;
            mp[find(edg[j].from)].emplace_back(find(edg[j].to), edg[j].id);
            mp[find(edg[j].to)].emplace_back(find(edg[j].from), edg[j].id);
            // cout << "edge " << edg[j].from << " " << edg[j].to << " w=" << edg[j].w << endl; 
            // cout << "join " << find(edg[j].from) << " " << find(edg[j].to) << " edge id " << edg[j].id << endl;
            ++j;
        }

        for (auto v : nd) {
            if (!visited[v]) {
                dfs1(v, -1);
                dfs2(v, v, -1);
            }
        }

        for (k = 0 ; k < (int) nd.size(); k += 2) {
            unionset(nd[k], nd[k+1]);
        }
    }

    ll beauty = 0;
    for (i = 1; i <= n - 1; ++i) {
        beauty = max(beauty, ans[i]);
    }

    int c = 0;
    for (i = 1; i <= n - 1; ++i) {
        c += (beauty == ans[i]);
    }

    printf("%I64d %d\n", beauty * 2, c);
    for (i = 1; i <= n - 1; ++i) {
        if (ans[i] == beauty) {
            printf("%d ", i);
        }
    }
    printf("\n");
    return 0;
}