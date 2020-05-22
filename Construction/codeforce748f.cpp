#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

/*
    Key observation here is there's always a node satisfies the
    maximum subtree has no more than k special nodes.
    Hence, the answer is always 1.

    We should firstly use dfs to find that node and do a second dfs 
*/

vector<int> g[MAX_SIZE];
vector<int> ans[MAX_SIZE];
int special[MAX_SIZE];
int f[MAX_SIZE];
int root = 1;
int n, k;

void dfs1(int v, int pre) {
    int max_child = special[v];
    f[v] = special[v];
    for (auto nv : g[v]) {
        if (nv != pre) {
            dfs1(nv, v);
            f[v] += f[nv];
            max_child = max(max_child, f[nv]);
        }
    }

    max_child = max(max_child, 2 * k - f[v]);
    if (max_child <= k) {
        root = v;
    }
}

void dfs2(int v, int pre, vector<int> &node) {
    if (special[v]) {
        node.push_back(v);
    }

    for (auto nv : g[v]) {
        if (nv != pre) {
            dfs2(nv, v, node);
        }
    }
}

struct nd {
    int id;
    bool operator < (nd other) const {
        return ans[id].size() < ans[other.id].size();
    }
};

int main() {
    int i;
    scanf("%d%d", &n, &k);
    for (i = 1; i < n; ++i) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        g[v1].push_back(v2);
        g[v2].push_back(v1);
    }

    for (i = 1; i <= 2 * k; ++i) {
        int v;
        scanf("%d", &v);
        special[v] = 1;
    }

    dfs1(1, 0);
    
    printf("1\n%d\n", root);
    priority_queue<nd> q;
    // now we have a root, we simiply needs to partition the special nodes
    // in the subtree of root to corresponding chunks.'
    for (auto nv : g[root]) {
        dfs2(nv, root, ans[nv]);
        if (!ans[nv].empty()) {
            q.push(nd{nv});
        }
    }

    if (special[root]) {
        ans[root].push_back(root);
        q.push(nd{root});
    }

    while (!q.empty()) {
        auto t1 = q.top();
        q.pop();
        auto t2 = q.top();
        q.pop();
        printf("%d %d %d\n", ans[t1.id].back(), ans[t2.id].back(), root);
        ans[t1.id].pop_back(), ans[t2.id].pop_back();
        if (!ans[t1.id].empty()) {
            q.push(nd{t1.id});
        }

        if (!ans[t2.id].empty()) {
            q.push(nd{t2.id});
        }
    }
    return 0;
}