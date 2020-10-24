#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

int n, p;
int a[MAX_SIZE];

bool check1(int x) {
    int i, j, target, curr = 0;
    for (i = 1, j = 1; i <= n; ++i) {
        target = x + i - 1;
        while (j <= n && target >= a[j]) {
            j++;
            curr++;
        } 

        curr--;
        if (curr < 0) {
            return false;
        }
    }

    return true;
}

bool check2(int x) {
    int i, j, target, curr = 0;
    for (i = 1, j = 1; i <= n; ++i) {
        target = x + i - 1;
        while (j <= n && target >= a[j]) {
            j++;
            curr++;
        } 

        if (curr % p == 0) return false;
        curr--;
    }
    return true;
}

int main() {
    int i;
    scanf("%d%d", &n, &p);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }

    sort(a + 1, a + 1 + n);
    int l = -1, r = -1, low, high;
    low = 1, high = 1001000000;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (check1(mid)) {
            l = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    if (low == -1) {
        printf("0\n");
        return 0;
    }

    low = l, high = 1001000000;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (check2(mid)) {
            r = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }    

    if (r == -1) {
        printf("0\n");
        return 0;
    }

    printf("%d\n", r - l + 1);
    for (i = l; i <= r; ++i) {
        printf("%d ", i);
    }
    return 0;
}