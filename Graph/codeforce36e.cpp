#include <bits/stdc++.h>
#define MAX_SIZE 10011
using namespace std;

set<pair<int, int>> g[MAX_SIZE];
// active nodes
int active[MAX_SIZE];
// used for union-find
int f[MAX_SIZE];

int find(int x) {
    if (x == f[x]) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int a = find(x), b = find(y);
    f[a] = b;
}

void euler(int v, vector<int> &ret) {
    while (!g[v].empty()) {
        auto p = *g[v].begin();
        g[v].erase(p);
        g[p.first].erase(make_pair(v, p.second));
        euler(p.first, ret);
        ret.push_back(p.second);
    }
}

void print(vector<int> &vc) {
    printf("%d\n", (int) vc.size());
    for (auto v : vc) {
        printf("%d ", v);
    }
    printf("\n");
}

int main() {
    int m, i;
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%d", &m);
    // only 1 edge, no solution
    if (m == 1) {
        printf("-1\n");
        return 0;
    }

    for (i = 0 ; i < MAX_SIZE; ++i) {
        f[i] = i;
    }

    // the only added edge is assigned to have id = m + 1
    for (i = 1; i <= m; ++i) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        g[v1].insert(make_pair(v2, i));
        g[v2].insert(make_pair(v1, i));
        active[v1] = active[v2] = 1;
        unionset(v1, v2);
    }

    unordered_set<int> st;
    for (i = 1; i <= 10000; ++i) {
        if (active[i] == 1) {
            st.insert(find(i));
        }
    }
    // if there are more than 2 connected components, no solution
    if ((int) st.size() > 2) {
        printf("-1\n");
        return 0;
    }

    // only 1 connected component
    if ((int) st.size() == 1) {
        // here it is a bit complecated, 0/2/4 odd number
        // of edges all works
        int odd = 0;
        // record any node in the graph
        int pos = 0;
        vector<int> nd, ans1, ans2;
        for (i = 1; i <= 10000; ++i) {
            if (active[i] == 1) {
                if ((int) g[i].size() % 2 == 1) {
                    odd++;
                    nd.push_back(i);
                }
                // if there are more than 4 odd degree nodes
                // there's no solution
                if (odd > 4) {
                    printf("-1\n");
                    return 0;
                }
                pos = i;
            }
        }

        
        vector<int> ret;
        bool flag = false;
        if ((int) nd.size() > 4) {
            printf("-1\n");
            return 0;
        }

        if ((int) nd.size() == 4) {
            g[nd[0]].insert(make_pair(nd[1], m + 1));
            g[nd[1]].insert(make_pair(nd[0], m + 1));
            euler(nd[2], ret);
            for (i = 0 ; i < (int) ret.size(); ++i) {
                if (ret[i] == m + 1) {
                    flag = true;
                } else {
                    if (flag) {
                        ans1.push_back(ret[i]);
                    } else {
                        ans2.push_back(ret[i]);
                    }
                }
            }
        }
        // there's an euler path, walk from nd[0]/nd[1]
        if ((int) nd.size() == 2) {
            euler(nd[0], ret);
            ans1.push_back(ret[0]);
            for (i = 1; i < (int) ret.size(); ++i) {
                ans2.push_back(ret[i]);
            }
        } 
        // there's an euler cycle, simply walk from pos
        if (nd.empty()) {
            euler(pos, ret);
            ans1.push_back(ret[0]);
            for (i = 1; i < (int) ret.size(); ++i) {
                ans2.push_back(ret[i]);
            }
        }

        print(ans1);
        print(ans2);
    } else {
        // 2 connected components
        vector<int> ret;
        int cnt[2] = {0, 0};
        // the starting nodes, must be odd nodes/ret[0],ret[1]
        int nd[2][2] = {{0,0},{0,0}};
        for (auto v : st) {
            ret.push_back(v);
        }

        for (i = 1; i <= 10000; ++i) {
            if ((int) g[i].size() % 2 == 1) {
                if (find(i) == find(ret[0])) {
                    cnt[0]++;
                    if (nd[0][0] == 0) {
                        nd[0][0] = i;
                    } else {
                        nd[0][1] = i;
                    }
                } else if (find(i) == find(ret[1])) {
                    cnt[1]++;
                    if (nd[1][0] == 0) {
                        nd[1][0] = i;
                    } else {
                        nd[1][1] = i;
                    }
                }
            }
        }

        // if the connected components is equal to 2
        // if there's a component does not have an euler
        // path, no solution exists
        if (cnt[0] > 2 || cnt[1] > 2) {
            printf("-1\n");
            return 0;
        }

        vector<int> ans1, ans2;
        if (cnt[0] != 0) {
            euler(nd[0][0], ans1);
        } else {
            euler(ret[0], ans1);
        }

        if (cnt[1] != 0) {
            euler(nd[1][0], ans2);
        } else {
            euler(ret[1], ans2);
        }

        print(ans1);
        print(ans2);
    }
    return 0;
}