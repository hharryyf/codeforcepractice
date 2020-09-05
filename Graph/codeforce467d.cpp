#include <bits/stdc++.h>
#define MAX_SIZE 500111
using namespace std;
typedef long long ll;
// map for id
map<string, int> mp;
set<pair<int, int>> edg;
int id[MAX_SIZE];
pair<int, int> cost[MAX_SIZE], cst[MAX_SIZE];
char st[MAX_SIZE], pt[MAX_SIZE];
vector<int> g[MAX_SIZE];
set<int> g2[MAX_SIZE];
int cmpid[MAX_SIZE], visited[MAX_SIZE], low[MAX_SIZE];
int cnt = 0;
int curr = 1;
stack<int> stk;
int instack[MAX_SIZE];

int n;

int getid(string &s) {
    for (auto &ch : s) {
        if (ch < 'a') ch += 'a' - 'A';
    }
    auto iter = mp.find(s);
    if (iter == mp.end()) return -1;
    return iter->second;
}

pair<int, int> getcost(string &s) {
    pair<int, int> p = {0,0};
    for (auto &ch : s) {
        if (ch < 'a') ch += 'a' - 'A';
        if (ch == 'r') p.first++;
    }
    p.second = (int) s.size();
    return p;
}

void tarjan(int v) {
    visited[v] = low[v] = ++cnt;
    instack[v] = 1;
    stk.push(v);
    for (auto nv : g[v]) {
        if (!visited[nv]) {
            tarjan(nv);
            low[v] = min(low[v], low[nv]); 
        } else if (instack[nv]) {
            low[v] = min(low[v], visited[nv]);
        }
    }

    if (low[v] == visited[v]) {
        while (stk.top() != v) {
            instack[stk.top()] = 0;
            cmpid[stk.top()] = curr;
            stk.pop();
        }

        instack[stk.top()] = 0;
        cmpid[stk.top()] = curr++;
        stk.pop();
    }
}

void dfs(int v) {
    visited[v] = 1;
    for (auto nv : g2[v]) {
        if (!visited[nv]) {
            dfs(nv);
        }
        cst[v] = min(cst[v], cst[nv]);
    }
}

int main() {
    int i, m;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%s", st);
        string s = string(st);
        int idx = getid(s);
        int sz = mp.size();
        if (idx == -1) {
            mp[s] = sz + 1;
            idx = sz + 1;
        }
        
        id[i] = idx;
        cost[idx] = getcost(s);
    }

    scanf("%d", &m);
    for (i = 0 ; i < m; ++i) {
        scanf("%s%s", st, pt);
        string s = string(st), p = string(pt);
        int v1 = getid(s);
        if (v1 == -1) {
            v1 = mp[s] = (int) mp.size() + 1;
            cost[v1] = getcost(s);
        }
        int v2 = getid(p);
        if (v2 == -1) {
            v2 = mp[p] = (int) mp.size() + 1;
            cost[v2] = getcost(p);
        }

        if (!edg.count(make_pair(v1, v2))) {
            edg.insert(make_pair(v1, v2));
    //        cout << "Addedge " << v1 << " " << v2 << endl;
    //        cout << "cost= " << cost[v1].first << " " << cost[v2].first << endl;
            g[v1].push_back(v2);
        }
    }

    int sz = mp.size();
    for (i = 1; i <= sz; ++i) {
        if (!visited[i]) {
            tarjan(i);
        }
    }

    for (i = 1; i <= sz; ++i) cst[i] = make_pair(2 * MAX_SIZE, 2 * MAX_SIZE);
    for (i = 1; i <= sz; ++i) {
        cst[cmpid[i]] = min(cst[cmpid[i]], cost[i]);
    }
/*
    for (i = 1; i < curr; ++i) {
        cout << cst[i].first << " " << cst[i].second << endl;
    }
*/
    for (i = 1; i <= sz; ++i) {
        for (auto v : g[i]) {
            if (cmpid[v] != cmpid[i]) {
                g2[cmpid[i]].insert(cmpid[v]);
            }
        }
    }   

    memset(visited, 0, sizeof(visited));

    for (i = 1; i < curr; ++i) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    ll rcnt = 0, lcnt = 0;
    for (i = 1; i <= n; ++i) {
        auto p = cst[cmpid[id[i]]];
        rcnt += p.first, lcnt += p.second;
    }

    cout << rcnt << " " << lcnt << endl;
    return 0;
}