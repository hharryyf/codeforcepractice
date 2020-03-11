#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 500011
using namespace std;

// a is the original defensive strength array
// cnt is the duplicated array that is reset in
// each time of the validation procedure
ll a[MAX_SIZE], cnt[MAX_SIZE];
// k is the number of additional archers
ll k;
int n, r;
// validate whether this amount of strength is satisfiable
bool valid(ll strength) {
	ll rsum = 0;
	ll rem = k;
	int i, j;
	for (i = 1; i <= n; ++i) cnt[i] = a[i];
	// we need to maintain a window of sum [i-r, i+r]
	for (i = 1, j = 1; i <= n; ++i) {
		while (j <= i + r && j <= n) {
			rsum += cnt[j];
			j++;
		}
		
		if (i > r + 1) rsum -= cnt[i - r - 1];
		if (strength - rsum > rem) return false;
		if (strength > rsum) {
			int idx = min(n, i + r);
			cnt[idx] += strength - rsum;
			rem -= strength - rsum;
			rsum = strength;
		}
	}
	
	return true;
}

int main() {
	int i;
	scanf("%d%d%I64d", &n, &r, &k);
	for (i = 1; i <= n; ++i) scanf("%I64d", &a[i]);
	
	ll low = 0, high = 2e18;
	ll ans = 0;
	while (low <= high) {
		ll mid = low + (high - low) / 2;
		if (valid(mid)) {
			ans = mid;
			low = mid + 1;
		} else {
			high = mid - 1;
		}
	}
	
	printf("%I64d\n", ans);
	return 0;
}