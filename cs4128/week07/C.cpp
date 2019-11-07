#include <bits/stdc++.h>
#define MAX_SIZE 100011

using namespace std;

long long dp[MAX_SIZE];
long long cost[MAX_SIZE];
long long height[MAX_SIZE];
/*
	dp[1] = 0
	dp[i] = max(dp[j] + a[i] * b[j], 1 <= j < i)
	return dp[n]
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
	
int main() {
	int n;
	scanf("%d", &n);
	int i;
	for (i = 1; i <= n; i++) {
		cin >> height[i];
	}
	
	for (i = 1; i <= n; i++) {
		cin >> cost[i];
	}
	
	dp[1] = 0;
	
	insert(line{cost[1], dp[1]});
	
	for (i = 2; i <= n; i++) {
		dp[i] = query(height[i]);
		insert(line{cost[i], dp[i]});
	}
	
	cout << dp[n] << endl;
	return 0;
}
