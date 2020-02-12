#include <bits/stdc++.h>
#define MAX_SIZE 2011
using namespace std;

bool dp[MAX_SIZE >> 1][MAX_SIZE];
char s[MAX_SIZE];

int main() {
    
    int shift = 1001, n, k, i, j;
    scanf("%d%d", &n, &k);
    scanf("%s", s);
    dp[0][shift] = true;
    for (i = 1; i <= n; i++) {
        for (j = -k; j <= k; j++) {
            if ((j == -k || j == k) && i != n) continue;
            if (s[i-1] == 'W') {
                dp[i][j+shift] = dp[i-1][j+shift-1];
            } else if (s[i-1] == 'D') {
                dp[i][j+shift] = dp[i-1][j+shift];
            } else if (s[i-1] == 'L') {
                dp[i][j+shift] = dp[i-1][j+shift+1];
            } else {
                dp[i][j+shift] = (dp[i-1][j+shift+1] || dp[i-1][j+shift] || dp[i-1][j+shift-1]); 
            }
        }
    }
    
    i = n, j = 0;
    if (dp[n][k+shift]) {
        j = k + shift;
    } else if (dp[n][-k+shift]) {
        j = -k+shift;
    } else {
        printf("NO\n");
        return 0;
    }
    stack<char> st;
    while (i > 0) {
        if (s[i-1] == 'W') {
            st.push('W');
            i--;
            j--;
        } else if (s[i-1] == 'D') {
            st.push('D');
            i--;
        } else if (s[i-1] == 'L') {
            st.push('L');
            i--;
            j++;
        } else {
            if (dp[i-1][j-1]) {
                st.push('W');
                i--, j--;
            } else if (dp[i-1][j]) {
                st.push('D');
                i--;
            } else {
                st.push('L');
                i--, j++;
            }
        }
    }
    
    while (!st.empty()) {
        printf("%c", st.top());
        st.pop();
    }
    printf("\n");
    return 0;
}
