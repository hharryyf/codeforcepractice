#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

vector<int> g[MAX_SIZE];
int k;
int p[MAX_SIZE], depth[MAX_SIZE];
int visited[MAX_SIZE];
int cnt[MAX_SIZE];

void dfs(int v, int pre) {
    int backvertex = -1;
    visited[v] = 1;
    depth[v] = depth[pre] + 1;
    p[v] = pre;
    cnt[depth[v] % 2]++;
    for (auto nv : g[v]) {
        if (nv != pre && depth[nv] >= 1) {
            if (backvertex == -1 || depth[backvertex] < depth[nv]) {
                backvertex = nv;
            }
        }
    }

    if (backvertex != -1) {
        vector<int> ret;
        while (v != backvertex) {
            ret.push_back(v);
            v = p[v];
        }
        ret.push_back(v);
        if ((int) ret.size() <= k) {
            printf("2\n%d\n", (int) ret.size());
            for (auto nd : ret) {
                printf("%d ", nd);
            }
            printf("\n");
        } else {
            int i = 0;
            printf("1\n");
            if (k % 2 == 0) {
                k = k / 2;
            } else {
                k = k / 2 + 1;
            }
            
            while (k > 0) {
                printf("%d ", ret[i]);
                i += 2;
                k--;
            }
            printf("\n");
        }
        
        exit(0);
    }

    for (auto nv : g[v]) {
        if (!visited[nv]) {
            dfs(nv, v);
        }
    }
}

int main() {
    int n, m, i;
    scanf("%d%d%d", &n, &m, &k);
    for (i = 1; i <= m; ++i) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        g[v1].push_back(v2);
        g[v2].push_back(v1);
    }

    dfs(1, 0);

    if (cnt[0] > cnt[1]) {
        printf("1\n");
        if (k % 2 == 0) {
            k = k / 2;
        } else {
            k = k / 2 + 1;
        }
        for (i = 1; i <= n && k > 0; ++i) {
            if (depth[i] % 2 == 0) {
                k--;
                printf("%d ", i);
            }
        }
    } else {
        printf("1\n");
        if (k % 2 == 0) {
            k = k / 2;
        } else {
            k = k / 2 + 1;
        }
        for (i = 1; i <= n && k > 0; ++i) {
            if (depth[i] % 2 == 1) {
                k--;
                printf("%d ", i);
            }
        }
    }
    return 0;
}