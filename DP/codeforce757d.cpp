#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const ll mod = 1e9 + 7;
int n;
int dp[76][(1 << 20) + 3];
char st[77];

int main() {
    int i, j;
    scanf("%d", &n);
    scanf("%s", st + 1);
    dp[0][0] = 1;
    for (i = 0; i < n; ++i) {
        for (j = 0 ; j < (1 << 20); ++j) {
            int curr = 0;
                
        }
    }
    return 0;
}