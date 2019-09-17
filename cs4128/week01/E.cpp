#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#define MAX_SIZE 1501
#define MAX_VAL 1000000000000ll
typedef long long ll;
using namespace std;
/*
	t = 5 n = 4
	0 4 5 6 7 8
	
	t = 5
	0 1 2 3 4 5 6
	
	0 1 2 3 4 5 6
*/
ll arr[MAX_SIZE];

int main() {
	int T, n, m, t, i, j;
	scanf("%d", &T);
	while (T > 0) {
		scanf("%d%d%d", &n, &t, &m);
		for (i = 1; i <= m; i++) {
			scanf("%lld", &arr[i]);
		}
		
		vector<ll> dp = vector<ll>(m + 1, MAX_VAL);
		vector<ll> cnt = vector<ll>(m + 1, MAX_VAL);
		dp[0] = 0;
		dp[1] = 2 * t + arr[1];
		cnt[0] = 0;
		cnt[1] = 1;
		for (i = 1; i <= m; i++) {
			j = i;
			while (j > 0 && j > i - n) {
				// last window is [j, i]
				if (dp[j-1] <= arr[i]) {
					if (dp[i] >= arr[i] + 2 * t) {
						dp[i] = arr[i] + 2 * t;
						cnt[i] = min(cnt[j-1] + 1, cnt[i]);
					}
				} else {
					if (dp[i] >= dp[j-1] + 2 * t) {
						dp[i] = dp[j-1] + 2 * t;
						cnt[i] = min(cnt[j-1] + 1, cnt[i]);
					}
				}
				j--;
			}
			
		}
		
		cout << dp[m] - t << " " << cnt[m] << endl;
		T--;
	}
	return 0;
}
