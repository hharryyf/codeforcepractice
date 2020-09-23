#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int c1[27], c2[27];
char s[1011], t[1011];

int main() {
    scanf("%s", s);
    scanf("%s", t);
    int n = strlen(s), m = strlen(t);
    int i;
    for (i = 0 ; i < n; ++i) c1[s[i] - 'a']++;
    for (i = 0 ; i < m; ++i) c2[t[i] - 'a']++;
    int ans = 0;
    for (i = 0 ; i < 26; ++i) {
        if (c1[i] == 0 && c2[i] != 0) {
            cout << -1 << endl;
            return 0;
        }
        ans += min(c1[i], c2[i]);
    }
    cout << ans << endl;
    return 0;
}