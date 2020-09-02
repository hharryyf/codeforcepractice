#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
map<pair<int, int>, pair<int, int>> mp;
int ans = -1e9;
ll bt = 0;
int N;
int a[27][3];

ll fastpower(int p) {
    ll ret = 1;
    ll base = 3;
    while (p > 0) {
        if (p & 1) {
            ret = ret * base;
            --p;
        } else {
            base = base * base;
            p >>= 1;
        }
    }
    return ret;
}

vector<int> getbit(int val, int tol) {
    vector<int> ret(tol);
    int i = 0;
    while (val > 0) {
        ret[i++] = val % 3;
        val /= 3;
    }
    return ret;
}

int main() {
    int i, j;
    scanf("%d", &N);
    for (i = 0 ; i < N; ++i) {
        for (j = 0 ;j < 3; ++j) {
            scanf("%d", &a[i][j]);
        }
    } 

    int up = fastpower(N / 2);
    for (i = 0 ; i < up; ++i) {
        auto vc = getbit(i, N / 2);
        int b1 = 0, b2 = 0, b3 = 0;
        for (j = 0 ; j < N / 2; ++j) {
            if (vc[j] == 0) {
                b1 += a[j][0], b2 += a[j][1];
            } else if (vc[j] == 1) {
                b1 += a[j][0], b3 += a[j][2];
            } else {
                b2 += a[j][1], b3 += a[j][2];
            }
        }

        pair<int, int> p = make_pair(b2-b1, b3-b1);
        pair<int, int> cost = make_pair(min(b1, min(b2, b3)), i);
        auto iter = mp.find(p);
        if (iter == mp.end()) {
            mp[p] = cost;
        } else {
            iter->second = max(cost, iter->second);
        }
    }

    up = fastpower(N - N / 2);
    for (i = 0 ; i < up; ++i) {
        auto vc = getbit(i, N - N / 2);
        int b1 = 0, b2 = 0, b3 = 0;
        for (j = N / 2; j < N; ++j) {
            if (vc[j-N/2] == 0) {
                b1 += a[j][0], b2 += a[j][1];
            } else if (vc[j-N/2] == 1) {
                b1 += a[j][0], b3 += a[j][2];
            } else {
                b2 += a[j][1], b3 += a[j][2];
            }
        }

        if (mp.count(make_pair(b1-b2,b1-b3))) {
            auto p = mp[make_pair(b1-b2, b1-b3)];
            if (p.first + max(max(b1, b2), b3) >= ans) {
                ans = p.first + max(max(b1, b2), b3);
                bt = fastpower(N/2) * i + p.second; 
            }
        }
    }

    if (ans == -1e9) {
        printf("Impossible\n");
        return 0;
    }

    // printf("%d\n", ans);
    vector<int> ret(N);
    i = 0;
    while (bt > 0) {
        ret[i++] = bt % 3;
        bt /= 3;
    }

    for (i = 0 ; i < N; ++i) {
        if (ret[i] == 0) {
            printf("LM\n");
        } else if (ret[i] == 1) {
            printf("LW\n");
        } else {
            printf("MW\n");
        }
    }
    return 0;
}