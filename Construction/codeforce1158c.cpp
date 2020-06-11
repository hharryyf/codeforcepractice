#include <bits/stdc++.h>
#define MAX_SIZE 500011
using namespace std;

vector<int> g[MAX_SIZE];
int deg[MAX_SIZE];
int nxt[MAX_SIZE];
int visited[MAX_SIZE];
set<int> leave;
int n;
int ans[MAX_SIZE];
vector<int> ret;

void init() {
    int i;
    leave.clear();
    scanf("%d", &n);
    for (i = 0; i <= n + 1; ++i) {
        deg[i] = 0;
        visited[i] = 0;
        g[i].clear();
        nxt[i] = 0;
    }

    for (i = 1; i <= n; ++i) {
        scanf("%d", &nxt[i]);
    }

    ret.clear();
}

void addedge(int v1, int v2) {
    g[v1].push_back(v2);
    deg[v2]++;
    // cout << "addedge " << v1 << " " << v2 << endl;
}

void dfs(int v) {
    visited[v] = 1;
    for (auto nv : g[v]) {
        if (!visited[nv]) {
            dfs(nv);
        }
    }

    ret.push_back(v);
}

int main() {
    int T, i;
    scanf("%d", &T);
    while (T-- > 0) {
        init();
        bool valid = true;
        for (i = 1; i <= n; ++i) {

            if (!leave.empty() && *leave.begin() == i) {
                leave.erase(i);
            } 
            
            if (!leave.empty() && nxt[i] != -1 && *leave.begin() < nxt[i]) {
                valid = false;
                break;
            }

            if (nxt[i] != -1) {
                leave.insert(nxt[i]);
            }
        }        

        if (!valid) {
            printf("-1\n");
            continue;
        }

        set<pair<int, int>> rt;
        multiset<int> lft;
        for (i = 1; i <= n + 1; ++i) {
            if (i > 1) {
                if (!rt.empty() && rt.begin()->first == i) {
                    while (!rt.empty() && rt.begin()->first == i) {
                        lft.erase(lft.find(rt.begin()->second));
                        rt.erase(rt.begin());
                    }

                    if (!lft.empty()) {
                        addedge(*lft.rbegin(), i);     
                    }

                } else {
                    addedge(i - 1, i);
                }
            }

            if (nxt[i] > 0) {
                rt.insert(make_pair(nxt[i], i));
                lft.insert(i);
                addedge(nxt[i], i);
            }
        }

        for (i = n + 1; i >= 1; --i) {
            if (deg[i] == 0) {
                dfs(i);
            }
        }

        // reverse(ret.begin(), ret.end());
        int tol = 1;
        for (i = 0; i <= n; ++i) {
            if (ret[i] != n + 1) {
                ans[ret[i]] = tol++;
            }
        }

        for (i = 1; i <= n; ++i) {
            printf("%d ", ans[i]);
        }
        printf("\n");
    }
    return 0;
}