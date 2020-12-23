#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

vector<int> g[MAX_SIZE];
int cmpid[MAX_SIZE], low[MAX_SIZE], visited[MAX_SIZE], instack[MAX_SIZE];
stack<int> st;
int cnt, N, cid = 1;

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

int pos(int x) {
    return x * 2;
}

int neg(int x) {
    return x * 2 + 1;
}

int a, b;
int p[MAX_SIZE];
map<int, int> mp;

int main() {
    int i;
    scanf("%d%d%d", &N, &a, &b);
    for (i = 0; i < N; ++i) {
        scanf("%d", &p[i]);
        mp[p[i]] = i;    
    }

    for (i = 0; i < N; ++i) {
        if (mp.find(a - p[i]) != mp.end()) {
            g[pos(i)].push_back(pos(mp[a - p[i]]));
            g[neg(i)].push_back(neg(mp[a - p[i]]));
        } else {
            g[pos(i)].push_back(neg(i));
        }

        if (mp.find(b - p[i]) != mp.end()) {
            g[neg(i)].push_back(neg(mp[b - p[i]]));
            g[pos(i)].push_back(pos(mp[b - p[i]]));
        } else {
            g[neg(i)].push_back(pos(i));
        }
    }

    for (i = 0; i < 2 * N; ++i) {
        if (!visited[i]) {
            tarjan(i);
        }
    }

    for (i = 0; i < N; ++i) {
        if (cmpid[pos(i)] == cmpid[neg(i)]) {
            printf("NO\n");
            return 0;
        }
    }

    printf("YES\n");
    for (i = 0; i < N; ++i) {
        if (cmpid[pos(i)] < cmpid[neg(i)]) {
            printf("0 ");
        } else {
            printf("1 ");
        }
    }
    printf("\n");
    return 0;
}