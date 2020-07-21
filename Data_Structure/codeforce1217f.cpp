#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

pair<int, int> edg[MAX_SIZE][2];
int f[MAX_SIZE];
int sz[MAX_SIZE];
vector<pair<int, int>> history;
// in the union-find relation, pending
set<pair<int, int>> in, pend, possible;
int tp[MAX_SIZE];
int ans[MAX_SIZE];
int N;
int find(int x, int cp=0) {
    if (f[x] == x) return x;
    if (cp) {
        return find(f[x], cp);
    }
    return f[x] = find(f[x], cp);
}

void cancel() {
    if (history.empty()) return;
    auto p = history.back();
    history.pop_back();
    f[p.first] = p.first;
    sz[p.second] -= sz[p.first];
}

void unionset(int x, int y, int tp=0) {
    int a = find(x, tp), b = find(y, tp);
    if (a != b) {
        if (sz[a] > sz[b]) swap(a, b);
        // join a, b
        sz[b] += sz[a];
        f[a] = b;
        if (tp) {
            history.emplace_back(a, b);
        }
    }
}

void init() {
    int i;
    for (i = 1 ; i <= N; ++i) {
        f[i] = i, sz[i] = 1;
    }
}

void reconstruct() {
    int i;
    for (i = 1 ; i <= N; ++i) {
        f[i] = i, sz[i] = 1;
    }

    for (auto &e : in) {
        unionset(e.first, e.second);
    }

    history.clear();
}

void addpend(pair<int, int> &e) {
    if (pend.find(e) != pend.end()) {
        pend.erase(e); 
    } else {
        pend.insert(e);
    }
}

void addin(pair<int, int> &e) {
    if (in.find(e) != in.end()) {
        in.erase(e);
    } else {
        in.insert(e);
    }
}

int main() {
    int i, j, Q;
    scanf("%d%d", &N, &Q);
    init();
    int block_size = 5000;
    for (i = 1; i <= Q; ++i) {
        scanf("%d", &tp[i]);
        int x, y;
        scanf("%d%d", &x, &y);
        edg[i][0].first = (x - 1) % N + 1;
        edg[i][0].second = (y - 1) % N + 1;
        if (edg[i][0].first > edg[i][0].second) swap(edg[i][0].first, edg[i][0].second);
        edg[i][1].first = x % N + 1;
        edg[i][1].second = y % N + 1;  
        if (edg[i][1].first > edg[i][1].second) swap(edg[i][1].first, edg[i][1].second);     
    }

    for (i = 1; i <= Q; ++i) {
        int L = (i - 1) * block_size + 1, R = min(Q, block_size * i);
        if (L > Q || L > R) break;
        in.clear();
        pend.clear();
        possible.clear();
        for (j = L; j <= R; ++j) {
            if (tp[j] == 2) continue;
            possible.insert(make_pair(edg[j][0].first, edg[j][0].second));
            possible.insert(make_pair(edg[j][1].first, edg[j][1].second));
        }

        for (j = 1; j < L; ++j) {
            if (tp[j] == 2) continue;
            if (possible.find(edg[j][ans[j-1]]) == possible.end()) {
                addin(edg[j][ans[j-1]]);
            } else {
                addpend(edg[j][ans[j-1]]);
            }
        }
        reconstruct();
        // cout << "finish construct " << endl;
        for (j = L; j <= R; ++j) {
            if (tp[j] == 2) {
                while (!history.empty()) {
                    cancel();
                }

                for (auto &e : pend) {
                    // cout << "pending " << e.first << " " << e.second << endl;
                    unionset(e.first, e.second, 1);
                }

                ans[j] = (find(edg[j][ans[j-1]].first, 1) == find(edg[j][ans[j-1]].second, 1));
            } else {
                addpend(edg[j][ans[j-1]]);
                ans[j] = ans[j-1];
            }
        }
    }

    for (i = 1; i <= Q; ++i) {
        if (tp[i] == 2) {
            printf("%d", ans[i]);
        }
    }
    return 0;
}