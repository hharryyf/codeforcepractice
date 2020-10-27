#include <bits/stdc++.h>
#define MAX_SIZE 200011
#define MAX_L 255
using namespace std;

int dp[MAX_L][MAX_L][MAX_L];
char s[MAX_SIZE], tmp[4];
int nxt[MAX_SIZE][26];
vector<char> s1, s2, s3;

int f(int l1, int l2, int l3) {
    if (l1 < 0 || l2 < 0 || l3 < 0) return MAX_SIZE;
    if (dp[l1][l2][l3] != -1) return dp[l1][l2][l3];
    int ret1 = f(l1 - 1, l2, l3), ret2 = f(l1, l2 - 1, l3), ret3 = f(l1, l2, l3 - 1);
    dp[l1][l2][l3] = MAX_SIZE;
    if (ret1 < MAX_SIZE && l1 >= 1) {
        dp[l1][l2][l3] = min(dp[l1][l2][l3], nxt[ret1 + 1][s1[l1-1] - 'a']);
    }

    if (ret2 < MAX_SIZE && l2 >= 1) {
        dp[l1][l2][l3] = min(dp[l1][l2][l3], nxt[ret2 + 1][s2[l2-1] - 'a']);
    }

    if (ret3 < MAX_SIZE && l3 >= 1) {
        dp[l1][l2][l3] = min(dp[l1][l2][l3], nxt[ret3 + 1][s3[l3-1] - 'a']);
    }

    return dp[l1][l2][l3];
}

int main() {
    int i, j, k, n, q;
    for (i = 0; i < MAX_SIZE; ++i) {
        for (j = 0; j < 26; ++j) {
            nxt[i][j] = MAX_SIZE;
        }
    }

    for (i = 0; i < MAX_L; ++i) {
        for (j = 0 ; j < MAX_L; ++j) {
            for (k = 0 ; k < MAX_L; ++k) {
                dp[i][j][k] = -1;
            }
        }
    }

    scanf("%d%d", &n, &q);
    scanf("%s", s + 1);
    dp[0][0][0] = 0;
    for (i = n; i >= 1; --i) {
        for (j = 0; j < 26; ++j) {
            if ('a' + j == s[i]) {
                nxt[i][j] = i;
            } else {
                nxt[i][j] = nxt[i+1][j];
            }
        }
    }

    while (q-- > 0) {
        int id;
        scanf("%s%d", tmp, &id);
        if (tmp[0] == '+') {
            scanf("%s", tmp);
            if (id == 1) {
                s1.push_back(tmp[0]);
            } else if (id == 2) {
                s2.push_back(tmp[0]);
                
            } else {
                s3.push_back(tmp[0]);        
            }

            int sz1 = s1.size(), sz2 = s2.size(), sz3 = s3.size();
            dp[sz1][sz2][sz3] = f(sz1, sz2, sz3);
        } else {
            if (id == 1) {
                int sz1 = s1.size(), sz2 = s2.size(), sz3 = s3.size();
                for (i = 0; i <= sz2; ++i) {
                    for (j = 0; j <= sz3; ++j) {
                        dp[sz1][i][j] = -1;
                    }
                }
                s1.pop_back();
            } else if (id == 2) {
                int sz1 = s1.size(), sz2 = s2.size(), sz3 = s3.size();
                for (i = 0 ; i <= sz1; ++i) {
                    for (j = 0 ; j <= sz3; ++j) {
                        dp[i][sz2][j] = -1;
                    }
                }
                s2.pop_back();
            } else {
                int sz1 = s1.size(), sz2 = s2.size(), sz3 = s3.size();
                for (i = 0 ; i <= sz1; ++i) {
                    for (j = 0 ; j <= sz2; ++j) {
                        dp[i][j][sz3] = -1;
                    }
                }
                s3.pop_back();
            }
        }

        dp[0][0][0] = 0;
        int sz1 = s1.size(), sz2 = s2.size(), sz3 = s3.size();
        dp[sz1][sz2][sz3] = f(sz1, sz2, sz3);
        printf("%s\n", dp[sz1][sz2][sz3] <= n ? "YES" : "NO");
       //  printf("%d\n", dp[sz1][sz2][sz3]);
    }
    return 0;
}