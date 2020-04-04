#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	priority_queue<ll, vector<ll>, greater<ll>> q;
	int n;
	scanf("%d", &n);
	while (n > 0) {
		int v;
		scanf("%d", &v);
		q.push(v);
		--n;
	}
	
	int sz = q.size();
	if (sz % 2 == 0) q.push(0);
	ll cost = 0;
	while ((int) q.size() >= 2) {
		if ((int) q.size() >= 3) {
			ll d = 0;
			d += q.top();
			q.pop();
			d += q.top();
			q.pop();
			d += q.top();
			q.pop();
			cost += d;
			q.push(d);
		} else {
			ll d = 0;
			d += q.top();
			q.pop();
			d += q.top();
			q.pop();
			cost += d;
			q.push(d);
		}
	}
	
	cout << cost << endl;
	return 0;
}