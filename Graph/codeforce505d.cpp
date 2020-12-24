#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

vector<int> g[MAX_SIZE];
set<int> h[MAX_SIZE];
int cmpid[MAX_SIZE], low[MAX_SIZE], visited[MAX_SIZE], instack[MAX_SIZE];
int sz[MAX_SIZE];
int ok = 0;
stack<int> st;
int N, M, cnt = 0, cid = 1;
int ans = 0;

void tarjan(int v) {
    st.push(v);
    instack[v] = 1;
    visited[v] = low[v] = ++cnt;
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
            instack[st.top()] = 0;
            cmpid[st.top()] = cid;
            st.pop();
        }

        cmpid[st.top()] = cid++;
        instack[st.top()] = 0;
        st.pop();

    }
}

void dfs2(int v) {
    visited[v] = 1;
    if (sz[v] != 1) ok = 0;
    ans += sz[v];
    for (auto nv : h[v]) {
        if (!visited[nv]) {
            dfs2(nv);
        }
    }
}

int main() {
    int i;
    scanf("%d%d", &N, &M);
    for (i = 1; i <= M; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
    }

    for (i = 1; i <= N; ++i) {
        if (!visited[i]) {
            tarjan(i);
        }
    }

    for (i = 1; i <= N; ++i) {
        sz[cmpid[i]]++;
        for (auto v : g[i]) {
            if (cmpid[i] != cmpid[v]) {
                h[cmpid[i]].insert(cmpid[v]);
                h[cmpid[v]].insert(cmpid[i]);
            }
        }
    }

    for (i = 0 ; i < MAX_SIZE; ++i) visited[i] = 0;
    for (i = 1; i < cid; ++i) {
        if (!visited[i]) {
            ok = 1;
            dfs2(i);
            ans -= ok;
        }
    }


    printf("%d\n", ans);
    return 0;
}