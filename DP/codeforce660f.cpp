#include <bits/stdc++.h>
#define MAX_SIZE 200111
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

ll arr[MAX_SIZE];
ll s[MAX_SIZE], pref[MAX_SIZE];

int main() {
	ll ret = 0;
	int i, n;
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		scanf("%lld", &arr[i]);
		s[i] = s[i-1] + arr[i] * ((ll) i);
		pref[i] = pref[i-1] + arr[i];
	}
	
	/*
		We consider term by term, let ans[i] be the answer with i as the end element
	*/
	
	add(line{0,0});
	
	for (i = 1; i <= n; i++) {
		ret = max(ret, s[i] + query(-pref[i]));
		add(line{i, pref[i] * i - s[i]});
	}
	
	printf("%lld\n", ret);
	return 0;
}
