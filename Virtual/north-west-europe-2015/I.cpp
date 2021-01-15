#include <bits/stdc++.h>

using namespace std;

char st[32];
int N;

void divc(int x1, int y1, int x2, int y2, int idx) {
    if (idx == N) {
        printf("%d %d\n", x1, y1);
        return;
    }
    int mx = x1 + (x2 - x1) / 2, my = y1 + (y2 - y1) / 2;
    if (st[idx] == '0') {
        divc(x1, y1, mx, my, idx + 1);
    } else if (st[idx] == '1') {
        divc(mx + 1, y1, x2, my, idx + 1);
    } else if (st[idx] == '2') {    
        divc(x1, my + 1, mx, y2, idx + 1);
    } else if (st[idx] == '3') {
        divc(mx + 1, my + 1, x2, y2, idx + 1);
    }
}

int main() {
    scanf("%s", st);
    N = strlen(st);
    printf("%d ", N);
    divc(0, 0, (1 << N) - 1, (1 << N) - 1, 0);
    return 0;
}