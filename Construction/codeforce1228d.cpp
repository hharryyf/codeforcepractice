#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;
int n, m;

set<int> g[MAX_SIZE];
set<int> s1, s2, s3;
int ans[MAX_SIZE];

int main() {
    int i, j;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; ++i) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        g[v1].insert(v2), g[v2].insert(v1);
    }

    s1.insert(1);
    for (i = 2; i <= n; ++i) {
        if (g[1].find(i) == g[1].end()) {
            s1.insert(i);
        }
    }

    for (i = 2; i <= n; ++i) {
        if (s1.find(i) == s1.end()) {
            s2.insert(i);
            for (j = 1; j <= n; ++j) {
                if (g[i].find(j) == g[i].end()) {
                    s2.insert(j);
                }
            }
            break;
        }
    }

    for (i = 1; i <= n; ++i) {
        if (s1.find(i) == s1.end() && s2.find(i) == s2.end()) {
            s3.insert(i);
            for (j = 1; j <= n; ++j) {
                if (g[i].find(j) == g[i].end()) {
                    s3.insert(j);
                }
            }
            break;
        }
    }

    int sz1 = s1.size(), sz2 = s2.size(), sz3 = s3.size();
    if (sz1 == 0 || sz2 == 0 || sz3 == 0 || sz1 + sz2 + sz3 != n) {
        printf("-1\n");
        return 0;
    } 

    // check s1, s2, s3 not intersect
    for (auto v : s1) {
        if (s2.find(v) != s2.end()) {
            printf("-1\n");
            return 0;
        }

        if (s3.find(v) != s3.end()) {
            printf("-1\n");
            return 0;
        }

        for (auto nv : g[v]) {
            if (s1.find(nv) != s1.end()) {
                printf("-1\n");
                return 0;
            }
        }
    }

    for (auto v : s2) {
        if (s1.find(v) != s1.end()) {
            printf("-1\n");
            return 0;
        }

        if (s3.find(v) != s3.end()) {
            printf("-1\n");
            return 0;
        }

        for (auto nv : g[v]) {
            if (s2.find(nv) != s2.end()) {
                printf("-1\n");
                return 0;
            }
        }
    }

    for (auto v : s3) {
        for (auto nv : g[v]) {
            if (s3.find(nv) != s3.end()) {
                printf("-1\n");
                return 0;
            }
        }
    }

    // check all points in s1 is connected with all points in s2/s3
    for (auto v : s1) {
        if ((int) g[v].size() != sz2 + sz3) {
            printf("-1\n");
            return 0;
        }
    }

    for (auto v : s2) {
        if ((int) g[v].size() != sz1 + sz3) {
            printf("-1\n");
            return 0;
        }
    }

    for (auto v : s3) {
        if ((int) g[v].size() != sz2 + sz1) {
            printf("-1\n");
            return 0;
        }
    }

    for (auto v : s1) {
        ans[v] = 1;
    }

    for (auto v : s2) {
        ans[v] = 2;
    }

    for (auto v : s3) {
        ans[v] = 3;
    }

    for (i = 1; i <= n; ++i) {
        printf("%d ", ans[i]);
    }
    printf("\n");
    return 0;
}