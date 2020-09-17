#include <bits/stdc++.h>
#define MAX_SIZE 300111
using namespace std;
typedef long long ll;

char st[MAX_SIZE];

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int n, k, i;
        bool valid = true;
        map<int, char> mp;
        scanf("%d%d", &n, &k);
        scanf("%s", st);
        for (i = 0 ; i < n; ++i) {
            if (st[i] == '0' || st[i] == '1') {
                if (mp.find(i % k) != mp.end()) {
                    if (mp[i % k] != st[i]) {
                        printf("NO\n");
                        valid = false;
                        break;
                    }
                }
                mp[i % k] = st[i];
            }
        }

        if (valid) {
            int c1 = 0, c2 = 0;
            for (auto iter : mp) {
                if (iter.second == '1') {
                    c1++;
                } else {
                    c2++;
                }
            }

            if (c1 <= k / 2 && c2 <= k / 2) {
                printf("YES\n");
            } else {
                printf("NO\n");
            }
        }
    }
    return 0;
}