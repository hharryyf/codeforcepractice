#include <bits/stdc++.h>
#define MAX_SIZE 1011
using namespace std;

int f[MAX_SIZE];

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int a = find(x), b = find(y);
    f[a] = b;
}

int t[MAX_SIZE], l[MAX_SIZE], r[MAX_SIZE];
int a[MAX_SIZE];

int main() {
    int i, j, n, m;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i) f[i] = i;
    for (i = 1; i <= m; ++i) {
        scanf("%d%d%d", &t[i], &l[i], &r[i]);
        if (t[i] == 1) {
            for (j = l[i]; j <= r[i] - 1; ++j) {
                unionset(j, j + 1);
            }
        }
    }

    for (i = 1; i <= n; ++i) {
        if (i == 1) {
            a[i] = 1000000000;
        } else {
            if (find(i) == find(i-1)) {
                a[i] = a[i-1];
            } else {
                a[i] = a[i-1] - 1;
            }
        }
    }

    for (i = 1; i <= m; ++i) {
        bool flag = false;
        if (t[i] == 1) continue;
        for (j = l[i]; j < r[i]; ++j) {
            if (a[j] > a[j+1]) {
                flag = true;
                break;
            }
        }

        if (!flag) {
            printf("NO\n");
            return 0;
        }
    }

    printf("YES\n");
    for (i = 1; i <= n; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}