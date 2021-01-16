#include <bits/stdc++.h>
#define MAX_SIZE 211
using namespace std;

const int inf = 1e8;
int N, P, dp[MAX_SIZE][MAX_SIZE];
vector<pair<int, int>> p;
vector<pair<int, int>> tp1, tp2;

static bool cmp1(pair<int, int> &p1, pair<int, int> &p2) {
    return (p1.second - p1.first) > (p2.second - p2.first);
}

int main() {
    int i, j, k;
    scanf("%d%d", &N, &P);    
    for (i = 1; i <= N; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        p.emplace_back(u, v);
    }

    sort(p.begin(), p.end(), cmp1);
    for (i = 0 ; i < N; ++i) {
        bool ok = false;
        for (j = i + 1 ; j < N; ++j) {
            if (p[i].first <= p[j].first && p[j].second <= p[i].second) {
                tp1.push_back(p[i]);
                ok = true;
                break;
            }
        }

        if (!ok) {
            tp2.push_back(p[i]);
        }
    }

    sort(tp1.begin(), tp1.end(), cmp1);
    sort(tp2.begin(), tp2.end());
    int sz = tp2.size();

    for (i = 1 ; i <= N; ++i) {
        for (j = 0; j <= N; ++j) {
            dp[i][j] = -inf;
        }
    }

    for (i = 1; i <= sz; ++i) {
        for (j = 1; j <= i; ++j) {
            for (k = 1; k <= i; ++k) {
                if (tp2[k-1].second <= tp2[i-1].first) continue;
                dp[i][j] = max(dp[i][j], dp[k-1][j-1] + tp2[k-1].second - tp2[i-1].first);
            }
        }
    }

    int ans = -inf;
    for (i = 0; i <= P; ++i) {
        int tol = 0;
        for (j = 0; j < P - i && j < (int) tp1.size(); ++j) {
            tol = tol + tp1[j].second - tp1[j].first;
        }

        ans = max(ans, tol + dp[sz][i]);
    }

    cout << ans << endl;
    return 0;
}