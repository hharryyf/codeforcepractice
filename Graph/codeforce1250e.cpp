#include <bits/stdc++.h>
#define MAX_SIZE 58
using namespace std;

char st[MAX_SIZE][MAX_SIZE];
vector<pair<int, int>> g[MAX_SIZE];
int visited[MAX_SIZE];
// here we store things in a group of 2
vector<int> part[MAX_SIZE][2];
int tol = 0;
int m;
bool valid = true;

void dfs(int v) {
    for (auto np : g[v]) {
        int nv = np.first, tp = np.second;
        if (visited[nv] == -1) {
            if (tp == 0) {
                visited[nv] = visited[v];
                part[tol][visited[v]].push_back(nv);
                dfs(nv);
            } else {
                visited[nv] = 1 ^ visited[v];
                part[tol][visited[nv]].push_back(nv);
                dfs(nv);
            }
        } else {
            if (tp == 0 && visited[nv] != visited[v]) {
                valid = false;
            }

            if (tp == 1 && visited[nv] == visited[v]) {
                valid = false;
            }
        }
    }
}

void init() {
    int i;
    valid = true;
    tol = 0;
    for (i = 0 ; i < MAX_SIZE; ++i) {
        part[i][0].clear();
        part[i][1].clear();
        g[i].clear();
        visited[i] = -1;
    }
}

pair<int, int> sim(int id1, int id2) {
    int i;
    pair<int, int> p = make_pair(0, 0);
    for (i = 0 ; i < m; ++i) {
        p.first += (st[id1][i] == st[id2][i]);
        p.second += (st[id1][i] == st[id2][m - i - 1]);
    }

    return p;
}

int main() {
    int n, k, T, i, j;
    scanf("%d", &T);
    while (T-- > 0) {
        init();
        scanf("%d%d%d", &n, &m, &k);
        for (i = 1; i <= n; ++i) {
            scanf("%s", st[i]);
        }

        for (i = 1; i <= n; ++i) {
            for (j = i + 1; j <= n; ++j) {
                pair<int, int> p = sim(i, j);
                if (p.first < k && p.second < k) {
                    valid = false;
                    break;
                }

                if (p.first < k && p.second >= k) {
                    g[i].emplace_back(j, 1);
                    g[j].emplace_back(i, 1);
                } else if (p.first >= k && p.second < k) {
                    g[i].emplace_back(j, 0);
                    g[j].emplace_back(i, 0);
                }
            }

            if (!valid) {
                break;
            }
        }

        if (!valid) {
            printf("-1\n");
            continue;
        }

        for (i = 1; i <= n; ++i) {
            if (visited[i] == -1) {
                part[tol][0].push_back(i);
                visited[i] = 0;
                dfs(i);
                tol++;
            }
        }
        
        if (!valid) {
            printf("-1\n");
            continue;
        }

        vector<int> ans;
        for (i = 0 ; i < tol; ++i) {
            if (part[i][0].size() < part[i][1].size()) {
                for (auto p : part[i][0]) {
                    ans.push_back(p);
                }
            } else {
                for (auto p : part[i][1]) {
                    ans.push_back(p);
                }
            }
        }

        printf("%d\n", (int) ans.size());
        for (auto v : ans) {
            printf("%d ", v);
        }
        printf("\n");
    }
    return 0;
}