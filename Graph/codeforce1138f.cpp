#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 5000011
using namespace std;
/*
    This code is guarenteed to be algorithm correct, however it would get MLE
    because of the insane memory constraints
*/
list<int> g[MAX_SIZE];
list<int> h[MAX_SIZE];
int cmpid[MAX_SIZE], low[MAX_SIZE], visited[MAX_SIZE], instack[MAX_SIZE];
int wt[MAX_SIZE];
stack<int> st;
char conn[52];
int N, M, d, cnt = 0;
int dp[MAX_SIZE];

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
            cmpid[st.top()] = v;
            st.pop();
        }

        cmpid[st.top()] = v;
        instack[st.top()] = 0;
        st.pop();

    }
}

void dfs(int v) {
    if (dp[v] != -1) return;
    dp[v] = wt[v];
    int curr = 0;
    for (auto nv : h[v]) {
        if (dp[nv] == -1) {
            dfs(nv);
            curr = max(curr, dp[nv]);
        }
    }

    dp[v] += curr;
}

void addedge(int u1, int d1, int u2, int d2) {
    int idx1 = d1 + u1 * d, idx2 = d2 + u2 * d;
    g[idx1].push_back(idx2);
}

int main() {
    int i, j;
    scanf("%d%d%d", &N, &M, &d);
    for (i = 0; i < M; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u, --v;
        for (j = 0 ; j < d; ++j) {
            addedge(u, j, v, (j + 1) % d);
        }
    }

    tarjan(0);
    for (i = 0 ; i < d * N; ++i) {
        if (!visited[i]) continue;
        for (auto v : g[i]) {
            if (!visited[v]) continue;
            if (cmpid[i] == cmpid[v]) continue;
            h[cmpid[i]].push_back(cmpid[v]);
            // cout << "addedge " << cmpid[i] << " " << cmpid[v] << endl;
        }
    }

    for (i = 0 ; i < N; ++i) {
        scanf("%s", conn);
        // if (!visited[i]) continue;
        for (j = 0 ; j < d; ++j) {
            if (!visited[i * d + j]) continue;
            dp[cmpid[i * d + j]] |= (conn[j] - '0');    
        }

        for (j = 0 ; j < d; ++j) {
            wt[cmpid[i * d + j]] += dp[cmpid[i * d + j]];
            dp[cmpid[i * d + j]] = 0;
        }
    }

    memset(dp, -1, sizeof(dp));
    dfs(cmpid[0]);
    printf("%d\n", dp[0]);
    return 0;
}