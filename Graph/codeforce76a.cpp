#include <bits/stdc++.h>
#define MAX_SIZE 211
using namespace std;
typedef long long ll;

int f[MAX_SIZE];
ll G, S;
int n, m;
struct edge {
	int from, to;
	ll g, s;
	bool select;
	bool operator < (edge other) const {
		return g < other.g;
	}
};

edge edg[50011];

void init() {
	int i;
	for (i = 1; i < MAX_SIZE; ++i) f[i] = i;
}

int find(int x) {
	if (f[x] == x) return x;
	return f[x] = find(f[x]);
}

void unionset(int x, int y) {
	int a = find(x), b = find(y);
	f[a] = b;
}

int main() {
	int i, j;
	ll ans = 7e18;
	scanf("%d%d%I64d%I64d", &n, &m, &G, &S);
	for (i = 1; i <= m; ++i) {
		scanf("%d%d%I64d%I64d", &edg[i].from, &edg[i].to, &edg[i].g, &edg[i].s);
		edg[i].select = false;
	}
	
	sort(edg + 1, edg + 1 + m);
	vector<edge> ret;
	// the current cost is edg[i].g * G + S * max_S_in_MST
	for (i = 1; i <= m; ++i) {
		init();
		int cnt = 0;
		ll high = 0;
		ret.push_back(edg[i]);
		j = (int) ret.size() - 1;
		while (j > 0 && ret[j].s < ret[j-1].s) {
			swap(ret[j-1], ret[j]);
			j--;
		}
		for (j = 0 ; j < (int) ret.size(); ++j) {
			auto e = ret[j];
			// cout << e.from << " " << e.to << endl;
			if (find(e.from) != find(e.to)) {
				cnt++;
				unionset(e.from, e.to);
				high = e.s;
				ret[j].select = true;
			} 
		}
		
		// cout << i << "  " << cnt << endl;
		if (cnt == n - 1) {
			ans = min(ans, edg[i].g * G + S * high);
		}
		
		vector<edge> r;
		for (auto e : ret) {
			if (e.select) {
				r.push_back(e);
			}
		}
		
		ret.clear();
		for (auto &e : r) {
			e.select = false;
			ret.push_back(e);
		}
	}
	
	if (ans < 7e18) {
		printf("%I64d\n", ans); 
	} else {
		printf("-1\n");
	}
	return 0;
}