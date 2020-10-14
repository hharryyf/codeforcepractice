#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 2097312
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
using namespace std;

vector<int> g[MAX_SIZE];
int a[MAX_SIZE][2];
char st[MAX_SIZE];
int f[MAX_SIZE];

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

int main() {
    int n, i, j, cnt;
    scanf("%d", &n);
    scanf("%s", st + 1);
    for (i = n; i >= 1; --i) {
        if (st[i] != '1') {
            a[i][0] = a[i+1][0] + 1;
        }
        
        if (st[i] != '0') {
            a[i][1] = a[i+1][1] + 1;
        }

        g[max(a[i][1], a[i][0])].push_back(i);
        f[i] = i;
    }

    f[n + 1] = n + 1;

    for (i = 1; i <= n; ++i) {
        j = 1, cnt = 0;
        while (j <= n) {
            j = find(j);
            if (j > n) {
                break;
            }

            cnt++;
            j += i;
        }

        printf("%d ", cnt);
        for (auto v : g[i]) {
            f[v] = v + 1;
        }
    }

    return 0;
}