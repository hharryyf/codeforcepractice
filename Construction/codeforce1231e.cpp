#include <bits/stdc++.h>
#define MAX_SIZE 111
using namespace std;

char s[MAX_SIZE], t[MAX_SIZE];
int cnt[26];
int N;

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int i, j;
        bool valid = true;
        scanf("%d", &N);
        scanf("%s", s + 1);
        scanf("%s", t + 1);
        for (i = 0 ; i < 26; ++i) cnt[i] = 0;
        for (i = 1; i <= N; ++i) {
            cnt[s[i] - 'a']++;
        }

        for (i = 1; i <= N; ++i) {
            cnt[t[i] - 'a']--;
        }

        for (i = 0 ; i < 26; ++i) {
            if (cnt[i] != 0) {
                printf("-1\n");
                valid = false;
                break;
            }
        }

        if (!valid) continue;
        int ans = 0;
        for (i = 1; i <= N; ++i) {
            for (j = 1; j <= i; ++j) {
                // check t[j:i] match s
                int l = j, r = 1;
                while (l <= i && r <= N) {
                    if (t[l] == s[r]) {
                        l++, r++;
                    } else {
                        r++;
                    }
                }

                if (l == i + 1) {
                    ans = max(ans, i - j + 1);
                }
            }
        }

        printf("%d\n", N - ans);
    }
    return 0;
}