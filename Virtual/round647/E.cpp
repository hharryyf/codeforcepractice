#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1000000007;
const ll N = 1000100;
ll t, p, k[N];
int n;

ll qpow(ll x, ll pw) {
	ll ret = 1;
	while (pw) {
		if (pw & 1) ret = (ret * x) % mod;
		x = (x * x) % mod;
		pw >>= 1;
	}
	return ret;
}

int main() {
	int T;
    scanf("%d", &T);
	while (T--) {
		map<int, int> pcnt;
        scanf("%d%I64d", &n, &p);
		for (int i = 1; i <= n; i++) {
			scanf("%I64d", &k[i]);
            pcnt[k[i]] += 1;
		}

		if (p == 1) {
			cout << (n % 2) << endl;
			continue;
		}

		ll mpow = 1;
		ll at = n;
		while (at > p) {
			at /= p;
			mpow += 1;
		}

		bool ok = false;
		ll pre = N, debt = 0;
		for (auto iter = pcnt.rbegin(); iter != pcnt.rend(); ++iter) {
            ll x = iter->first;
			ll y = iter->second;
			ll moves = pre - x;
			pre = x;
            // the sum of later powers cannot make up debt
			if ((debt && moves >= mpow) || (debt * qpow(p, moves) > n)) {
				debt *= qpow(p, moves);
				ll ans = (debt * qpow(p, x)) % mod;
				for (auto it = iter; it != pcnt.rend(); ++it) {
					ans -= (it->second * qpow(p, it->first)) % mod;
					if (ans < 0) ans += mod;
				}
				ok = true;
				printf("%I64d\n", ans);
                break;
			}

			debt *= qpow(p, moves);
			if (y >= debt) {
				debt = (y - debt) % 2;
			} else {
				debt -= y;
			}
		}

		debt *= qpow(p, pre);
		debt %= mod;
		if (!ok) {
            printf("%I64d\n", debt);
		}
	}

    return 0;
}
