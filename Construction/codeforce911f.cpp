#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

vector<int> g[MAX_SIZE];
// I found some interesting properties on this
// firstly, if the tree is a link list, the answer is simply every time
// remove one of the end point for n-1 times.
// then, let's consider the following constructive process
// 1) find the tree's diameter, then remove all the points not in the diameter
// 2) remove the diameter according to the way in the intuition.
// let's think why this is correct, for the non-diameter nodes
// let u, v be the two end points of the diameter
// consider a node w not on the diameter 
// its distance with the closest point on the diameter p is d1, and dist(p, u) = d2, dist(p, v) = d3
// suppose that d2 >= d3. Then d1 + d2 <= d2 + d3 and d1 + d3 <= d2 + d3 by definition.
// What's more, let's suppose there exists there's a node in the subtree of p has d4 + d1 >= d1 + d2
// this would form a contradiction. Hence, all nodes not on the diameter can achieve tha maximum cost.
// For a single list we left, the longer it is the larger the cost we can achieve.
// Hence, the construction is optimal.
int parent[MAX_SIZE][19];
int depth[MAX_SIZE];
int height[MAX_SIZE];
int far[MAX_SIZE];

void dfs(int v, int pre) {
    depth[v] = depth[pre] + 1;
    parent[v][0] = pre;
    int i;
    for (i = 1; i <= 18; ++i) parent[v][i] = parent[parent[v][i-1]][i-1];
    for (auto nv : g[v]) {
        if (nv != pre) {
            dfs(nv, v);
        }
    }
}
// find the bottom up height of the tree
int dfs2(int v, int pre) {
    for (auto nv : g[v]) {
        if (nv != pre) {
            int p = dfs2(nv, v);
            height[v] = max(1 + p, height[v]);
        }
    }

    return height[v];
}
// find the furthest distance from the tree to any other nodes
void dfs3(int v, int pre) {
    multiset<int> st;
    for (auto nv : g[v]) {
        if (nv != pre) {
            st.insert(height[nv]);
        }
    }

    for (auto nv : g[v]) {
        if (nv != pre) {
            far[nv] = far[v] + 1;
            st.erase(st.find(height[nv]));
            if (!st.empty()) {
                far[nv] = max(far[nv], 2 + *st.rbegin());
            }
            st.insert(height[nv]);
        }
    }

    for (auto nv : g[v]) {
        if (nv != pre) {
            dfs3(nv, v);
        }
    }
}

int LCA(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int i;
    for (i = 18; i >= 0; --i) {
        if (depth[u] >= (1 << i) + depth[v]) {
            u = parent[u][i];
        }
    }

    if (u == v) return u;

    for (i = 18; i >= 0; --i) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }

    return parent[u][0];
}

int dist(int u, int v) {
    return depth[u] + depth[v] - 2 * depth[LCA(u, v)];
}

vector<pair<pair<int, int>, int>> ans;
bool nodim[MAX_SIZE];
int deg[MAX_SIZE];
bool visited[MAX_SIZE];

int main() {
    int i, n;
    scanf("%d", &n);
    for (i = 0 ; i < n - 1; ++i) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        g[v1].push_back(v2);
        g[v2].push_back(v1);
        deg[v1]++, deg[v2]++;
    }

    if (n == 2) {
        printf("1\n");
        printf("1 2 1\n");
        return 0;
    }

    dfs(1, 0);
    dfs2(1, 0);
    dfs3(1, 0);

    int ht = 0, rt = 1, rt2 = 1;
    for (i = 1; i <= n; ++i) {
        far[i] = max(far[i], height[i]);
        if (far[i] > ht) {
            ht = far[i], rt = i;
        }
    }

    for (i = 1; i <= n; ++i) {
        if (dist(i, rt) == far[rt]) {
            rt2 = i;
            break;
        }
    }

    long long cost = 0;
    queue<int> q;
    for (i = 1; i <= n; ++i) {
        int d1 = dist(i, rt), d2 = dist(i, rt2);
        if (d1 + d2 != far[rt]) {
            cost += max(d1, d2);
            nodim[i] = true;
            if (deg[i] == 1) {
                q.push(i);
            }
        }    
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (visited[v]) continue;
        visited[v] = true;
        int d1 = dist(v, rt), d2 = dist(v, rt2);
        if (d1 >= d2) {
            ans.push_back(make_pair(make_pair(v, rt), v));
        } else {
            ans.push_back(make_pair(make_pair(v, rt2), v));
        }
        for (auto nv : g[v]) {
            if (nodim[nv] && !visited[nv]) {
                --deg[nv];
                if (deg[nv] == 1) {
                    q.push(nv);
                }
            }
        }
    }

    int d = far[rt];
    while (rt2 != rt) {
        cost += d--;
        ans.push_back(make_pair(make_pair(rt, rt2), rt2));
        for (auto v : g[rt2]) {
            if (dist(v, rt) == d) {
                rt2 = v;
                break;
            }
        }
    }

    printf("%I64d\n", cost);
    for (auto p : ans) {
        printf("%d %d %d\n", p.first.first, p.first.second, p.second);
    }


    return 0;
}