#include <bits/stdc++.h>
#define MAX_SIZE 5011
using namespace std;

char st[MAX_SIZE >> 1][MAX_SIZE];
int occ[MAX_SIZE >> 1][26];

int main() {
    int k, n, i, j, idx = -1, ok = 0, l, r;
    scanf("%d%d", &k, &n);
    vector<int> dif;
    for (i = 1; i <= k; ++i) {
        scanf("%s", st[i] + 1);
        for (j = 1; j <= n; ++j) {
            occ[i][st[i][j] - 'a']++;
            if (occ[i][st[i][j] - 'a'] > 1) ok = 1;
        }
    }
    
    for (i = 2; i <= k; ++i) {
        for (j = 0 ; j < 26; ++j) {
            if (occ[i][j] != occ[i-1][j]) {
                printf("-1\n");
                return 0;
            }
        }
    }

    vector<int> swp;
    for (i = 2; i <= k; ++i) {
        for (j = 1; j <= n; ++j) {
            if (st[i][j] != st[i-1][j]) {
                swp.push_back(j);
                idx = i - 1;
            }
        }

        if (idx != -1) break;
    }

    if ((int) swp.size() > 4) {
        printf("-1\n");
        return 0;
    }

    if (idx == -1) {
        swap(st[1][1], st[1][2]);
        printf("%s\n", st[1] + 1);
        return 0;
    }

    for (i = 0 ; i < (int) swp.size(); ++i) {
        for (j = 1; j <= n; ++j) {
            if (j == swp[i]) continue;
            swap(st[idx][swp[i]], st[idx][j]);
            bool valid = true;
            for (l = 1; l <= k; ++l) {
                if (l == idx) continue;
                int cnt = 0;
                for (r = 1; r <= n; ++r) {
                    if (st[idx][r] != st[l][r]) cnt++;
                }

                if (cnt > 2 || (cnt == 0 && ok == 0)) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                printf("%s\n", st[idx] + 1);
                return 0;
            }
            swap(st[idx][swp[i]], st[idx][j]);
        }
    }

    idx++;
    for (i = 0 ; i < (int) swp.size(); ++i) {
        for (j = 1; j <= n; ++j) {
            if (j == swp[i]) continue;
            swap(st[idx][swp[i]], st[idx][j]);
            bool valid = true;
            for (l = 1; l <= k; ++l) {
                if (l == idx) continue;
                int cnt = 0;
                for (r = 1; r <= n; ++r) {
                    if (st[idx][r] != st[l][r]) cnt++;
                }

                if (cnt > 2 || (cnt == 0 && ok == 0)) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                printf("%s\n", st[idx] + 1);
                return 0;
            }
            swap(st[idx][swp[i]], st[idx][j]);
        }
    }

    printf("-1\n");
    return 0;
}