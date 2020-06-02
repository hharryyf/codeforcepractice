#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

pair<int, int> a[MAX_SIZE];
int sa[MAX_SIZE], sb[MAX_SIZE];

int main() {
    int n, i;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &a[i].first);
        a[i].second = i;
    }

    sort(a + 1, a + 1 + n);
    int sz = n / 3 + (n % 3 != 0);
    for (i = 1; i <= sz; ++i) {
        sa[a[i].second] = a[i].first;
    }

    for (i = sz + 1; i <= 2 * sz; ++i) {
        sb[a[i].second] = a[i].first;
    }

    for (i = n; i > 2 * sz; --i) {
        sb[a[i].second] = n - i;
        sa[a[i].second] = a[i].first - sb[a[i].second];
    }

    printf("YES\n");
    for (i = 1; i <= n; ++i) printf("%d ", sa[i]);
    printf("\n");
    for (i = 1; i <= n; ++i) printf("%d ", sb[i]);
    printf("\n");
    return 0;
}