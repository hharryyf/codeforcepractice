#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 1000111
using namespace std;

char s[MAX_SIZE];
int nxt[MAX_SIZE];
int m;

void calnext() {
    nxt[0] = -1;
    int j = 0, k = -1;
    while (j <= m - 1) {
        if (k == -1 || s[j] == s[k]) {
            j++, k++;
            nxt[j] = k;
        } else {
            k = nxt[k];
        }     
    }
}

int main() {
    while (gets(s) != NULL) {
        m = strlen(s);
        if (strcmp(s, ".") == 0) break;
        calnext();
        int prd = m - nxt[m];
        if (m % prd == 0) {
            printf("%d\n", m / prd);
        } else {
            printf("1\n");
        }
    }
    return 0;
}
