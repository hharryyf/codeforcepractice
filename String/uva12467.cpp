#include <bits/stdc++.h>
#define MAX_SIZE 2000111
using namespace std;

char st[MAX_SIZE];
int p[MAX_SIZE];

int main() {
    int T, i, j;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%s", st + 1);
        int N = strlen(st + 1);
        st[N + 1] = '#';
        for (i = 1; i <= N; ++i) {
            st[i + N + 1] = st[N - i + 1];
            p[i] = 0;
        }

        for (i = 2, j = 0; i <= 2 * N + 1; ++i) {
            while (j > 0 && st[i] != st[j+1]) j = p[j];
            if (st[i] == st[j+1]) ++j;
            p[i] = j;
        } 

        int ans = 1;
        for (i = N + 2; i <= 2 * N + 1; ++i) {
            ans = max(ans, p[i]);
        }

        for (i = ans; i >= 1; --i) {
            putchar(st[i]);
        }
        putchar('\n');
    }
    return 0;
}