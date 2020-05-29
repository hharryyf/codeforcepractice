#include <bits/stdc++.h>
#define MAX_SIZE 5011
using namespace std;

int a[MAX_SIZE];

int main() {
    int i, n, m, pos = -1;
    scanf("%d%d", &n, &m);
    if (n < 3 && m != 0) {
        printf("-1\n");
        return 0;
    }

    a[1] = 1;
    for (i = 2; i <= n; ++i) {
        int nxt = (i - 1) / 2;
        if (m < nxt) {
            pos = i;
            break;
        }
        a[i] = i;
        m -= nxt;
    }

    if (pos == -1 && m > 0) {
        printf("-1\n");
        return 0;
    }

    if (m != 0) {
        int delta = m;
        a[pos] = a[pos - 2 * delta] + a[pos - 1];
        // cout << pos << " " << a[pos] << endl;
        pos++;
        m = 0;
        // len = delta * 2
        // i = pos - len
    }

    if (a[n] == 0) {
        a[n] = 1e9 - 1;
    }

    for (i = n - 1; i >= pos && pos != -1; --i) {
        a[i] = a[i+1] - 5002;
    }

    for (i = 1; i <= n; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}   