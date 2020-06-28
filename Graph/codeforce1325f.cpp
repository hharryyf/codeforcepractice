#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

vector<int> g[MAX_SIZE];
int p[MAX_SIZE];
int depth[MAX_SIZE];
int cycle = 0;
int chunk[MAX_SIZE];
int cid[MAX_SIZE];
int visited[MAX_SIZE];
void dfs(int v, int pre) {
    p[v] = pre;
    visited[v] = 1;
    depth[v] = depth[pre] + 1;
    chunk[depth[v] % (cycle-1)]++;
    cid[v] = depth[v] % (cycle-1);
    for (auto nv : g[v]) {
        if (nv == pre) continue;
        if (!visited[nv]) {
            dfs(nv, v);
        } else {
            if (depth[v] - depth[nv] + 1 >= cycle) {
                printf("2\n%d\n", depth[v] - depth[nv] + 1);
                while (v != nv) {
                    printf("%d\n", v);
                    v = p[v];
                }
                printf("%d\n", v);
                exit(0);
            }
        }
    }
}

int main() {
    int i, n, m;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; ++i) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        g[v1].push_back(v2);
        g[v2].push_back(v1);
    }

    cycle = (int) ceil(sqrt(n));

    depth[0] = -1;   
    dfs(1, 0);

    printf("1\n");

    int id = 0;
    for (i = 1; i <= n; ++i) {
        if (chunk[i] > chunk[id]) id = i;
    }
    // cout << cycle << endl;
    int j;
    for (i = 1, j = 0; i <= n && j < cycle; ++i) {
        if (cid[i] == id) {
            printf("%d ", i);
            j++;
        }
    }
    printf("\n");
    return 0;
}