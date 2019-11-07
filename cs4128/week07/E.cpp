#include <bits/stdc++.h>
#define MAX_SIZE 1048596

typedef long long ll;
using namespace std;

/*
	dp[i] = x[i] * y[i] - a[i] + max(dp[j] - x[j] * y[i])	
*/

struct line {
	long long m, b;
};

long long floordiv ( long long a, long long b) {
	return a / b - (a%b && ((a <0) ^ (b <0) )) ;
}

long long intersect ( line a, line b) {
	return floordiv (b.b - a.b, a.m - b.m);
}

vector<line> cht;

void insert(line l) {
	auto n = cht.size();
	while (n >= 2 && intersect(cht[n-1], cht[n-2]) >= intersect(cht[n-1], l)) {
		cht.pop_back();
		n = cht.size();
	}
	cht.push_back(l);
}

long long query(long long x) {
	int low = 0, high = (int) cht.size() - 2;
	int ret = (int) cht.size() - 1;
	while (low <= high) {
		int mid = low + (high - low) / 2;
		if (intersect(cht[mid], cht[mid + 1]) >= x) {
			ret = mid;
			high = mid - 1;
		} else {
			low = mid + 1;
		}
	}
	
	return cht[ret].m * x + cht[ret].b;
}

struct rec {
	ll x, y, a;
};

rec rts[MAX_SIZE];

static bool cmp(rec &a, rec &b) {
	return a.x < b.x;
}

ll dp[MAX_SIZE];

int main() {
	int i, n;
	scanf("%d", &n);
	for (i = 1 ; i <= n; i++) {
		scanf("%lld%lld%lld", &rts[i].x, &rts[i].y, &rts[i].a);
	}	
	
	sort(rts + 1, rts + n + 1, cmp);
	ll ans = 0ll;
	dp[0] = 0;
	insert(line{0, 0});
	for (i = 1; i <= n; i++) {
		
		dp[i] = query(-rts[i].y) + rts[i].x * rts[i].y - rts[i].a;
		insert(line{rts[i].x, dp[i]});
		// cout << dp[i] << endl;
		ans = max(ans, dp[i]);
	}
	
	cout << ans << endl;
	return 0;
}
