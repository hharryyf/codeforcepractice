#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 1111111
using namespace std;

int f[MAX_SIZE];
multiset<pair<int, int>> g[MAX_SIZE];
vector<pair<int, int>> ret;
int a[MAX_SIZE], b[MAX_SIZE];
int deg[MAX_SIZE];
int fac;
int n;

int find(int x) {
    // cout << x << endl;
    if (x == f[x]) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int aa = find(x), bb = find(y);
    f[aa] = bb;
}

void preprocess() {
    int i;
    for (i = 0 ; i < MAX_SIZE; ++i) f[i] = i, deg[i] = 0;
}

void euler(int v) {
    // cout << "enter" << endl;
    while (!g[v].empty()) {
        auto np = *g[v].begin();
        g[np.first].erase(g[np.first].find(make_pair(v, np.second)));
        g[v].erase(g[v].find(make_pair(np.first, np.second)));
        euler(np.first);
        if (np.first == b[np.second] % fac) {
            ret.emplace_back(np.second * 2, np.second * 2 - 1);
        } else {
            ret.emplace_back(np.second * 2 - 1, np.second * 2);
        }
    }
}


int main() {
    int i, n, j;
    scanf("%d", &n);
    for (i = 1 ; i <= n; ++i) {
        scanf("%d%d", &a[i], &b[i]);
    }


    for (j = 20 ; j >= 0; --j) {
        preprocess();
        int curr = -1;
        bool valid = true;
        fac = 1 << j;
        for (i = 1; i <= n; ++i) {
            deg[a[i] % fac]++, deg[b[i] % fac]++;
            unionset(a[i] % fac, b[i] % fac);
        }

        for (i = 0 ; i < fac; ++i) {
            if (deg[i] & 1) {
                valid = false;
                break;
            }

            if (deg[i] > 0) {
                if (curr == -1) curr = find(i);
                if (curr != find(i)) {
                    valid = false;
                    break;
                }
            }
        }

        if (valid) {
            printf("%d\n", j);
            for (i = 1; i <= n; ++i) {
                int v1 = a[i] % fac, v2 = b[i] % fac;
                g[v1].insert(make_pair(v2, i));
                g[v2].insert(make_pair(v1, i));
            }

            euler(a[1] % fac);
            for (auto v : ret) {
                printf("%d %d ", v.first, v.second);
            }
            return 0;
        }
    }

    printf("-1\n");
    return 0;
}