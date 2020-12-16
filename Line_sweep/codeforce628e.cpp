#include <bits/stdc++.h>
#define MAX_SIZE 3011
using namespace std;

int N, M;

struct BIT {
    int tree[MAX_SIZE];
    int shift(int x) {
        return x & (-x);
    }

    void update(int index, int val) {
        if (index <= 0) return;
        while (index <= M) {
            tree[index] += val;
            index += shift(index);
        }
    }

    int query(int index) {
        int ret = 0;
        while (index > 0) {
            ret += tree[index];
            index -= shift(index);
        }
        return ret;
    }
};

BIT t[MAX_SIZE * 2];
int zL[MAX_SIZE][MAX_SIZE], zR[MAX_SIZE][MAX_SIZE], zD[MAX_SIZE][MAX_SIZE];
char st[MAX_SIZE][MAX_SIZE];
vector<pair<int, int>> evt[MAX_SIZE * 2];

int main() {
    int i, j;
    scanf("%d%d", &N, &M);
    for (i = 1; i <= N; ++i) {
        scanf("%s", st[i] + 1);
    }

    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= M; ++j) {
            zL[i][j] = zL[i][j-1] * (st[i][j] == 'z') + (st[i][j] == 'z');
        }

        for (j = M; j >= 1; --j) {
            zR[i][j] = zR[i][j+1] * (st[i][j] == 'z') + (st[i][j] == 'z');
        }
    }

    for (i = N; i >= 1; --i) {
        for (j = 1; j <= M; ++j) {
            zD[i][j] = zD[i+1][j-1] * (st[i][j] == 'z') + (st[i][j] == 'z');
        }
    }

    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= M; ++j) {
            evt[j + zR[i][j] - 1].emplace_back(i, j);
        }
    }

    long long ans = 0;
    for (j = M; j >= 1; --j) {
        for (auto p : evt[j]) {
            t[p.first + p.second].update(p.second, 1);
        }

        for (i = 1; i <= N; ++i) {
            int len = min(zL[i][j], zD[i][j]);
            if (len == 0) continue;
            ans = ans + t[i + j].query(j) - t[i + j].query(j - len);
        }
    }

    cout << ans << endl;
    return 0;
}