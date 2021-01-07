#include <bits/stdc++.h>
#define MAX_SIZE 29
using namespace std;

set<int> g[MAX_SIZE];
int instack[MAX_SIZE];
int dp[MAX_SIZE], visited[MAX_SIZE], nxt[MAX_SIZE];
stack<int> st;
bool flag = false;
int N;
char s[4];
vector<int> cycle;

void init() {
    int i, j;
    flag = false;
    cycle.clear();
    while (!st.empty()) st.pop();
    for (i = 0 ; i <= 26; ++i) {
        g[i].clear();
        dp[i] = instack[i] = visited[i] = nxt[i] = 0;
    }

    for (i = 1; i <= 26; ++i) {
        for (j = 1; j <= 26; ++j) {
            g[i].insert(j);
        }
    }

}

void dfs(int v) {
    if (flag) return;
    visited[v] = 1;
    st.push(v);
    instack[v] = 1;
    for (auto nv : g[v]) {
        if (instack[nv] && !flag) {
            flag = true;
            while (st.top() != nv) {
                instack[st.top()] = 0;
                cycle.push_back(st.top());
                st.pop();
            }
            cycle.push_back(st.top());
            instack[st.top()] = 0;
            st.pop();
            reverse(cycle.begin(), cycle.end());
        }
    }
    
    for (auto nv : g[v]) {
        if (!visited[nv]) {
            dfs(nv);
        }
    }
    if (!st.empty()) {
        st.pop();
    }
    instack[v] = 0;
}

void dfs2(int v) {
    if (dp[v] != 0) return;
    for (auto nv : g[v]) {
        dfs2(nv);
        if (dp[v] < dp[nv] + 1) {
            nxt[v] = nv;
            dp[v] = dp[nv] + 1;
        }
    }
    if (g[v].empty()) dp[v] = 1;
}

int main() {
    int T, i, j;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d", &N);
        init();
        for (i = 0 ; i < N; ++i) {
            scanf("%s", s);
            g[s[0] - 'a' + 1].erase(s[1] - 'a' + 1);
        }
        
        for (i = 1; i <= 26; ++i) {
            if (!visited[i]) {
                dfs(i);
            }
        }

        // cout << st.size() << endl;
        if (!flag) {
            for (i = 1; i <= 26; ++i) visited[i] = 0;
            for (i = 1; i <= 26; ++i) {
                if (!visited[i]) {
                    dfs2(i);
                }
            }
        }

        if (flag) {
            int sz = cycle.size();
            for (i = 0; i < 20; ++i) {
                for (j = 0 ; j < 20; ++j) {
                    printf("%c", 'a' + cycle[(i + j) % sz] - 1);
                }
                printf("\n");
            }
        } else {
            int sz = 0, idx = 0;
            for (i = 1; i <= 26; ++i) {
                if (sz == 0 || dp[sz] <= dp[i]) sz = i;
            }
            idx = sz;
            sz = (dp[idx] + 1) / 2;
            vector<int> path;
            int curr = idx;
            while (curr != 0) {
                path.push_back(curr);
                curr = nxt[curr];
            }
            for (i = 0; i < sz; ++i) {
                for (j = 0 ; j < sz; ++j) {
                    printf("%c", 'a' + path[i+j] - 1);
                }
                printf("\n");
            }
        }
    }
    return 0;
}