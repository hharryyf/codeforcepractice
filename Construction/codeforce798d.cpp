#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;
typedef long long ll;
pair<pair<int, int>, int> a[MAX_SIZE];

int main() {
    int n, i;
    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
        scanf("%d", &a[i].first.first);
        a[i].second = i + 1;
    }

    for (i = 0 ; i < n; ++i) {
        scanf("%d", &a[i].first.second);
    }

    sort(a, a + n, greater<pair<pair<int, int>, int>>());
    printf("%d\n%d", n / 2 + 1, a[0].second);
    for (i = 1; i < n; i += 2) {
        if (a[i].first.second >= a[i+1].first.second) {
            printf(" %d", a[i].second);
        } else {
            printf(" %d", a[i+1].second);
        }
    }
    return 0;
}