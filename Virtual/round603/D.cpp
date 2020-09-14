#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 201111
using namespace std;

int f[MAX_SIZE];
char st[MAX_SIZE];

int find(int x) {
    if (x == f[x]) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int a = find(x), b = find(y);
    f[a] = b;
}

int n;

int main() {
    int i, len, j;
    for (i = 0; i < MAX_SIZE; ++i) f[i] = i;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%s", st);
        len = (int) strlen(st);
        for (j = 0 ; j < len; ++j) {
            unionset(n + 1 + st[j] - 'a', i);
        }
    }

    set<int> s;
    for (i = 1; i <= n; ++i) {
        s.insert(find(i));
    }

    printf("%d\n", (int) s.size());
    return 0;
}