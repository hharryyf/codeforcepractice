#include <bits/stdc++.h>
#define MAX_SIZE 711
using namespace std;

vector<char> g[MAX_SIZE];
vector<int> p[MAX_SIZE];
int curr[MAX_SIZE];
int cost[MAX_SIZE][MAX_SIZE];
void upd(int idx, char ch) {
    g[idx].push_back(ch);
    // special case for index 1
    if ((int) g[idx].size() == 2) {
        p[idx].push_back(0);
        return;
    }
    while (curr[idx] > 0 && ch != g[idx][curr[idx]+1]) curr[idx] = p[idx][curr[idx]];
    if (g[idx].back() == g[idx][curr[idx]+1]) ++curr[idx];
    p[idx].push_back(curr[idx]);
}

char st[MAX_SIZE];
int N;

void precompute() {
    int i, j;
    for (i = 1; i <= N; ++i) {
        g[i].push_back('#');
        p[i].push_back(0);
    }

    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= i; ++j) {
            upd(j, st[i]);
            int len = (i - j + 1) - p[j].back();
            if ((i - j + 1) % len == 0 && len != (i - j + 1)) {
                cost[j][i] = len;
            }
        }
    }
}

int dp[MAX_SIZE][MAX_SIZE];

int f(int l, int r) {
    // cout << l << " " << r << endl;
    if (l > r) return 0;
    if (l == r) {
        return 1;
    }

    if (dp[l][r] != 0) return dp[l][r];
    if (cost[l][r] != 0) {
        // cout << "l= " << l << " r= " << r << " cost= " << cost[l][r] << endl;
        r = cost[l][r] + l - 1;
        // cout << "enter " << l << " " << r << endl;
        dp[l][r] = f(l, r);

        return dp[l][r];
    }

    int i;
    int ans = r - l + 1;
    for (i = l; i < r; ++i) {
        ans = min(ans, f(l, i) + f(i + 1, r));
    }

    return dp[l][r] = ans;
}

int main() {
    scanf("%d", &N);
    scanf("%s", st + 1);
    precompute();
    /*
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            printf("%d ", cost[i][j]);
        }
        printf("\n");
    }*/
    printf("%d\n", f(1, N));
    
    return 0;
}