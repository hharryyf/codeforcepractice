#include <bits/stdc++.h>
#define MAX_SIZE 101111

typedef long long ll;
using namespace std;



struct rect {
	ll x, y;
};

vector<rect> rec;

static bool cmp(rect &a, rect &b) {
	if (a.x == b.x) {
		return a.y < b.y;
	}
	return a.x < b.x;
}

int n;

ll dp[MAX_SIZE];

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
	scanf("%d", &n);
	int i;
	for (i = 0 ; i < n; i++) {
		int w, d;
		scanf("%d%d", &w, &d);
		rec.push_back(rect{w, d});
	}
	
	sort(rec.begin(), rec.end(), cmp);
	
	vector<rect> a;
	for (i = 0 ; i < n; i++) {
		while (!a.empty()) {
			int k = (int) a.size() - 1;
			if (a[k].y > rec[i].y) {
				break;
			}
			a.pop_back();
		}
		a.push_back(rec[i]);
	}
	
	
	/* 
		Then the problem is changed to a very simple and naive dp problem,
		dp[i] = min(dp[j-1] + a[i].x * a[j].y, 1 <= j <= i)
	*/
	
	dp[0] = 0;
	insert(line{a[0].y, 0});
	for (i = 1; i <= (int) a.size(); i++) {
		dp[i] = query(a[i-1].x);
		if (i < (int) a.size()) {
			insert(line{a[i].y, dp[i]});
		}
		// cout << dp[i] << endl;
	}
	
	cout << dp[(int) a.size()] << endl;
	return 0;
}
