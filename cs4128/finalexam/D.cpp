#include <bits/stdc++.h>
#define MAX_SIZE 500111
typedef long long ll;
using namespace std;

int visited[MAX_SIZE];

ll cnt[MAX_SIZE];

int main() {
	ll ans = 0;
	
	int b, f, i, j;
	cin >> b >> f;
	for (i = 1; i <= b; i++) {
		ll ci;
		int si;
		scanf("%lld%d", &ci, &si);
		cnt[si] += ci;
	}
	
	for (i = 1; i <= f; i++) {
		int v;
		scanf("%d", &v);
		if (!visited[v]) {
			for (j = 1; j * v <= 500001; j++) {
				ans += cnt[v * j];
				cnt[v * j] = 0;
			}
			visited[v] = 1;
		}
	}
	
	cout << ans << endl;
	return 0;
}
