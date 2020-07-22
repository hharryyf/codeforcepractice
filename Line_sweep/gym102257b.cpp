#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

struct edge {
    int from, to, w;
};

int f[MAX_SIZE];
int sz[MAX_SIZE];
pair<int, int> history[MAX_SIZE << 1];
int tol = 0;

int find(int x, int tp=1) {
    if (f[x] == x) return x;
    if (tp) {
        return f[x] = find(f[x], tp);
    }

    return find(f[x], tp);
}

void cancel() {
    if (tol <= 0) return;
    auto p = history[--tol];
    sz[p.second] -= sz[p.first];
    f[p.first] = p.first;
}

void unionset(int x, int y, int tp=1) {
    int a = find(x, tp), b = find(y, tp);
    if (a == b) return;
    if (sz[a] > sz[b]) swap(a, b);
    if (tp == 0) {
        history[tol++] = {a, b};
    }
    sz[b] += sz[a];
    f[a] = b;
}

edge edg[MAX_SIZE];
int ok[MAX_SIZE];
int wt[MAX_SIZE];
// q[i].from type of the ith query
// q[i].to vertex/edge id
// q[i].w weight
edge q[MAX_SIZE];
int ans[MAX_SIZE];
int N, M, Q;
vector<int> in, pend, qrs;
vector<int> complete;

static bool cmp(const int &a, const int &b) {
    return q[a].w < q[b].w;
}

static bool cmp2(const int &a, const int &b) {
    return edg[a].w < edg[b].w;
}

static bool cmp3(const int &a, const int &b) {
    return wt[a] < wt[b];
}

void init() {
    int i;
    for (i = 1; i <= N; ++i) f[i] = i, sz[i] = 1;
    in.clear(), qrs.clear(), pend.clear();
    tol = 0;
}

void Merge() {
    // merge in and pend to complete
    int i = 0, j = 0, k = 0;
    int sz1 = in.size(), sz2 = pend.size();
    while (i < sz1 && j < sz2) {
        if (edg[in[i]].w < edg[pend[j]].w) {
            complete[k++] = in[i++];
        } else {
            complete[k++] = pend[j++];
        }
    }

    while (i < sz1) {
        complete[k++] = in[i++];
    }

    while (j < sz2) {
        complete[k++] = pend[j++];
    }
/*
    cout << "in edge " << endl;
    for (auto v : in) {
        cout << "idx= " << v << " wt= " << edg[v].w << endl;
    }

    cout << "pend edge " << endl;
    for (auto v : pend) {
        cout << "idx= " << v << " wt= " << edg[v].w << endl;
    }

    cout << "complete edge " << endl;
    for (auto v : complete) {
        cout << "idx= " << v << " wt= " << edg[v].w << endl;
    }*/
}

int main() {
    int i, j, k;
    scanf("%d%d", &N, &M);
    int block_size = sqrt(log2(N) * N);
    block_size = max(block_size, 1);
    for (i = 1; i <= M; ++i) {
        scanf("%d%d%d", &edg[i].from, &edg[i].to, &edg[i].w);       
        edg[i].w *= -1;
        wt[i] = edg[i].w;
        ok[i] = 1;
        complete.push_back(i);
    }

    scanf("%d", &Q);

    for (i = 1; i <= Q; ++i) {
        scanf("%d%d%d", &q[i].from, &q[i].to, &q[i].w);
        q[i].w *= -1;
    }

    sort(complete.begin(), complete.end(), cmp2);

    for (i = 1; i <= Q; ++i) {
        int L = (i - 1) * block_size + 1, R = min(Q, i * block_size);
        if (L > R || L > Q) break;
        init();
        for (j = L; j <= R; ++j) {
            if (q[j].from == 1) {
                ok[q[j].to] = 0;
            } else {
                qrs.push_back(j);
            }
        }

        for (j = 0; j < M; ++j) {

            if (ok[complete[j]]) {
                //cout << "in insert " << complete[j] << endl;
                in.push_back(complete[j]);
            } else {
                //cout << "pend insert " << complete[j] << endl;
                pend.push_back(complete[j]);
            }

            wt[j] = edg[j].w;
        }
        // here is the problem, we cannot call sort on in here
        // otherwise we are booking a TLE
        // sort(in.begin(), in.end(), cmp2);
        sort(qrs.begin(), qrs.end(), cmp);

        k = 0;
        int cp = in.size();
        for (auto qq : qrs) {
            for (auto e : pend) {
                wt[e] = edg[e].w;
            }    

            for (j = L; j < qq; ++j) {
                if (q[j].from == 1) {
                    wt[q[j].to] = q[j].w;
                }
            }

            sort(pend.begin(), pend.end(), cmp3);

            while (k < cp && edg[in[k]].w <= q[qq].w) {
                unionset(edg[in[k]].from, edg[in[k]].to);
                // cout <<  "general join " << edg[in[k]].from << " " << edg[in[k]].to << endl;
                k++;
            }

            for (auto pp : pend) {
                if (wt[pp] <= q[qq].w) {
                    unionset(edg[pp].from, edg[pp].to, 0);
                    // cout << edg[pp].from << " " << edg[pp].to << " joined " << wt[pp] << " < " << q[qq].w << endl;
                } else {
                    break;
                }
            }

            ans[qq] = sz[find(q[qq].to, 0)];
            // cout << "answer query " << qq << endl;
            while (tol > 0) cancel();
        }

        for (j = L; j <= R; ++j) {
            if (q[j].from == 1) {
                edg[q[j].to].w = q[j].w;
                ok[q[j].to] = 1;
            }
        }

        sort(pend.begin(), pend.end(), cmp2);

        Merge();
    }

    for (i = 1; i <= Q; ++i) {
        if (q[i].from == 2) {
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}