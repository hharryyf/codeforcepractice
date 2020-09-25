#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 1011
using namespace std;

map<int, vector<pair<int, int>>> X, Y; 
struct Vertex {
    int x, y, id;
};

struct Edge {
    Vertex u, v;  
    bool ishorizontal() {
        return u.y == v.y;
    }

    bool isvertical() {
        return u.x == v.x;
    }

    int length() {
        if (ishorizontal()) return abs(u.x - v.x);
        return abs(u.y - v.y);
    }
};

Vertex vc[MAX_SIZE];
vector<Edge> edg;
int N, f[MAX_SIZE];

void init() {
    int i;
    for (i = 1; i <= N; ++i) f[i] = i;
}

int find(int v) {
    if (f[v] == v) return v;
    return f[v] = find(f[v]);
}

void unionset(int v1, int v2) {
    int a = find(v1), b = find(v2);
    f[a] = b;
}

void preprocess() {
    int i;
    auto iter = X.begin();
    while (iter != X.end()) {
        sort(iter->second.begin(), iter->second.end());
        int sz = iter->second.size();
        for (i = 0 ; i < sz - 1; ++i) {
            Vertex v1 = Vertex{iter->first, iter->second[i].first, iter->second[i].second};
            Vertex v2 = Vertex{iter->first, iter->second[i+1].first, iter->second[i+1].second};
            Edge e = Edge{v1, v2};
            edg.push_back(e);
        }
        ++iter;
    }

    iter = Y.begin();
    while (iter != Y.end()) {
        sort(iter->second.begin(), iter->second.end());
        int sz = iter->second.size();
        for (i = 0 ; i < sz - 1; ++i) {
            Vertex v1 = Vertex{iter->second[i].first, iter->first, iter->second[i].second};
            Vertex v2 = Vertex{iter->second[i+1].first, iter->first, iter->second[i+1].second};
            Edge e = Edge{v1, v2};
            edg.push_back(e);
        }
        ++iter;
    }
}

bool valid(int T) {
    init();
    int tol = N, i, j;
    for (auto e : edg) {
        if (e.length() <= T) {
            if (find(e.u.id) != find(e.v.id)) {
                unionset(e.u.id, e.v.id);
                tol--;
            }
        }
    }

    if (tol == 1) return true;
    if (tol > 4) return false;
    if (tol == 2) {
        for (auto e : edg) {
            if (find(e.u.id) != find(e.v.id) && 1ll * e.length() <= 1ll * 2 * T) return true;
        }

        for (i = 1; i <= N; ++i) {
            for (j = i + 1; j <= N; ++j) {
                if (find(i) != find(j)) {
                    if (max(abs(vc[i].x - vc[j].x), abs(vc[i].y - vc[j].y)) <= T) return true;
                }
            }
        }

        return false;
    } else if (tol == 3) {
        int sz = edg.size();
        for (i = 0 ; i < sz; ++i) {
            for (j = 1; j <= N; ++j) {
                if (find(j) != find(edg[i].u.id) && find(j) != find(edg[i].v.id) && find(edg[i].v.id) != find(edg[i].u.id)) {
                    if (edg[i].ishorizontal()) {
                        int x1 = edg[i].u.x, x2 = edg[i].v.x;
                        if (x1 > x2) swap(x1, x2);
                        if (x1 <= vc[j].x && vc[j].x <= x2) {
                            int dist = max(abs(vc[j].y - edg[i].u.y), max(x2 - vc[j].x, vc[j].x - x1));
                            if (dist <= T) return true;
                        }
                    } else {
                        int y1 = edg[i].u.y, y2 = edg[i].v.y;
                        if (y1 > y2) swap(y1, y2);
                        if (y1 <= vc[j].y && vc[j].y <= y2) {
                            int dist = max(abs(vc[j].x - edg[i].u.x), max(y2 - vc[j].y, vc[j].y - y1));
                            if (dist <= T) return true;
                        }
                    }
                }
            }
        }
        return false; 
    }

    int sz = edg.size();
    for (i = 0 ; i < sz; ++i) {
        if (edg[i].ishorizontal() || find(edg[i].u.id) == find(edg[i].v.id)) continue;
        int y1 = min(edg[i].u.y, edg[i].v.y), y2 = max(edg[i].u.y, edg[i].v.y);
        for (j = i + 1; j < sz; ++j) {
            if (edg[j].isvertical() || find(edg[j].u.id) == find(edg[j].v.id)) continue;
            if (find(edg[i].u.id) == find(edg[j].u.id)) continue;
            if (find(edg[i].u.id) == find(edg[j].v.id)) continue;
            if (find(edg[i].v.id) == find(edg[j].u.id)) continue;
            if (find(edg[i].v.id) == find(edg[j].v.id)) continue;
            int x1 = min(edg[j].u.x, edg[j].v.x), x2 = max(edg[j].u.x, edg[j].v.x);
            int x = edg[i].v.x, y = edg[j].v.y;
            if (x1 <= x && x <= x2 && y1 <= y && y <= y2) {
                if (max(max(x - x1, x2 - x), max(y - y1, y2 - y)) <= T) return true;
            }
        }
    }

    return false;
}

int main() {
    int i;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        X[x].emplace_back(y, i);
        Y[y].emplace_back(x, i);
        vc[i].x = x, vc[i].id = i, vc[i].y = y;
    }

    preprocess();

    int low = 0, high = 2e9, ans = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (valid(mid)) {
            high = mid - 1;
            ans = mid;
        } else {
            low = mid + 1;
        }
    }

    printf("%d\n", ans);
    return 0;
}