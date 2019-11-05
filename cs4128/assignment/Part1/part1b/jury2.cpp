#include <bits/stdc++.h>
typedef long long ll;

#define MAX_SIZE 2048

ll arr[MAX_SIZE][MAX_SIZE];

char str[4];

int main() {
	int n, q;
	int vs = 0;
	scanf("%d", &n);
	scanf("%d", &q);
	while (q > 0) {
		scanf("%s", str);
		if (str[0] == 'U') {
			int l, r;
			ll val;
			scanf("%d%d%lld", &l, &r, &val);
			for (int i = 1; i <= n; i++) {
				arr[vs+1][i] = arr[vs][i];
			}
			for (int i = l; i <= r; i++) {
				arr[vs+1][i] = val;
			}
			vs++;
		} else {
			int v, l, r;
			scanf("%d%d%d", &v, &l, &r);
			ll ret = 0;
			for (int i = l; i <= r; i++) {
				ret = ret + arr[v][i];
			}
			printf("%lld\n", ret);
		}
		q--;
	}
	return 0;
}
