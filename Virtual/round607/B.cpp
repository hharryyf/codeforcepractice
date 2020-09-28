#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 5011
using namespace std;

char s[MAX_SIZE], c[MAX_SIZE];

void solve() {
    scanf("%s%s", s, c);
    int i, j, n = strlen(s), m = strlen(c);
    bool ok = false, used = false;
    for (i = 0 ; i < min(n, m); ++i) {
        if (s[i] < c[i]) break; 
        char mn = 'a';
        int idx = -1;
        for (j = n - 1; j >= i + 1; --j) {
            if (s[j] < mn) {
                idx = j;
                mn = s[j];
            }
        }

        if (mn < s[i]) {
            swap(s[idx], s[i]);
            used = true;
        }
        if (used) break;
    }

    ok = (strcmp(s, c) < 0);

    if (ok) {
        printf("%s\n", s);
    } else {
        printf("---\n");
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        solve();
    }
    return 0;
}