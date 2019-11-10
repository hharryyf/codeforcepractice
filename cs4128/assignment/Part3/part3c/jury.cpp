#include <bits/stdc++.h>
#define MAX_SIZE 1024
using namespace std;

pair<int, int> pt[MAX_SIZE];

int main() {
	int n, q;
	scanf("%d%d", &n, &q);
	int i;
	for (i = 1; i <= n; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		pt[i].first = x, pt[i].second = y;
	}
	
	for (i = 1; i <= q; i++) {
		int l, r, dn, up;
		scanf("%d%d%d%d", &l, &r, &dn, &up);
		int j;
		int ans = 0;
		for (j = 1; j <= n; j++) {
			if (pt[j].first <= r && pt[j].first >= l && pt[j].second <= up && pt[j].second >= dn) {
				ans = 1;
				break;
			}
		}
		cout << ans << endl;
	}
	
	return 0;
}
