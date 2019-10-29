#include <bits/stdc++.h>
#define INF 1e15
typedef long long ll;
using namespace std;
int n;
char s[100011];

ll cnt[100011][4];
ll x1, x2, y11, y2;
/* U is 0, D is 1, L is 2, R is 3 */
bool valid(ll day) {
	ll du = cnt[day % n][0] + (1ll) * (day / n) * cnt[n][0];
	ll dd = cnt[day % n][1] + (1ll) * (day / n) * cnt[n][1];
	ll dl = cnt[day % n][2] + (1ll) * (day / n) * cnt[n][2];
	ll dr = cnt[day % n][3] + (1ll) * (day / n) * cnt[n][3];	
	ll tx = x1 + dr - dl;
	ll ty = y11 + du - dd;
	return (abs(tx - x2) + abs(ty - y2) <= day);
}

int main() { 
	
	scanf("%lld%lld%lld%lld", &x1, &y11, &x2, &y2);
	cin >> n;
	scanf("%s", s);
	
	int i;
	for (i = 1; i <= n; i++) {
		cnt[i][0] = cnt[i-1][0] + (s[i-1] == 'U');
		cnt[i][1] = cnt[i-1][1] + (s[i-1] == 'D');
		cnt[i][2] = cnt[i-1][2] + (s[i-1] == 'L');
		cnt[i][3] = cnt[i-1][3] + (s[i-1] == 'R');
	}
	
	ll ans = INF;
	ll low = 0ll, high = ans;
	while (low <= high) {
		ll mid = low + (high - low) / 2;
		if (valid(mid)) {
			ans = min(ans, mid);
			high = mid - 1;
		} else {
			low = mid + 1;
		}
	}
	if (ans < INF) {
		cout << ans << endl;
	} else {
		cout << -1 << endl;
	}
	return 0;
}
