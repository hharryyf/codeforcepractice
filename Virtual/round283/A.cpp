#include <bits/stdc++.h>
#define MAX_SIZE 200011
typedef long long ll;
using namespace std;
int n;
int a[111];

int solve(int idx) {
    int curr = a[idx], ret = 0, i;
    a[idx] = a[idx-1];
    for (i = 2; i <= n; ++i) {
        ret = max(ret, a[i] - a[i-1]);
    }

    a[idx] = curr;
    return ret;
}

int main() {    
    int i, ans = 5000;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }

    for (i = 2; i <= n - 1; ++i) {
        ans = min(ans, solve(i));
    }

    printf("%d\n", ans);
    return 0;
}