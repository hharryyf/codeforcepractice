#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 200011
using namespace std;
char st[MAX_SIZE];
int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%s", st);
        int n = strlen(st);
        if (st[n-1] == 'o') {
            printf("FILIPINO\n");
        } else if (st[n-1] == 'u') {
            printf("JAPANESE\n");
        } else {
            printf("KOREAN\n");
        }
    }
    return 0;
}