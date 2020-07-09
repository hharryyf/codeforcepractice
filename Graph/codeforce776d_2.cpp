#include <bits/stdc++.h>
#define MAX_SIZE 200111
using namespace std;
/*
    There are 3 ways of solving this problem, union-find and dfs coloring are old and well-known tricks.
    Here I implemented the 2-sat approach. Quite interesting.
*/
vector<int> g[MAX_SIZE];
int visited[MAX_SIZE], low[MAX_SIZE];
int instack[MAX_SIZE];
stack<int> st;
int id[MAX_SIZE];
int cnt = 0;
int n, m;
int a[MAX_SIZE];
pair<int, int> cl[MAX_SIZE];

int T(int x) {
    return x * 2 - 1;
}

int F(int x) {
    return x * 2;
}

void tarjan(int v) {
    low[v] = visited[v] = ++cnt;
    st.push(v);
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
            id[st.top()] = v;
            instack[st.top()] = 0;
            st.pop();
        }

        id[st.top()] = v;
        instack[st.top()] = 0;
        st.pop();
    }
}

int main() {
    int i;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i) scanf("%d", &a[i]);
    for (i = 1; i <= m; ++i) {
        int v;
        scanf("%d", &v);
        while (v-- > 0) {
            int p;
            scanf("%d", &p);
            if (cl[p].first == 0) {
                cl[p].first = i;
            } else {
                cl[p].second = i;
            }
        }
    }

    for (i = 1; i <= n; ++i) {
        if (a[i] == 0) {
            g[T(cl[i].first)].push_back(F(cl[i].second));
            g[F(cl[i].second)].push_back(T(cl[i].first));
            g[T(cl[i].second)].push_back(F(cl[i].first));
            g[F(cl[i].first)].push_back(T(cl[i].second));
        } else {
            g[T(cl[i].first)].push_back(T(cl[i].second));
            g[T(cl[i].second)].push_back(T(cl[i].first));
            g[F(cl[i].first)].push_back(F(cl[i].second));
            g[F(cl[i].second)].push_back(F(cl[i].first));
        }
    }

    for (i = 1; i <= 2 * m; ++i) {
        if (!visited[i]) {
            tarjan(i);
        }
    }

    for (i = 1; i <= m; ++i) {
        if (id[T(i)] == id[F(i)]) {
            printf("NO\n");
            return 0;
        }
    }

    printf("YES\n");
    return 0;
}