#include <bits/stdc++.h>
#define MAX_SIZE 1011
typedef long long ll;
using namespace std;
int N, K;
vector<pair<int, int>> a, b;

ll solve(vector<pair<int, int>> &vc) {
    ll cost = 0;
    int sz = vc.size() - 1, i;
    int amount = 0;
    for (i = sz; i >= 0; --i) {
        if (amount >= vc[i].second) {
            amount -= vc[i].second;
        } else {
            vc[i].second -= amount;
            cost += 1ll * ((vc[i].second / K) + ((vc[i].second % K) != 0)) * vc[i].first * 2;
            if (vc[i].second % K != 0) {
                amount = K - vc[i].second % K;
            } else {
                amount = 0;
            }
        }
    }

    return cost;
}

int main() {
    int i;
    scanf("%d%d", &N, &K);
    for (i = 1; i <= N; ++i) {
        int xi, mi;
        scanf("%d%d", &xi, &mi);
        if (xi > 0) {
            a.emplace_back(xi, mi);
        } else {
            b.emplace_back(-xi, mi);
        }
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    printf("%I64d\n", solve(a) + solve(b));
    return 0;
}