#include <bits/stdc++.h>
#define MAX_SIZE 100111
using namespace std;

// the remaining edges (black,white)->weight
vector<pair<int, int>> rem;
vector<int> rb, rw;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> wt, blk;

int main() {
	int n, i;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) {
		int cl, v;
		scanf("%d%d", &cl, &v);
		if (cl == 0) {
			wt.push(make_pair(v, i));
		} else {
			blk.push(make_pair(v, i));
		}
	}
	
	while (!wt.empty() && !blk.empty()) {
		auto p1 = wt.top(), p2 = blk.top();
		wt.pop(), blk.pop();
		if (p1.first < p2.first) {
			printf("%d %d %d\n", p1.second, p2.second, p1.first);
			blk.push(make_pair(p2.first - p1.first, p2.second));
		} else if (p1.first > p2.first) {
			printf("%d %d %d\n", p1.second, p2.second, p2.first);
			wt.push(make_pair(p1.first - p2.first, p1.second));
		} else {
			rem.emplace_back(p2.second, p1.second);
			printf("%d %d %d\n", p1.second, p2.second, p1.first);
		}
	}
	
	while (!wt.empty()) {
		rw.push_back(wt.top().second);
		wt.pop();
	}
	
	while (!blk.empty()) {
		rb.push_back(wt.top().second);
		blk.pop();
	}
	
	int tp = 0;
	if (rb.size() != 0) {
		// top is a white node
		tp = rem[0].second;
		for (i = 1; i < (int) rem.size(); ++i) {
			printf("%d %d %d\n", tp, rem[i].first, 0);
		}
		for (auto v : rb) {
			printf("%d %d %d\n", tp, v, 0);
		}
	} else {
		tp = rem[0].first;
		for (i = 1; i < (int) rem.size(); ++i) {
			printf("%d %d %d\n", tp, rem[i].second, 0);
		}
		for (auto v : rw) {
			printf("%d %d %d\n", tp, v, 0);
		}
	}
	return 0;
}