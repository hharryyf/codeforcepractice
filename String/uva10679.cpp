#include <bits/stdc++.h>
using namespace std;

const int N = 1000111;
const int M = 1011;
int ans[M];

struct AC {
    const int alphabet = 52;
    int tr[N][53];
    int cnt;
    int e[N], fail[N];
    void init() {
        memset(tr, 0, sizeof(tr));
        memset(e, 0, sizeof(e));
        memset(fail,0,sizeof(fail));
        cnt = 0;
    }

    int idx(char ch) {
        if (ch <= 'Z') return ch - 'A' + 26;
        return ch - 'a';
    }

    void insert(char s[], int id) {
        int p = 0, i, len = strlen(s);
        for(i = 0; i < len; ++i) {
            int k= idx(s[i]);
            if (!tr[p][k]) {
                tr[p][k] = ++cnt;
            }
            p = tr[p][k];
        }
        ans[id] = p;
        e[p]++;
    }

    void build() {
        queue<int>q;
        int i;
        for(i = 0; i < alphabet; ++i) {
            if (tr[0][i]) {
                q.push(tr[0][i]);
            }
        }

        while(!q.empty()) {
            int k = q.front();
            q.pop();
            for (i = 0; i < alphabet; ++i) {
                if (tr[k][i]) {
                    fail[tr[k][i]] = tr[fail[k]][i];
                    q.push(tr[k][i]);
                } else {
                    tr[k][i]=tr[fail[k]][i];
                }
            }
        }
    }
};

AC ac;
char pt[N];
char s[M];
bool visited[M];

int main() {
    int T, n, i;
    scanf("%d", &T);
    while (T-- > 0) {
        memset(visited, 0, sizeof(visited));
        memset(ans, 0, sizeof(ans));
        scanf("%s", pt);
        scanf("%d", &n);
        ac.init();
        for (i = 1; i <= n; ++i) {
            scanf("%s", s);
            ac.insert(s, i);
        }

        ac.build();
        int p = 0, j, len = strlen(pt);
        for (i = 0 ; i < len; ++i) {
            p = ac.tr[p][ac.idx(pt[i])];
            for (j = p; j != 0 && ~ac.e[j]; j = ac.fail[j]) {
                visited[j] = true;
                ac.e[j] = -1;
            }
        }

        for (i = 1; i <= n; ++i) {
            if (visited[ans[i]]) {
                printf("y\n");
            } else {
                printf("n\n");
            }
        }
    }
    return 0;
}