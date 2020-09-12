#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

vector<int> vc;

int main() {
	int i = 0, tp, v, Q;
	ll sm = 0;
	double ans = 0.0;
	scanf("%d", &Q);
	while (Q-- > 0) {
		scanf("%d", &tp);
		if (tp == 1) {
			scanf("%d", &v);
			vc.push_back(v);
			if ((int) vc.size() == 1) {
				sm += v;
			} else {
				ll curr = sm + vc.back();
				ans = max(ans, 1.0 * vc.back() - 1.0 * curr / (i + 2));
				while (i + 2 < (int) vc.size()) {
					ll curr = sm + vc[i + 1] + vc.back();
					if (1.0 * vc.back() - 1.0 * curr / (i + 3) > ans) {
						sm += vc[i + 1];
						ans = 1.0 * vc.back() - 1.0 * curr / (i + 3);
						++i;
					} else {
						break;
					}
				}
			}
			// cout << "i= " << i << endl;
			// cout << ans << endl;
		} else {
			printf("%.10lf\n", ans);
		}
	}
	return 0;
}
