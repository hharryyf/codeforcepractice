#include <bits/stdc++.h>
#define MAX_SIZE 1011
using namespace std;

struct edge {
    int from, to, cost;
};

// bridge[i] refers to whether the ith edge is a bridge
int bridge[MAX_SIZE * 30];
vector<pair<int, int>> g[MAX_SIZE];
vector<pair<int, int>> gi[MAX_SIZE];

int cmpid[MAX_SIZE];
int instack[MAX_SIZE];
stack<int> st;
int low[MAX_SIZE];
int visited[MAX_SIZE];
int cnt = 0;
edge edg[MAX_SIZE * 30];
// cg stands for compressed graph
unordered_set<int> cg[MAX_SIZE];
int useful[MAX_SIZE];

void init() {
    memset(visited, 0, sizeof(visited));
    memset(low, 0, sizeof(low));
    memset(instack, 0, sizeof(instack));
    memset(useful, 0, sizeof(useful));
    while (!st.empty()) st.pop();
    cnt = 0;
}

struct record {
    int ans = 2e9 + 7;
    int ed1 = 0, ed2 = 0;
    void update(int e1, int e2=0) {
        if (edg[e1].cost + edg[e2].cost < ans) {
            ans = edg[e1].cost + edg[e2].cost;
            ed1 = e1, ed2 = e2;
        }
    }
};

record rc;

void tarjan(int v, int pid) {
    low[v] = visited[v] = ++cnt;
    st.push(v);
    instack[v] = 1;
    for (auto np : gi[v]) {
        int nv = np.first, id = np.second;
        if (id == pid) continue;
        if (!visited[nv]) {
            tarjan(nv, id);
            low[v] = min(low[v], low[nv]);
            if (visited[v] < low[nv]) {
                bridge[id] = 1;
            }
        } else if (instack[nv]) {
            low[v] = min(low[v], visited[nv]);
        }
    }

    if (low[v] == visited[v]) {
        while (st.top() != v) {
            cmpid[st.top()] = v;
            instack[st.top()] = 0;
            st.pop();
        }

        instack[st.top()] = 0;
        cmpid[st.top()] = v;
        st.pop();
    }
}

void dfs(int v, int pre, int target) {
    // cout << v << endl;
    if (v == target) {
        useful[v] = 1;
        return;
    }

    for (auto nv : cg[v]) {
        if (nv != pre) {
            dfs(nv, v, target);
            useful[v] |= useful[nv];
        }
    }
}

void bridge_finding(int v, int pid, int ban, int &id, int target) {
    low[v] = visited[v] = ++cnt;
    if (v == target) useful[target] = 1;
    vector<int> bri;
    for (auto np : g[v]) {
        int nv = np.first, eid = np.second;
        if (eid == pid || eid == ban) continue;
        if (!visited[nv]) {
            bridge_finding(nv, eid, ban, id, target);
            low[v] = min(low[v], low[nv]);
            if (visited[v] < low[nv]) {
                bri.push_back(eid);
            }
            useful[v] |= useful[nv];
        } else {
            low[v] = min(low[v], visited[nv]);
        }
    }

    for (auto b : bri) {
        if (useful[edg[b].from] && useful[edg[b].to]) {
            if (id == 0 || edg[b].cost < edg[id].cost) {
                id = b;
                // cout << ban << " ** " << id << endl;
            }
        }
    }
}

int pre[MAX_SIZE], lst[MAX_SIZE];

int main() {
    int s, t, n, m, i;
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for (i = 1; i <= m; ++i) {
        scanf("%d%d%d", &edg[i].from, &edg[i].to, &edg[i].cost);
        if (edg[i].from != edg[i].to) {
            gi[edg[i].from].emplace_back(edg[i].to, i);
            gi[edg[i].to].emplace_back(edg[i].from, i);
        }
    }

    tarjan(s, 0);
    if (!visited[t]) {
        printf("0\n0\n");
        return 0;
    }
    
    for (i = 1; i <= m; ++i) {
        if (edg[i].from != edg[i].to && visited[edg[i].from] && visited[edg[i].to]) {
            int v1 = cmpid[edg[i].from], v2 = cmpid[edg[i].to];
            if (v1 == v2) continue;
            cg[v1].insert(v2);
            cg[v2].insert(v1);
            // cout << "Add " << v1 << " " << v2 << endl;
        }
    }

    
    dfs(s, 0, cmpid[t]);

    for (i = 1; i <= m; ++i) {
        if (edg[i].from != edg[i].to) {
            int c1 = cmpid[edg[i].from], c2 = cmpid[edg[i].to];
            if (useful[c1] && useful[c2]) {
                g[edg[i].from].emplace_back(edg[i].to, i);
                g[edg[i].to].emplace_back(edg[i].from, i);
                // cout << "Add " << edg[i].from << " " << edg[i].to << endl;
            }
        }
    }
    
    queue<int> q;
    q.push(s);
    init();
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (visited[v]) continue;
        if (v == t) break;
        visited[v] = 1;
        for (auto np : g[v]) {
            int nv = np.first, id = np.second;
            if (!visited[nv]) {
                pre[nv] = v;
                lst[nv] = id;
                q.push(nv);
            }
        }
    }   

    vector<int> candidate;
    int v = t;
    while (v != s) {
        candidate.push_back(lst[v]);
        // cout << "eid= " << lst[v] << endl;
        v = pre[v];
    }
    
    for (auto e : candidate) {
        if (bridge[e]) {
            rc.update(e);
        } else {
            int id = 0;
            init();
            bridge_finding(s, 0, e, id, t);
            if (id != 0) {
                rc.update(e, id);
            }
        }
    }

    if (rc.ans > 2e9) {
        printf("-1\n");
        return 0;
    }

    printf("%d\n", rc.ans);
    if (rc.ed2 == 0) {
        printf("1\n%d\n", rc.ed1);
    } else {
        printf("2\n%d %d\n", rc.ed1, rc.ed2);
    }
    return 0;
}