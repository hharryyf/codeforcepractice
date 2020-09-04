#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#define MAX_SIZE 1011111
using namespace std;

vector<int> pos[MAX_SIZE][2];
vector<int> g[MAX_SIZE];
set<pair<int, int>> ss;
int N;
int dp[MAX_SIZE][2], visited[MAX_SIZE];

struct Trie {
    int child[MAX_SIZE][26];
    int cnt = 0;
    void init() {
        ss.clear();
        for (int i = 0; i <= N + 1; ++i) {
            pos[i][0].clear();
            pos[i][1].clear();
        }

        for (int i = 0 ; i <= cnt; ++i) g[i].clear();
        cnt = 0;
        clear();
    }
    void insert(char st[], int id) {
        int n = strlen(st), i = 0, rt = 0;
        while (i < n) {
            if (child[rt][st[i] - 'a'] == 0) {
                child[rt][st[i] - 'a'] = ++cnt;
            }

            rt = child[rt][st[i++] - 'a'];
            pos[id][0].push_back(rt);
        }
    }

    void mark(const char st[], int id) {
        int i = 1, rt = 0, n = strlen(st);
        // cout << "mark " << st << " " << id << endl;
        while (i <= n) {
            pos[id][1].push_back(rt);
            if (i < n && child[rt][st[i] - 'a'] != 0) {
                rt = child[rt][st[i++] - 'a'];
            } else {
                break;
            }
        }
    }

    void build() {
        int i, j;
        for (i = 1; i <= N; ++i) {
            int sz = min(pos[i][0].size(), pos[i][1].size());
            for (j = 0 ; j < sz; ++j) {
                if (pos[i][0][j] != 0 && pos[i][1][j] != 0) {
                    if (pos[i][0][j] > pos[i][1][j]) {
                        swap(pos[i][0][j], pos[i][1][j]);
                    }
                    if (pos[i][0][j] == pos[i][1][j]) continue;
                    if (ss.count(make_pair(pos[i][0][j], pos[i][1][j]))) continue;
                    ss.insert(make_pair(pos[i][0][j], pos[i][1][j]));
                    g[pos[i][0][j]].push_back(pos[i][1][j]);
                    g[pos[i][1][j]].push_back(pos[i][0][j]);
                    // cout << "Addedge " << pos[i][0][j] << " " << pos[i][1][j] << endl;
                }
            }
        }
    }

    void clear(int rt=0) {
        int i;
        for (i = 0 ; i < 26; ++i) {
            if (child[rt][i] != 0) {
                clear(child[rt][i]);
                child[rt][i] = 0;
            }
        }
    }

    void dfs(int v) {
        visited[v] = 1;
        dp[v][0] = 1, dp[v][1] = 0;
        for (auto nv : g[v]) {
            if (!visited[nv]) {
                dfs(nv);
                dp[v][0] = dp[v][0] + dp[nv][1];
                dp[v][1] = dp[v][1] + max(dp[nv][0], dp[nv][1]);
            }
        }
    }

    int solve() {
        int i, ans = 0;
        for (i = 1; i <= cnt; ++i) {
            visited[i] = 0;
        }

        for (i = 1; i <= cnt; ++i) {
            if (!visited[i]) {
                dfs(i);
                ans += max(dp[i][0], dp[i][1]);
            }
        }

        return ans;
    }
};

Trie t;
char st[MAX_SIZE];
string s[MAX_SIZE];


int main() {
    int i;
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d", &N);
        t.init();
        for (i = 1; i <= N; ++i) {
            scanf("%s", st);
            s[i] = st;
            t.insert(st, i);
        } 

        for (i = 1; i <= N; ++i) {
            t.mark(s[i].c_str(), i);    
        }

        t.build();

        printf("%d\n", t.solve());
    }
    return 0;
}