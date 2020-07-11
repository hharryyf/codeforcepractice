#include <bits/stdc++.h>
#define MAX_SIZE 200111
using namespace std;

vector<int> g[MAX_SIZE];
// there are 2 types of constraints
// 1. b->a
// 2. a is true, b is false
// this is equivalent to (a or a) and (not b or not b)
// hence we add edges between not a->a, b->not b.
int id[MAX_SIZE], low[MAX_SIZE];
int instack[MAX_SIZE], visited[MAX_SIZE];
stack<int> st;
int cnt = 0;
int cid = 1;
vector<int> word[MAX_SIZE];
set<int> cg[MAX_SIZE];

void tarjan(int v) {
    st.push(v);
    low[v] = visited[v] = ++cnt;
    instack[v] = 1;
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
            id[st.top()] = cid;
            st.pop();
        }

        instack[st.top()] = 0;
        id[st.top()] = cid++;
        st.pop();
    }
}

int T(int x) {
    return x * 2 - 1;
}

int F(int x) {
    return x * 2;
}

void addedge(int from, int to) {
    g[from].push_back(to);
}

vector<int> ret;
int ord[MAX_SIZE];

void dfs(int v) {
    visited[v] = 1;
    for (auto nv : cg[v]) {
        if (!visited[nv]) {
            dfs(nv);
        }
    }

    ret.push_back(v);
}

int main() {
    int n, m, i, j;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i) {
        int v;
        scanf("%d", &v);
        while (v-- > 0) {
            int w;
            scanf("%d", &w);
            word[i].push_back(w);
        }
    }

    for (i = 1; i < n; ++i) {
        int pos = -1;
        int sz = min((int) word[i].size(), (int) word[i+1].size());
        for (j = 0 ; j < sz; ++j) {
            if (word[i][j] > word[i+1][j]) {
                // here is the case we must swap word[i][j] and not sawp word[i+1][j]
                addedge(F(word[i][j]), T(word[i][j]));
                addedge(T(word[i+1][j]), F(word[i+1][j]));
                pos = j;
                break;
            } else if (word[i][j] < word[i+1][j]) {
                addedge(T(word[i+1][j]), T(word[i][j]));
                addedge(F(word[i][j]), F(word[i+1][j]));
                pos = j;
                break;
            }
        } 

        if (pos == -1 && word[i].size() > word[i+1].size()) {
            printf("No\n");
            return 0;
        }      
    }

    for (i = 1; i <= 2 * m; ++i) {
        if (!visited[i]) {
            tarjan(i);
        }
    }

    for (i = 1; i <= m; ++i) {
        if (id[T(i)] == id[F(i)]) {
            // cout << "scc " << i << " ! " << endl;
            printf("No\n");
            return 0;
        }
    }

    printf("Yes\n");

    for (i = 1; i <= 2 * m; ++i) {
        for (auto v : g[i]) {
            if (id[i] != id[v]) {
                cg[id[i]].insert(id[v]);
            }
        }
    }

    memset(visited, 0, sizeof(visited));
    for (i = 1; i < cid; ++i) {
        if (!visited[i]) {
            dfs(i);
        }
    }
    
    reverse(ret.begin(), ret.end());
    for (i = 0 ; i < (int) ret.size(); ++i) {
        ord[ret[i]] = i;
    }

    ret.clear();
    for (i = 1; i <= m; ++i) {
        if (ord[id[T(i)]] > ord[id[F(i)]]) {
            ret.push_back(i);
        }
    }

    printf("%d\n", (int) ret.size());
    for (auto v : ret) {
        printf("%d ", v);
    }
    printf("\n");
    return 0;
}