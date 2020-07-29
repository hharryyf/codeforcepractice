#include <bits/stdc++.h>
typedef __int128_t lll;
typedef long long ll;
using namespace std;

int N;
ll A, B, L, R;
lll period;
vector<pair<ll, ll>> itv;
ll ans = 0;

int main() {
    int i;
    cin >> N >> A >> B;
    period = (lll) A * B;
    period /= __gcd(A, B + 1);
    for (i = 0 ; i < N; ++i) {
        scanf("%lld%lld", &L, &R);
        if (R - L + 1 >= period) {
            itv.emplace_back(0, (ll) period - 1);
        } else {
            ll l = L % period, r = R % period;
            if (r >= l) {
                itv.emplace_back(l, r);
            } else {
                //cout << "Case 2" << endl;
                itv.emplace_back(0, r);
                itv.emplace_back(l, (ll) period - 1);
            }
        }
    }
    
    sort(itv.begin(), itv.end());
    L = itv.front().first, R = itv.front().second;
    for (i = 1; i < (int) itv.size(); ++i) {
        if (itv[i].first > R) {
            ans += R - L + 1;
            L = itv[i].first, R = itv[i].second;
        } else {
            R = max(R, itv[i].second);
        }
    }
    
    ans += R - L + 1;
    cout << ans << endl;
    return 0;
}