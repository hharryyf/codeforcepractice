#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 200011
typedef long long ll;
using namespace std;

struct line { 
	ll m, b; 
};

ll floordiv ( ll a, ll b) {
	return a / b - (a%b && ((a <0) ^ (b <0))) ;
}

ll intersect (line a, line b) {
	return floordiv (b.b - a.b, a.m - b.m);
}

vector <line > cht ;
void add ( line l) {
	auto n = cht.size() ;
	while (n >= 2 && intersect(cht[n - 1] , cht[n - 2]) >= intersect(cht[n - 1] , l)) {
		cht.pop_back() ;
		n = cht.size() ;
	}
	cht.push_back (l);
}

ll query (ll x) {
	int lo = 0; int hi = cht.size () -2;
	int idx = cht.size() -1;
	while (lo <= hi) {
		int mid = (lo+hi) /2;
		// NOTE : It is critical here that this is >= not >.
		if (intersect(cht[mid], cht[mid +1]) >= x) {
			idx = mid ; 
			hi = mid -1;
		} else { 
			lo = mid + 1; 
		}
	}
	return cht[idx].m * x + cht[idx].b;
}

ll a[MAX_SIZE];
ll pref[MAX_SIZE];

int main() {
    int i, n;
    ll ans = 0;
    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        ans += 1ll * a[i] * i;
        pref[i] = pref[i-1] + a[i];
    }
    
    ll delta = 0;
    add(line{-n, -pref[n]});
    for (i = n - 1; i >= 1; i--) {
        delta = max(delta, query(-a[i]) + pref[i] - 1ll * a[i] * i);
        add(line{-i, -pref[i]});
    }
    
    cht.clear();
    
    for (i = 2; i <= n; i++) {
        add(line{i-1, -pref[i-2]});
        delta = max(delta, query(a[i]) - 1ll * a[i] * i + pref[i-1]);
    }
    printf("%lld\n", ans + delta);
    return 0;
}
