#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

struct triangle {
    int v1, v2, v3;
    // id of the triangle and the 
    // number of times the 3 edges are used
    int id, deg;
    bool operator < (triangle other) const {
        if (deg != other.deg) return deg < other.deg;
        return id < other.id;
    }
};

triangle tri[MAX_SIZE];
// g[i] has v means i < v in the partial order
set<int> g[MAX_SIZE];
// the id of the triangles with edge[i][j], each vector has size
// at most 2
map<int, vector<int>> mp[MAX_SIZE];
// id, (edge that connects the id)
vector<pair<int, pair<int, int>>> qg[MAX_SIZE];
int relaxed[MAX_SIZE], visited[MAX_SIZE];
int deg[MAX_SIZE];
int n;
vector<int> ret;
void init() {
    int i;
    for (i = 1; i <= n; ++i) {
        g[i].clear();
        mp[i].clear();
        qg[i].clear();
        deg[i] = 0;
        relaxed[i] = visited[i] = 0;
        tri[i].deg = 0;
    }
    ret.clear();
}

void increment(int u, int v, int id) {
    if (u > v) swap(u, v);
    mp[u][v].push_back(id);
}

void dfs(int v) {
    visited[v] = 1;
    for (auto nv : g[v]) {
        if (!visited[nv]) {
            dfs(nv);
        }
    }

    ret.push_back(v);
}

int main() {
    int T, i;
    scanf("%d", &T);
    while (T > 0) {
        scanf("%d", &n);
        vector<int> Q;
        init();
        for (i = 1; i <= n - 2; ++i) {
            scanf("%d%d%d", &tri[i].v1, &tri[i].v2, &tri[i].v3);
            tri[i].id = i;
            increment(tri[i].v1, tri[i].v2, i);
            increment(tri[i].v2, tri[i].v3, i);
            increment(tri[i].v1, tri[i].v3, i);
            deg[tri[i].v1]++, deg[tri[i].v2]++, deg[tri[i].v3]++;
        }

        for (i = 1; i <= n; ++i) {
            for (auto pp : mp[i]) {
                if ((int) pp.second.size() == 2) {
                    qg[pp.second[0]].emplace_back(pp.second[1], make_pair(i, pp.first));
                    qg[pp.second[1]].emplace_back(pp.second[0], make_pair(i, pp.first));
                    tri[pp.second[0]].deg += 1;
                    tri[pp.second[1]].deg += 1;
                }
            }
        }

        set<triangle> st;
        for (i = 1; i <= n - 2; ++i) {
            st.insert(tri[i]);
            // cout << tri[i].deg << " -- " << i << endl;
        }

        auto ti = *st.begin();
        // cout << ti.id << endl;
        int start = 1;
        queue<int> q;
        if (deg[ti.v1] == 1) {
            g[ti.v2].insert(ti.v3);
            g[ti.v1].insert(ti.v2);
            start = ti.v1;
        } else if (deg[ti.v2] == 1) {
            g[ti.v2].insert(ti.v3);
            g[ti.v3].insert(ti.v1);
            start = ti.v2;
        } else {
            g[ti.v3].insert(ti.v1);
            g[ti.v1].insert(ti.v2);
            start = ti.v3;
        }

        q.push(ti.id);
        while (!q.empty()) {
            auto v = q.front();
            q.pop();
            if (relaxed[v]) continue;
            relaxed[v] = 1;
            for (auto np : qg[v]) {
                int id = np.first;
                int v1 = np.second.first, v2 = np.second.second;
                if (!relaxed[id]) {
                    if (g[v2].find(v1) != g[v2].end()) swap(v1, v2);
                    if (tri[id].v1 != v1 && tri[id].v1 != v2) {
                        g[v1].insert(tri[id].v1);
                        g[tri[id].v1].insert(v2);
                    } else if (tri[id].v2 != v1 && tri[id].v2 != v2) {
                        g[v1].insert(tri[id].v2);
                        g[tri[id].v2].insert(v2);
                    } else  {
                        g[v1].insert(tri[id].v3);
                        g[tri[id].v3].insert(v2);
                    }
                    q.push(id);
                }
            }
        }

        // cout << start << endl;
        dfs(start);

        for (i = (int) ret.size() - 1; i >= 0; --i) {
            printf("%d ", ret[i]);
        }
        printf("\n");

        while (!st.empty()) {
            ti = *st.begin();
            Q.push_back(ti.id);
            st.erase(ti);
            for (auto np : qg[ti.id]) {
                int nv = np.first;
                if (st.find(tri[nv]) != st.end()) {
                    st.erase(tri[nv]);
                    tri[nv].deg--;
                    st.insert(tri[nv]);
                }
            }
        }

        for (auto qq : Q) {
            printf("%d ", qq);
        }
        printf("\n");

        --T;
    }
    return 0;
}