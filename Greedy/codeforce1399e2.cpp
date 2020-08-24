#include <bits/stdc++.h>
#define MAX_SIZE 100011
typedef long long ll;
using namespace std;

struct edge {
    int to, w, tp;
};

struct nd {
    int wt, sz;
    bool operator < (nd other) const {
        ll l1 = 1ll * sz * (wt - wt / 2);;
        ll l2 = 1ll * other.sz * (other.wt - other.wt / 2);;
        return l1 < l2;
    }

    ll lost() {
        return 1ll * sz * (wt - wt / 2);
    }
};

vector<edge> g[MAX_SIZE];
int sz[MAX_SIZE];
priority_queue<nd, vector<nd>> q1, q2;
ll S, tol;
int N;

void init() {
    int i;
    tol = 0;
    for (i = 1; i <= N; ++i) {
        g[i].clear();
        sz[i] = 0;
    }
    while (!q1.empty()) q1.pop();
    while (!q2.empty()) q2.pop();
}

void dfs(int v, int pre) {
    for (auto &ne : g[v]) {
        if (ne.to != pre) {
            dfs(ne.to, v);
            sz[v] += sz[ne.to];
            if (ne.tp == 1) {
                q1.push(nd{ne.w, sz[ne.to]});
            } else {
                q2.push(nd{ne.w, sz[ne.to]});
            }
            tol += 1ll * sz[ne.to] * ne.w;
        }
    }

    if (!sz[v]) sz[v] = 1;
}

void solve_case() {
    int cost = 0;
    while (tol > S) {
        if (q2.empty()) {
            cost += 1;
            auto e = q1.top();
            q1.pop();
            tol -= e.lost();
            e.wt = e.wt / 2;
            if (e.wt > 0) {
                q1.push(e);
            }
        } else if (q1.empty()) {
            cost += 2;
            auto e = q2.top();
            q2.pop();
            tol -= e.lost();
            e.wt = e.wt / 2;
            if (e.wt > 0) {
                q2.push(e);
            }
        } else {
            auto e1 = q1.top(), e2 = q2.top();
            if (tol - e1.lost() <= S) {
                cost += 1;
                break;
            }

            if (e1.lost() >= e2.lost()) {
                cost += 1;
                auto e = q1.top();
                q1.pop();
                tol -= e.lost();
                e.wt = e.wt / 2;
                if (e.wt > 0) {
                    q1.push(e);
                }
            } else {
                // if we can use q1 twice and achieve a better cost than q2
                // we should apply q1 twice, otherwise we should attempt q2
                auto e = q1.top();
                auto v = e;
                q1.top();
                ll v1 = v.lost();
                q1.pop();
                v.wt /= 2;
                if (!q1.empty()) {
                    auto v2 = q1.top();
                    v1 += max(v.lost(), v2.lost());
                } else {
                    v1 += v.lost(); 
                }
                if (v1 >= e2.lost()) {
                    cost++;
                    tol -= e.lost();
                    if (v.wt > 0) {
                        q1.push(v);
                    }
                } else {
                    q1.push(e);
                    v = q2.top();
                    q2.pop();
                    cost += 2;
                    tol -= v.lost();
                    v.wt /= 2;
                    if (v.wt > 0) {
                        q2.push(v);
                    }
                }
            }
        }
    }

    printf("%d\n", cost);
}

int main() {
    int T, i;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d%I64d", &N, &S);
        init();
        for (i = 0 ; i < N - 1; ++i) {
            int v1, v2, w, tp;
            scanf("%d%d%d%d", &v1, &v2, &w, &tp);
            g[v1].push_back(edge{v2, w, tp});
            g[v2].push_back(edge{v1, w, tp});
        }

        dfs(1, 0);

        solve_case();
    }
    return 0;
}