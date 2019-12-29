#include <bits/stdc++.h>
#pragma GCC optimize(2)
typedef long long ll;
#define MAX_SIZE 100011
using namespace std;

int dfsord[MAX_SIZE];
int subsz[MAX_SIZE];
vector<int> g[MAX_SIZE];
int n, block, m;
int k = 1;
int visited[MAX_SIZE];
int color[MAX_SIZE];
int tmp[MAX_SIZE];
int ans[MAX_SIZE], cnt[MAX_SIZE], tol[MAX_SIZE];


struct qrs {
    int l, r, k;
    int id;
};

qrs q[MAX_SIZE];

void dfs(int v, int pre) {
    dfsord[v] = k++;
    color[dfsord[v]] = tmp[v];
    subsz[v] = 1;
    for (auto nv : g[v]) {
        if (nv != pre) {
            dfs(nv, v);
            subsz[v] += subsz[nv];
        }
    }
}

static bool cmp(const qrs &a, const qrs &b) {
    if (a.l / block != b.l / block) return (a.l / block) < (b.l / block);
    return a.r < b.r;
}

void add(int index) {
    cnt[color[index]]++;
    tol[cnt[color[index]]]++;
}

void del(int index) {
    tol[cnt[color[index]]]--;
    cnt[color[index]]--;
}

int main() {
    int i, j;
    int l = 1, r = 0;
    scanf("%d%d", &n, &m);
    block = sqrt(n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &tmp[i]);
    }
    
    for (i = 1; i < n; i++) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        g[v1].push_back(v2);
        g[v2].push_back(v1);
    }
    
    dfs(1, -1);
    
    for (i = 1; i <= m; i++) {
        int v1, kk;
        scanf("%d%d", &v1, &kk);
        q[i].l = dfsord[v1], q[i].r = dfsord[v1] + subsz[v1] - 1, q[i].k = kk, q[i].id = i;
    }
    
    sort(q + 1, q + 1 + m, cmp);
    
    for (i = 1; i <= m; i++) {
        while (l < q[i].l) {
            del(l);
            l++;
        }
        
        while (l > q[i].l) {
            add(l-1);
            l--;
        }
        
        while (r > q[i].r) {
            del(r);
            r--;
        }
        
        while (r < q[i].r) {
            add(r+1);
            r++;
        }
        
        ans[q[i].id] = tol[q[i].k];
    }
    
    for (i = 1; i <= m; i++) {
        printf("%d\n", ans[i]);
    }
    return 0;
}
