#include <bits/stdc++.h>
#define MAX_SIZE 5111
using namespace std;

struct edge {
    char st[4];
    int to;
};

vector<edge> g[MAX_SIZE];
int active[MAX_SIZE];
int f[MAX_SIZE];
int outdeg[MAX_SIZE], indeg[MAX_SIZE];

int find(int x) {
    if (x == f[x]) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int a = find(x), b = find(y);
    f[a] = b;
}

int encode(char ch) {
    if (ch >= 'A' && ch <= 'Z') return ch - 'A';
    if (ch >= 'a' && ch <= 'z') return ch - 'a' + 26;
    return ch - '0' + 52;
}

// add an edge, and do set union
void addedge(char st[]) {
    int v1 = encode(st[0]) * 62 + encode(st[1]);
    int v2 = encode(st[1]) * 62 + encode(st[2]);
    active[v1] = active[v2] = 1;
    unionset(v1, v2);
    edge e;
    sscanf(st, "%s", e.st);
    e.to = v2;
    g[v1].push_back(e);
    outdeg[v1]++, indeg[v2]++;
}

char st[4];
vector<string> ret;

void euler(int v) {
    while (!g[v].empty()) {
        auto e = g[v].back();
        g[v].pop_back();
        euler(e.to);
        ret.push_back(string(e.st));
    }
}

int main() {
    int n, i;
    scanf("%d", &n);
    for (i = 0 ; i < MAX_SIZE; ++i) f[i] = i;

    for (i = 1; i <= n; ++i) {
        scanf("%s", st);
        addedge(st);
    }

    int p = -1;
    for (i = 0 ; i < MAX_SIZE; ++i) {
        if (active[i]) {
            if (p == -1) {
                p = find(i);
            } else if (p != find(i)) {
                printf("NO\n");
                return 0;
            }
        }
    }

    int cnt = 0;
    for (i = 0 ; i < MAX_SIZE; ++i) {
        if (abs(outdeg[i] - indeg[i]) > 1) {
            printf("NO\n");
            return 0;
        }

        if (abs(outdeg[i] - indeg[i]) == 1) {
            cnt++;
            if (outdeg[i] > indeg[i]) {
                p = i;
            }
        }
    }

    if (cnt > 2) {
        printf("NO\n");
        return 0;
    }

    euler(p);

    reverse(ret.begin(), ret.end());
    printf("YES\n");
    for (i = 0 ; i < (int) ret.size(); ++i) {
        if (i == 0) {
            printf("%s", ret[i].data());
        } else {
            printf("%c", ret[i][2]);
        }
    }

    printf("\n");
    return 0;
}