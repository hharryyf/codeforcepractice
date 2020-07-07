#include <bits/stdc++.h>

using namespace std;

int query(vector<int> &vc) {
    printf("? %d",(int) vc.size());
    for (auto v : vc) {
        printf(" %d", v);
    }
    printf("\n");
    fflush(stdout);
    int val;
    scanf("%d", &val);
    return val;
}

int getpos(vector<int> &vc, int x) {
    int low = 0, high = (int) vc.size() - 1;
    int i, ans = 0;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        vector<int> ret;
        for (i = low; i <= mid; ++i) {
            ret.push_back(vc[i]);
        }

        int r = query(ret);
        if (r != x && r != 0) {
            ans = vc[mid];
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return ans;
}

vector<int> g[11][2];
int occ[1011][11];
int xv[11][2];
int ok[1011];

int main() {
    int i, j, n, x, y;
    int tol = 0;
    scanf("%d%d%d", &n, &x, &y);
    tol = (n & 1) * x;
    for (i = 0; (1 << i) <= n; ++i) {
        // if the xor is y/x^y, we can do binary search to extract the y
        // otherwise we should know that both y occurs on the same side
        for (j = 1; j <= n; ++j) {
            g[i][(j >> i) & 1].push_back(j);
            occ[j][i] = (j >> i) & 1;
            ok[j] = 1;
        }
    }

    for (i = 0; (1 << i) <= n; ++i) {
        xv[i][0] = query(g[i][0]);
        xv[i][1] = xv[i][0] ^ tol;
    }

    int pos = 1, pos2 = 1;
    for (i = 0; (1 << i) <= n; ++i) {
        if (xv[i][0] != x && xv[i][0] != 0) {
            if (g[i][0].size() < g[i][1].size()) {
                pos = getpos(g[i][0], x);
            } else {
                pos = getpos(g[i][1], x);
            }
            break;
        }
    }

    for (i = 0; (1 << i) <= n; ++i) {
        int p = occ[pos][i];
        if (xv[i][p] != x && xv[i][p] != 0) {
            for (auto v : g[i][p]) ok[v] = 0;
        } else {
            for (auto v : g[i][1 ^ p]) ok[v] = 0;
        }
    }

    for (i = 1; i <= n; ++i) {
        if (ok[i]) pos2 = i;
    }
    if (pos > pos2) swap(pos, pos2);
    printf("! %d %d\n", pos, pos2);
    fflush(stdout);
    return 0;
}