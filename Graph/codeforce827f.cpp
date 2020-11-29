#include <bits/stdc++.h>
#define MAX_SIZE 1000011
using namespace std;

struct edg {
    int cost, id, parity;
    bool operator < (edg other) const {
        return cost > other.cost;
    }
};
// edge list
vector<int> g[MAX_SIZE >> 1][2];
int from[MAX_SIZE], to[MAX_SIZE], l[MAX_SIZE], r[MAX_SIZE];
int N, M;

bool cmp(int &a, int &b) {
    return l[a] > l[b];
}

int main() {
    int i;
    priority_queue<edg, vector<edg>, less<edg>> q;
    scanf("%d%d", &N, &M);
    if (N == 1) {
        printf("0\n");
        return 0;
    }

    for (i = 1; i <= M; ++i) {
        scanf("%d%d%d%d", &from[i * 2], &to[i * 2], &l[i * 2], &r[i * 2]);
        r[i * 2]--;
        from[i * 2 + 1] = to[i * 2];
        to[i * 2 + 1] = from[i * 2];
        l[i * 2 + 1] = l[i * 2];
        r[i * 2 + 1] = r[i * 2];
        g[from[i * 2]][0].push_back(i * 2);
        g[from[i * 2]][1].push_back(i * 2);
        g[to[i * 2]][0].push_back(i * 2 + 1);
        g[to[i * 2]][1].push_back(i * 2 + 1);
    }

    for (i = 1; i <= N; ++i) {
        sort(g[i][0].begin(), g[i][0].end(), cmp);
        sort(g[i][1].begin(), g[i][1].end(), cmp);
    }

    while (!g[1][0].empty() && l[g[1][0].back()] == 0) {
        edg e = {0, g[1][0].back(), 0};
        q.push(e);
        g[1][0].pop_back();
    }

    while (!q.empty()) {
        edg curr = q.top();
        q.pop();
        if (to[curr.id] == N) {
            printf("%d\n", curr.cost + 1);
            return 0;
        }   
        // the maximum start time we are allowed if we use the current edge
        // with the current parity
        int mxright = r[curr.id] - ((r[curr.id] % 2) != curr.parity);
        while (!g[to[curr.id]][curr.parity ^ 1].empty() && l[g[to[curr.id]][curr.parity ^ 1].back()] <= mxright + 1) {
            int nxtid = g[to[curr.id]][curr.parity ^ 1].back();
            int ncost = l[nxtid];
            ncost += (ncost % 2 == curr.parity);
            ncost = max(ncost, curr.cost + 1);
            if (ncost <= r[nxtid]) {
                q.push(edg{ncost, nxtid, curr.parity ^ 1});
            }

            g[to[curr.id]][curr.parity ^ 1].pop_back();
        }
    }

    printf("-1\n");
    return 0;
}