#include <bits/stdc++.h>
typedef long long ll;

#define MAX_SIZE 20011
using namespace std;

int n;

ll dp[MAX_SIZE];

// cost[i] refers to the cost of all cars to get to point i
ll cost[MAX_SIZE];

ll pref[MAX_SIZE];

ll dist[MAX_SIZE];

ll extra(int i) {
	ll ret = cost[n+1] - cost[i] - pref[i] * (dist[n+1] - dist[i]); 
	// cout << i << " " << ret << endl;
	return ret;
}


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

int main() {
	dist[1] = 0;
	int i;
	scanf("%d", &n);
	if (n == 0 || n == 1) {
		cout << 0 << endl;
		return 0;
	}
	for (i = 1; i <= n; i++) {
		ll v, p;
		scanf("%lld%lld", &v, &p);
		dist[i+1] = dist[i] + p;
		pref[i] = pref[i-1] + v;
	}
	
	for (i = 2; i <= n + 1; i++) {
		cost[i] = cost[i-1] + pref[i-1] * (dist[i] - dist[i-1]);
		// cout << i << " cost= " << cost[i] << endl;
	}
	
	// ret = extra[i] + cost[i] - max(pref[j] * x[i] - pref[j] * x[j])
	ll ret = extra(1);
	// an update of 1
	insert(line{pref[1], -pref[1] * dist[1]});
	for (i = 2; i <= n; i++) {
		ret = min(ret, extra(i) + cost[i] - query(dist[i]));
		insert(line{pref[i], -pref[i] * dist[i]});
	}
	
	printf("%lld\n", ret);
	return 0;
}
