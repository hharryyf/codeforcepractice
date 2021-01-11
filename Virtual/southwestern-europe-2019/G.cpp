#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

struct node {
    int id, v;
    bool operator < (node other) const {
        return v > other.v;
    }
};

int S, L, N;
char st[24], pt[24];
vector<string> vc;
int good[203][203], visited[MAX_SIZE];
vector<int> g[MAX_SIZE];
node nd[MAX_SIZE];
int ans[MAX_SIZE];
int pos[MAX_SIZE], indegree[MAX_SIZE];
map<string, int> mp;

int main() {
    int i, j;
    scanf("%d%d%d", &S, &L, &N);
    for (i = 0; i < S; ++i) {
        scanf("%s", st);
        vc.push_back(string(st));
    }

    sort(vc.begin(), vc.end());
    for (i = 0 ; i < S; ++i) {
        mp[vc[i]] = i;
    }

    for (i = 0 ; i < L; ++i) {
        scanf("%s%s", st, pt);
        int u = mp[string(st)], v = mp[string(pt)];
        good[u][v] = good[v][u] = 1;
    }

    for (i = 1; i <= N; ++i) {
        scanf("%s", st);
        int id = mp[string(st)];
        if (pos[id] != 0) {
            g[pos[id]].push_back(i);
        }
        pos[id] = i;
        nd[i].id = i, nd[i].v = id;
        for (j = 0 ; j < S; ++j) {
            if (j == id || !pos[j] || good[j][id]) continue;
            g[pos[j]].push_back(i);
        }
    }

    for (i = 1; i <= N; ++i) {
        for (auto nv : g[i]) {
            indegree[nv]++;
        }
    }

    priority_queue<node> q;
    for (i = 1; i <= N; ++i) {
        if (indegree[i] == 0) {
            q.push(nd[i]);
        }
    }

    vector<int> ret;
    while (!q.empty()) {
        auto curr = q.top();
        q.pop();
        ret.push_back(curr.v);
        for (auto nv : g[curr.id]) {
            indegree[nv]--;
            if (indegree[nv] == 0) {
                q.push(nd[nv]);
            }
        }
    }

    for (auto id : ret) {
        printf("%s ", vc[id].c_str());
    }
    printf("\n");
    return 0;
}