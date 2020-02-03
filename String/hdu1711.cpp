#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 1000011
using namespace std;

int s[MAX_SIZE], p[MAX_SIZE];
int nxt[MAX_SIZE];
int n, m;

void calnext() {
    nxt[0] = -1;
    int j = 0, k = -1;
    while (j < m - 1) {
        if (k == -1 || p[j] == p[k]) {
            j++, k++;
            nxt[j] = k;
        } else {
            k = nxt[k];
        }
    }
}

int KMP() {
    calnext();
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (j == -1 || s[i] == p[j]) {
            i++, j++;
        } else {
            j = nxt[j];
        }
    }
    
    if (j == m) {
        return i - j + 1;
    }
    
    return -1;
}

int main() {
    int T, i;
    scanf("%d", &T);
    while (T > 0) {
        scanf("%d%d", &n, &m);
        for (i = 0 ; i < n; i++) {
            scanf("%d", &s[i]);
        }
        for (i = 0 ; i < m; i++) {
            scanf("%d", &p[i]);
        }
        printf("%d\n", KMP());
        T--;
    }
    return 0;
}
