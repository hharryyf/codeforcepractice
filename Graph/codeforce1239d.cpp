#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 1000111
using namespace std;

int low[MAX_SIZE], instack[MAX_SIZE], visited[MAX_SIZE];
int cnt = 0;
stack<int> st;
vector<int> g[MAX_SIZE];
int cid = 1;
int id[MAX_SIZE];
int deg[MAX_SIZE];
vector<int> ret;

void init(int n) {
    int i;
    while (!st.empty()) st.pop();
    for (i = 0 ; i <= n + 2; ++i) {
        low[i] = instack[i] = visited[i] = 0;
        id[i] = deg[i] = 0;
        g[i].clear();
    }
    ret.clear();
    cnt = 0;
    cid = 1;
}

void tarjan(int v) {
    st.push(v);
    instack[v] = 1;
    low[v] = visited[v] = ++cnt;
    for (auto nv : g[v]) {
        if (!visited[nv]) {
            tarjan(nv);
            low[v] = min(low[v], low[nv]);
        } else if (instack[nv]) {
            low[v] = min(low[v], visited[nv]);
        }
    }

    if (low[v] == visited[v]) {
        while (st.top() != v) {
            id[st.top()] = cid;
            instack[st.top()] = 0;
            st.pop();
        }
        id[st.top()] = cid++;
        instack[st.top()] = 0;
        st.pop();
    }
} 

int n;

void solve() {
    int i, j;
    if (cid <= 2) {
        printf("No\n");
        return;
    }

    printf("Yes\n");
    for (i = 1; i <= n; ++i) {
        for (auto v : g[i]) {
            if (id[i] != id[v]) {
                deg[id[i]]++;
            }
        }
    }

    int v = 1;
    for (i = 1; i < cid; ++i) {
        if (deg[i] == 0) {
            v = i;
            break;
        }
    }

    for (i = 1; i <= n; ++i) {
        if (id[i] == v) {
            ret.push_back(i);
        }
    }

    int p = ret.size();
    printf("%d %d\n", p, n - p);
    for (auto r : ret) {
        printf("%d ", r);
    }
    printf("\n");
    for (i = 1, j = 0; i <= n; ++i) {
        if (j < p && i == ret[j]) {
            j++;
            continue;
        }
        printf("%d ", i);
    }
    printf("\n");
}

int main() {
    int T, i;
    scanf("%d", &T);
    while (T-- > 0) {
        int m;
        scanf("%d%d", &n, &m);
        init(n);
        for (i = 1; i <= m; ++i) {
            int v1, v2;
            scanf("%d%d", &v1, &v2);
            if (v1 != v2) {
                g[v1].push_back(v2);
            }
        }

        for (i = 1; i <= n; ++i) {
            if (!visited[i]) tarjan(i);
        }

        solve();
    }
    return 0;
}