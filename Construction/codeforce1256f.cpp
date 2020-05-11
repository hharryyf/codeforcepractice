#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

char s[MAX_SIZE], t[MAX_SIZE];
int cnt1[29], cnt2[29];
void init() {
    memset(cnt1, 0, sizeof(cnt1));
    memset(cnt2, 0, sizeof(cnt2));
}
int main() {
    int q, i, j;
    scanf("%d", &q);
    while (q-- > 0) {
        int n;
        init();
        scanf("%d", &n);
        scanf("%s", s);
        scanf("%s", t);
        for (i = 0; i < n; ++i) {
            cnt1[s[i] - 'a']++, cnt2[t[i] - 'a']++;
        }

        bool flag = true, flag2 = false;
        for (i = 0 ; i < 26; ++i) {
            if (cnt1[i] != cnt2[i]) {
                printf("NO\n");
                flag = false;
                break;
            }

            if (cnt1[i] > 1 || cnt2[i] > 1) {
                flag2 = true;
            }
        }

        if (!flag) continue;
        if (flag2) {
            printf("YES\n");
            continue;
        }

        int c1 = 0, c2 = 0;
        for (i = 0 ; i < n; ++i) {
            for (j = i + 1; j < n; ++j) {
                if (s[i] > s[j]) {
                    c1++;
                }

                if (t[i] > t[j]) {
                    c2++;
                }
            }
        }

        if (c1 % 2 != c2 % 2) {
            printf("NO\n");
        } else {
            printf("YES\n");
        }
    }
    return 0;
}