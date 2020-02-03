#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 1000011
using namespace std;

char s[MAX_SIZE], p[MAX_SIZE];
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
    int cnt = 0;
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (j == -1 || s[i] == p[j]) {
            i++, j++;
            if (j == m) {
                cnt++;
                j = nxt[j-1];
                if (i != n) i--;
            }
        } else {
            j = nxt[j];
        }
        
    }
    
    return cnt;
}

int main() {
    int T, i;
    scanf("%d", &T);
    while (T > 0) {
        scanf("%s", p);
        scanf("%s", s);
        n = strlen(s), m = strlen(p);
        printf("%d\n", KMP());
        T--;
    }
    return 0;
}
