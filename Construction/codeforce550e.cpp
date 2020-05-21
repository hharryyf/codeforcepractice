#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;
int a[MAX_SIZE];
int n;
bool invalid() {
    if (a[n] == 1) return true;
    if (n == 2 && a[1] == 0 && a[2] == 0) return true;
    int i;
    if (n > 2 && a[n] == 0 && a[n-1] == 0) {
        for (i = n - 2; i >= 1; --i) {
            if (a[i] == 0) return false;
        } 
        return true;
    }
    return false;
}

int main() {
    int i;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) scanf("%d", &a[i]);
    if (invalid()) {
        printf("NO\n");
        return 0;
    }

    printf("YES\n");
    if (n == 1) {
        printf("0\n");
    } else if (n == 2) {
        printf("%d->%d\n", a[n-1], a[n]);
    } else {
        if (a[n-1] == 1) {
            for (i = 1; i <= n - 1; ++i) {
                printf("%d->", a[i]);
            }
            printf("%d\n", a[n]);
        } else {
            int pos = 0;
            for (i = n - 2; i >= 1; --i) {
                if (a[i] == 0) {
                    pos = i;
                    break;
                }
            }           

            // make the sequence look like 
            // [a[1]->->a[pos-1]] -> (a[pos] ->(a[pos + 1]->...a[n-1]))->a[n]
            for (i = 1; i <= pos - 1; ++i) {
                printf("%d->", a[i]);
            }
            printf("(%d->(", a[pos]);
            for (i = pos + 1; i <= n - 1; ++i) {
                printf("%d", a[i]);
                if (i != n - 1) {
                    printf("->");
                }
            }
            printf("))->%d\n", a[n]);
        }
    }
    return 0;
}