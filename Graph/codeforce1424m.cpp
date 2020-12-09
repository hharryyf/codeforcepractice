#include <bits/stdc++.h>

using namespace std;
char st[1000011][102];
int visited[26], ok[26];
int add[26][26];
int cycle = 0;
vector<int> ret;

void dfs(int v) {
    visited[v] = 1;
    int i;
    for (i = 0 ; i < 26; ++i) {
        if (add[v][i] && visited[i] == 1) {
            cycle = 1;
        }

        if (add[v][i] && visited[i] == 0) {
            dfs(i);
        }
    }
    visited[v] = 2;
    ret.push_back(v);
}

int main() {
    int i, j, n, k;
    scanf("%d%d", &n, &k);
    for (i = 0 ; i < n; ++i) {
        int p;
        scanf("%d", &p);
        for (j = 0 ; j < k; ++j) {
            scanf("%s", st[p * n + j]);
        }
    }

    for (i = 0 ; i < n * k; ++i) {
        int len = strlen(st[i]);
        for (j = 0 ; j < len; ++j) {
            ok[st[i][j] - 'a'] = 1;
        }
    }

    for (i = 0 ; i < n * k - 1; ++i) {
        int l1 = strlen(st[i]), l2 = strlen(st[i+1]), len = min(l1, l2);
        bool valid = false;
        for (j = 0 ; j < len; ++j) {
            if (st[i][j] != st[i+1][j]) {
                valid = true;
                add[st[i][j] - 'a'][st[i+1][j] - 'a'] = 1;
                break;
            }
        }

        if (l1 > l2 && !valid) {
            printf("IMPOSSIBLE\n");
            return 0;
        }
    }

    for (i = 0 ; i < 26; ++i) {
        if (ok[i] && !visited[i]) {
            dfs(i);
        }
    }

    if (cycle == 1) {
        printf("IMPOSSIBLE\n");
        return 0;
    }

    reverse(ret.begin(), ret.end());
    for (auto v : ret) {
        printf("%c", 'a' + v);
    }
    return 0;
}