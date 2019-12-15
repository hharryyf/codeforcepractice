#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll t, n, a, b, k;

int main() {
	scanf("%lld%lld%lld%lld%lld", &t, &n, &a, &b, &k);
	ll la = 0, lb = 0;
	la = n / 2, lb = n / 2;
	if (n % 2 == 1) {
		la++;
	}
	
	ll low = 0, high = t;
	ll ret = 0;
	while (low <= high) {
		ll mid = low + (high - low) / 2;
		if (la * min(a, mid) + lb * min(b, mid) >= k * mid) {
			low = mid + 1;
			ret = mid;
		} else {
			high = mid - 1;
		}
	}
	
	printf("%lld\n", ret);
	return 0;
}
