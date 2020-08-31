#include <bits/stdc++.h>
#define MAX_SIZE 1000011
using namespace std;

int p[MAX_SIZE];
char st[MAX_SIZE];

int main() {
    int N, K, i, j = 0;
    scanf("%d%d", &N, &K);
    scanf("%s", st+1);
    for (i = 2; i <= N; ++i) {
        while (j > 0 && st[i] != st[j+1]) j = p[j];
        if (st[i] == st[j+1]) ++j;
        p[i] = j;
    }

    for (i = 1; i <= N; ++i) {
        int period = i - p[i];
        // cout << "period= " << period << endl;
        bool valid = false;
        j = 1ll * i / (1ll * period * K);
        if (j < 1) j = 1;
        valid = (1ll * period * j * K <= 1ll * i) && (1ll * period * j * (K + 1) >= 1ll * i);
        printf("%d", valid);
    }
    return 0;
}