#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 1000011
using namespace std;

char p[MAX_SIZE];
int nxt[MAX_SIZE];
int m;

void calnext() {
    nxt[0] = -1;
    int j = 0, k = -1;
    while (j <= m - 1) {
        if (k == -1 || p[j] == p[k]) {
            j++, k++;
            nxt[j] = k;
        } else {
            k = nxt[k];
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T > 0) {
        scanf("%s", p);
        m = strlen(p);
        calnext();
        int prd = m - nxt[m];
        if (m % prd == 0 && m != prd) {
	    printf("0\n");
	} else {
	    printf("%d\n", prd - m % prd);
	}
        T--;
    }
    return 0;
}
