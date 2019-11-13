#include <bits/stdc++.h>
#define MAX_SIZE 100011
#define MOD 1000000007
using namespace std;

typedef long long ll;

ll p2[MAX_SIZE];

ll arr[MAX_SIZE];

void precompute() {
	int i;
	p2[0] = 1;
	for (i = 1 ; i <= 100001; i++) {
		p2[i] = p2[i-1] * 2;
		p2[i] %= MOD;
	}
}

int main() {
	precompute();
	int T;
	scanf("%d", &T);
	while (T > 0) {
		int n;
		int i;
		scanf("%d", &n);
		for (i = 0 ; i < n; i++) {
			scanf("%lld", &arr[i]);
		}
		
		sort(arr, arr + n);
		
		ll ans = 0;
		
		for (i = 0 ; i < n; i++) {
			int ft = i;
			int bk = n - i - 1;
			ans = ans + ((arr[i] * (p2[ft] - p2[bk])) % MOD + MOD) % MOD;
			// cout << ft << " -- " << p2[ft] << endl;
			// cout << bk << " -- " << p2[bk] << endl;
			// cout << arr[i] << "..." << ans << endl;
			ans = ans % MOD;
		}
		
		cout << ans << endl;
		T--;
	}
	return 0;
}
