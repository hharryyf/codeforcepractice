#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 251111
using namespace std;

struct edge {
    int from, to;
};

int ok[MAX_SIZE << 1];
edge edg[MAX_SIZE << 1];
int cnt = 0;
// q[i][0] type, q[i][1] id
int q[MAX_SIZE][2];
// inuse means a vertex is in "useful"
// in the current block
int inuse[MAX_SIZE];
map<int, int> eid[MAX_SIZE];
int online[MAX_SIZE];
int ret[MAX_SIZE];
char st[5];
vector<pair<int, int>> g[MAX_SIZE];
int N, M, Q;

int main() {
    int i, j, block_size = 1, k;
    scanf("%d%d%d%d", &N, &M, &Q, &k);
    block_size = sqrt(Q);
    for (i = 1; i <= k; ++i) {
        scanf("%d", &j);
        online[j] = 1;
    } 

    for (i = 1; i <= M; ++i) {
        scanf("%d%d", &j, &k);
        if (j > k) swap(j, k);
        eid[j][k] = ++cnt;
        edg[i].from = j, edg[i].to = k;
        ok[i] = 1;
    }

    int u, v, L, R;
    for (i = 0; i < Q; ++i) {
        scanf("%s", st);
        if (st[0] == 'O') {
            q[i][0] = 0;
            scanf("%d", &q[i][1]);
        } else if (st[0] == 'F') {
            q[i][0] = 1;
            scanf("%d", &q[i][1]);
        } else if (st[0] == 'A') {
            q[i][0] = 2;
            scanf("%d%d", &u, &v);
            if (u > v) swap(u, v);
            int id = eid[u][v];
            if (id == 0) {
                eid[u][v] = ++cnt, edg[cnt].from = u, edg[cnt].to = v, id = cnt;
            }
            q[i][1] = id;
        } else if (st[0] == 'D') {
            q[i][0] = 3;
            scanf("%d%d", &u, &v);
            if (u > v) swap(u, v);
            int id = eid[u][v];
            q[i][1] = id;
        } else {
            q[i][0] = 4;
            scanf("%d", &q[i][1]);
        }
    }

    for (j = 0; j < Q; ++j) {
        L = j * block_size, R = min(Q - 1, L + block_size - 1);
        if (L > R || L > Q) break;
        for (i = L; i <= R; ++i) {
            if (q[i][0] == 2 || q[i][0] == 3) {
                inuse[edg[q[i][1]].from] = inuse[edg[q[i][1]].to] = 1;
            } else {
                inuse[q[i][1]] = 1;
            }
        }

        for (i = 1; i <= N; ++i) {
            ret[i] = 0;
            g[i].clear();
        }

        for (i = 1; i <= cnt; ++i) {
            // add in the edges that are previously added before this block
            if (ok[i]) {
                if (inuse[edg[i].from] && inuse[edg[i].to]) {
                    // probably useful for the block
                    g[edg[i].from].emplace_back(edg[i].to, i);
                    g[edg[i].to].emplace_back(edg[i].from, i);
                    ret[edg[i].from] += online[edg[i].to];
                    ret[edg[i].to] += online[edg[i].from];
                } else if (inuse[edg[i].from]) {
                    // not useful at all, just update the edg[i].from cnt value 
                    ret[edg[i].from] += online[edg[i].to];
                } else if (inuse[edg[i].to]) {
                    // not useful at all, just update the edg[i].to cnt value
                    ret[edg[i].to] += online[edg[i].from];
                } 
            } else {
                if (inuse[edg[i].from] && inuse[edg[i].to]) {
                    g[edg[i].from].emplace_back(edg[i].to, i);
                    g[edg[i].to].emplace_back(edg[i].from, i);
                }
            }
        }

        for (i = L; i <= R; ++i) {
            if (q[i][0] == 0) {
                online[q[i][1]] = 1;
                for (auto p : g[q[i][1]]) {
                    ret[p.first] += ok[p.second];
                }
                inuse[q[i][1]] = 0;
            } else if (q[i][0] == 1) {
                online[q[i][1]] = 0;
                for (auto p : g[q[i][1]]) {
                    ret[p.first] -= ok[p.second];
                }
                inuse[q[i][1]] = 0;
            } else if (q[i][0] == 2) {
                ok[q[i][1]] = 1;
                ret[edg[q[i][1]].from] += online[edg[q[i][1]].to];
                ret[edg[q[i][1]].to] += online[edg[q[i][1]].from];
                inuse[edg[q[i][1]].from] = inuse[edg[q[i][1]].to] = 0;
            } else if (q[i][0] == 3) {
                ok[q[i][1]] = 0;
                ret[edg[q[i][1]].from] -= online[edg[q[i][1]].to];
                ret[edg[q[i][1]].to] -= online[edg[q[i][1]].from];
                inuse[edg[q[i][1]].from] = inuse[edg[q[i][1]].to] = 0;
            } else {
                printf("%d\n", ret[q[i][1]]);
            }
        }
    }
    return 0;
}