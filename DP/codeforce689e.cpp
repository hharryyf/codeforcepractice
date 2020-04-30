#include <bits/stdc++.h>
#define MAX_SIZE 400011
typedef long long ll;
using namespace std;

const int mod = 1000000007;

int tmp[MAX_SIZE];
pair<int, int> itv[MAX_SIZE];
vector<int> disc;
multiset<int> st;
int n, k;
ll fac[MAX_SIZE];
/*
    C(n, k) = n!/(k!*(n-k)!)
*/
void preprocess() {
    fac[0] = fac[1] = 1;
    int i;
    for (i = 2; i < MAX_SIZE; ++i) fac[i] = (fac[i-1] * i) % mod;
}

ll ivt(ll p) {
    // this is equivalent to p to the power mod - 2;
    ll base = p, ep = mod - 2;
    ll ret = 1;
    while (ep > 0) {
        if (ep % 2 == 0) {
            base = base * base;
            base %= mod;
            ep >>= 1;
        } else {
            ret = ret * base;
            ret %= mod;
            ep--;
        }
    }
    return ret;
}

ll C(int x, int y) {
    if (x < y) return 0;
    ll ret = (((fac[x] * ivt(fac[y])) % mod) * ivt(fac[x-y])) % mod;
    // cout << "C(" << x << "," << y << ")= " << ret << endl;
    return ret;
}

int main() {
    int i, j = 0;
    scanf("%d%d", &n, &k);
    preprocess();
    for (i = 1; i <= n; ++i) {
        scanf("%d%d", &itv[i].first, &itv[i].second);
        tmp[j++] = itv[i].first, tmp[j++] = itv[i].second;
    }

    sort(tmp, tmp + j);
    sort(itv + 1, itv + 1 + n);
    for (i = 0 ; i < j; ++i) {
        if (i == 0 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
    }

    ll ans = 0;
    for (i = 0, j = 1; i < (int) disc.size(); ++i) {
        while (j <= n && itv[j].first == disc[i]) {
            st.insert(itv[j].second);
            ++j;
        }

        int x = st.size();
        if (x >= k) {
            ans = (ans + C(x, k)) % mod;
        }

        st.erase(disc[i]);

        if (i != (int) disc.size() - 1) {
            x = st.size();
            if (x >= k) {
                int l = disc[i] + 1, r = disc[i+1] - 1;
                if (r >= l) {
                    ans = (ans + C(x, k) * (r - l + 1)) % mod;
                }   
            }
        }
    }

    printf("%I64d\n", ans);
    return 0;
}