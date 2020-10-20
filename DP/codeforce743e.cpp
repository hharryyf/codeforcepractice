#include <bits/stdc++.h>

using namespace std;

int dp[1011][256], a[1011];
vector<int> pos[8];
int occ[8][2];
int n;
// we can definitely binary search on the final answer
// len means all of the length of 1-8 must be len or len + 1
// check whether this can exist, if so, return the maximum length
// of this group otherwise return -1
int check(int len) {
    int i, j, k;
    for (i = 0 ; i <= n; ++i) {
        for (j = 1 ; j < (1 << 8); ++j) {
            dp[i][j] = -1000000;
        }
    }


    for (i = 0; i < n; ++i) {
        for (j = 0; j < 8; ++j) {
            int sz = pos[j].size();
            occ[j][0] = -1, occ[j][1] = -1;
            int idx = lower_bound(pos[j].begin(), pos[j].end(), i + 1) - pos[j].begin();
            if (idx + len  - 1 < sz) {
                if (idx + len - 1 >= 0) {
                    occ[j][0] = pos[j][idx + len - 1];
                    //cout << "check " << len << endl;
                    //cout << "update " << occ[j][0] << " for " << j << endl;
                } else {
                    occ[j][0] = i;
                    //cout << "check " << len << " " << j << endl;
                }
            }
            if (idx + len < sz) occ[j][1] = pos[j][idx + len];
        }

        for (j = 0 ; j < (1 << 8); ++j) {
            for (k = 0 ; k < 8; ++k) {
                if ((1 << k) & j) continue;
                int nxt = j | (1 << k);
                // search from i + 1, len ocurrence of k
                if (occ[k][0] != -1) dp[occ[k][0]][nxt] = max(dp[occ[k][0]][nxt], dp[i][j] + len);
                if (occ[k][1] != -1) dp[occ[k][1]][nxt] = max(dp[occ[k][1]][nxt], dp[i][j] + len + 1);
            }
        }
    }

    int ans = -1;
    for (i = 1 ; i <= n; ++i) {
        ans = max(ans, dp[i][255]);
    }
    return ans;
}

int main() {
    int i, low, high;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        a[i]--;
        pos[a[i]].push_back(i);
    }

    low = 0, high = n;
    int ans = 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        int curr = check(mid);
        ans = max(ans, curr);
        if (curr < 0) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    printf("%d\n", ans);
    return 0;
}