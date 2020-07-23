#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 100111
using namespace std;

char st[MAX_SIZE];
int visited[MAX_SIZE];
int bit[MAX_SIZE][66];
int cnt[7];
char tmp[7];
char ans[MAX_SIZE];
int encode(char ch) {
    return ch - 'a';
}

bool check(int pos) {
    int i, j;
    for (i = 1 ; i < 64; ++i) {
        int sm = 0;
        for (j = 0 ; j < 6; ++j) {
            if ((1<<j) & i) {
                sm += cnt[j];
            }
        }

        if (sm < bit[pos][i]) {
            // cout << "pos= " << pos << " fail " << sm << " > " << bit[pos][i] << " bit= " << i << endl;
            return false;
        }
    }

    // cout << "pos find " << pos << endl;
    return true;
}

int main() {
    int m, i, n, j;
    scanf("%s", st + 1);
    n = strlen(st+1);
    for (i = 1; i <= n; ++i) {
        cnt[encode(st[i])]++;
    }

    scanf("%d", &m);
    for (i = 1; i <= m; ++i) {
        int idx;
        scanf("%d%s", &idx, tmp);
        for (j = 0 ; j < (int) strlen(tmp); ++j) {
            visited[idx] |= (1 << encode(tmp[j]));
        }
    }

    for (i = 1; i <= n; ++i) {
        if (!visited[i]) visited[i] = 63;
    }

    // bit[i][j] refers to the total number of allowed
    // position when considering st[i:n] such that union of
    // allowed letters form a bitmask of j

    for (i = n; i >= 1; --i) {
        for (j = 1; j < 64; ++j) {
            bit[i][j] = bit[i+1][j] + ((visited[i] & j) == visited[i]);    
        }
    }   
    for (i = 1; i <= n; ++i) {
        bool valid = false;
        for (j = 0 ; j < 6; ++j) {
            if (cnt[j] <= 0) continue;
            if ((1 << j) & visited[i]) {
                // cout << "pos= " << i << " attempt " << (char) (j + 'a') << endl;
                cnt[j]--;
                if (check(i+1)) {
                    ans[i] = j + 'a';
                    valid = true;
                    break;
                }
                cnt[j]++;
            }
        }

        if (!valid) {
            printf("Impossible\n");
            return 0;
        }
    }

    for (i = 1; i <= n; ++i) putchar(ans[i]);
    return 0;
}