#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 111
using namespace std;
char st[MAX_SIZE];
int main() {
    int n, i;
    scanf("%d", &n);
    scanf("%s", st);
    for (i = 1; i < n; ++i) {
        if (st[i] != '?' && st[i-1] != '?') {
            if (st[i] == st[i-1]) {
                printf("No\n");
                return 0;
            }
        }
    }

    for (i = 1; i < n - 1; ++i) {
        if (st[i] == '?' && st[i-1] != '?' && st[i+1] != '?' && st[i-1] != st[i+1]) {
            st[i] = '#';
        }
    }

    for (i = 0; i < n; ++i) {
        if (st[i] == '?') {
            printf("Yes\n");
            return 0;
        }
    }

    printf("No\n");
    return 0;
}