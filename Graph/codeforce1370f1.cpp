#include <bits/stdc++.h>
#define MAX_SIZE 1011 
using namespace std;

vector<int> g[MAX_SIZE];
int height[MAX_SIZE], id[MAX_SIZE], sz[MAX_SIZE];
int depth[MAX_SIZE];
int parent[MAX_SIZE];
int path[MAX_SIZE];
int dist[MAX_SIZE];
int n, cnt;
char st[9];
void init() {
    int i;
    for (i = 0 ; i < MAX_SIZE; ++i) {
        g[i].clear();
    }
    memset(id, 0, sizeof(id));
    memset(dist, 0, sizeof(dist));
    memset(path, 0, sizeof(path));
    memset(height, 0, sizeof(height));
    memset(sz, 0, sizeof(sz));
    memset(depth, 0, sizeof(depth));
    memset(parent, 0, sizeof(parent));
    cnt = 0;
}

pair<int, int> query(vector<int> &node) {
    pair<int, int> ret;
    printf("? %d", (int) node.size());
    for (auto v : node) {
        printf(" %d", v);
    }
    printf("\n");
    fflush(stdout);
    scanf("%d%d", &ret.first, &ret.second);
    return ret;
}

void dfs(int v, int pre) {
    id[v] = ++cnt;
    depth[v] = depth[pre] + 1;
    sz[v] = 1;
    parent[v] = pre;
    for (auto nv : g[v]) {
        if (!id[nv]) {
            dfs(nv, v);
            height[v] = max(height[v], 1 + height[nv]);
            sz[v] += sz[nv];
        }
    }
}

void dfs2(int v, int pre) {
    dist[v] = dist[pre] + 1;
    for (auto nv : g[v]) {
        if (nv != pre) {
            dfs2(nv, v);
        }
    }
}

pair<int, int> general_query() {
    int i;
    vector<int> qr;
    for (i = 1; i <= n; ++i) {
        qr.push_back(i);
    }

    return query(qr);
}

int main() {
    int i, T;
    scanf("%d", &T);
    while (T-- > 0) {
        init();
        scanf("%d", &n);
        for (i = 0 ; i < n - 1; ++i) {
            int v1, v2;
            scanf("%d%d", &v1, &v2);
            g[v1].push_back(v2);
            g[v2].push_back(v1);
        }

        dfs(1, 0);

        pair<int, int> ret = general_query();
        // now ret.first is a node on the path
        // ret.second is the distance of the shortest path from ret to v
        // here we apply binary search
        int low = 0, high = height[ret.first];
        int down = ret.first;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            // cout << "query height " << mid << endl;
            vector<int> node;
            for (i = 1; i <= n; ++i) {
                if (id[i] >= id[ret.first] && id[i] <= sz[ret.first] + id[ret.first] - 1) {
                    if (depth[i] - depth[ret.first] == mid) {
                        node.push_back(i);
                    }
                }
            }

            if (node.empty()) {
                high = mid - 1;
            } else {
                auto p = query(node);
                if (p.second == ret.second) {
                    down = p.first;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
        }

        if (depth[down] - depth[ret.first] == ret.second) {
            printf("! %d %d\n", ret.first, down);
            fflush(stdout);
            scanf("%s", st);
            if (st[0] == 'I') {
                exit(0);
            }
            continue;
        }

        int v = down;
        // cout << "! "<< down << endl;
        while (v != ret.first  && v != 0) {
            path[v] = 1;
            v = parent[v];
        }
        path[v] = 1;
        dist[0] = -1;
        // cout << "exit " << ret.first << endl;
        dfs2(ret.first, 0);
        vector<int> node;
        for (i = 1; i <= n; ++i) {
            if (dist[i] == ret.second - (depth[down] - depth[ret.first])) {
                if (!path[i]) {
                    node.push_back(i);
                }
            }
        }
        
        if ((int) node.size() == 1) {
            ret.first = node.back();
        } else {
            ret = query(node);
        }
        printf("! %d %d\n", ret.first, down);
        fflush(stdout);
        scanf("%s", st);
        if (st[0] == 'I') {
            exit(0);
        }
    }
    return 0;
}