#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

int L[MAX_SIZE], R[MAX_SIZE];

bool check(int up, int len) {
    return (min(R[up], R[up - len + 1]) - max(L[up], L[up - len + 1]) + 1) >= len;
}

int main() {
    int i, ans = 0, N;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%d%d", &L[i], &R[i]);
        int low = 1, high = i;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (check(i, mid)) {
                ans = max(ans, mid);
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}