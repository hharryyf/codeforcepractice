#include <bits/stdc++.h>

using namespace std;

/*
	2 things must be considered
	1. can we firstly use up all the operation a, then start operation b
		answer is yes, otherwise we would waste one operation b
	2. what should be the best candidate for operation a
		only one hp should use all operation a.
		
*/

typedef long long Long;

vector<pair<Long, Long> > p;

static bool cmp(const pair<Long, Long> p1, const pair<Long, Long> p2) {
	return (p1.first - p1.second) > (p2.first - p2.second);
}

int main(int argc, char *argv[]) {
	Long n, a, b;
	cin >> n >> a >> b;
	int i;

	p = vector<pair<Long, Long> >();
	for (i = 0 ; i < n; i++) {
		Long t1, t2;
		cin >> t1 >> t2;
		p.push_back(pair<Long, Long>(t1, t2));
	}
	
	sort(p.begin(), p.end(), cmp);
	/*
	for (i = 0 ; i < n; i++) {
		cout << p[i].first << " " << p[i].second << endl;
	}*/
	
	Long ans = 0ll;
	
	if (b == 0) {
		for (i = 0 ; i < n; i++) {
			ans += p[i].second;
		}
		
		cout << ans << endl;
		return 0;
	}
	
	for (i = 0 ; i < min(b, n); i++) {
		ans += max(p[i].first, p[i].second);
	}
	
	for (i = b; i < n; i++) {
		ans += p[i].second;
	}
	
	Long ret = ans;
	// cout << ans << endl;
	b = min(b, n);
	for (i = 0 ; i < n; i++) {
		Long tmp = ans;
		if (i < b) {
			tmp -= max(p[i].first, p[i].second);
			tmp += max(p[i].first * (1 << a), p[i].second);
		} else {
			tmp -= p[i].second;
			tmp += p[i].first * (1 << a);
			tmp -= max(p[b-1].first, p[b-1].second);
			tmp += p[b-1].second;
		}
		
		ret = max(tmp, ret);
	}
	
	cout << ret << endl;
	return 0;
}
