#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 1000011
using namespace std;

int child[MAX_SIZE][26];
char st[MAX_SIZE];
vector<int> v[MAX_SIZE][2];
bool visited[MAX_SIZE >> 3][2];
int cnt = 0;
int ans = 0;
vector<pair<int, int>> ret;

void insert(char *a, int id, int dim) {
	int sz = strlen(a);
	int i = 0, rt = 0;
    while (i < sz) {
        if (child[rt][a[i] - 'a'] == 0) child[rt][a[i] - 'a'] = ++cnt;
        v[child[rt][a[i] - 'a']][dim].push_back(id);
        rt = child[rt][a[i] - 'a'];
        ++i;
    }
}


void dfs(int rt, int dep) {
    int i;
    for (i = 0 ; i < 26; ++i) {
        if (child[rt][i] != 0) {
            dfs(child[rt][i], dep + 1);
        }
    }

    for (auto p : v[rt][0]) {
        if (visited[p][0]) continue;
        for(auto q : v[rt][1]) {
            if (visited[q][1]) continue;
            ret.emplace_back(p, q);
            visited[p][0] = visited[q][1] = 1;
            ans += dep;
            break;
        }
    }
}

int main() {
    int N, i;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%s", st);
        insert(st, i, 0);
        v[0][0].push_back(i);
    }

    for (i = 1; i <= N; ++i) {
        scanf("%s", st);
        insert(st, i, 1);
        v[0][1].push_back(i);
    }


    dfs(0, 0);

    printf("%d\n", ans);
    for (auto p : ret) {
        printf("%d %d\n", p.first, p.second);
    }
    return 0;
}