#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

int s[MAX_SIZE], t[MAX_SIZE];
int n;

int main() {
    int i;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &s[i]);
    }

    for (i = 1; i <= n; ++i) {
        scanf("%d", &t[i]);
    }

    if (s[1] != t[1] || s[n] != t[n]) {
        printf("No\n");
        return 0;
    }

    for (i = 1; i < n; ++i) {
        s[i] = s[i+1] - s[i];
        t[i] = t[i+1] - t[i];
    }   

    sort(t, t + n);
    sort(s, s + n);
    for (i = 1; i < n; ++i) {
        if (s[i] != t[i]) {
            printf("No\n");
            return 0;
        }
    }

    printf("Yes\n");
    return 0;
}