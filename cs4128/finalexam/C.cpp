#include <bits/stdc++.h>
#define MAX_SIZE 100111
typedef long long ll;
using namespace std;

struct edge {
	int s, e;
	ll w;
};

int selected[MAX_SIZE];
edge edg[MAX_SIZE];

int f[MAX_SIZE];

int n;

void preprocess() {
	int i;
	for (i = 1; i <= n; i++) {
		f[i] = i;
	}
}

int find(int x) {
	if (f[x] == x) return x;
	return f[x] = find(f[x]);
}

void unionset(int a, int b) {
	int x = find(a), y = find(b);
	f[x] = y;
}

static bool cmp(const edge &a, const edge &b) {
	return a.w < b.w;
}

int main() {
	int m, k, i;
	scanf("%d%d%d", &n, &m, &k);	
	preprocess();
	for (i = 1; i <= m; i++) {
		int a, b;
		ll c;
		scanf("%d%d%lld", &a, &b, &c);
		edg[i] = edge{a, b, c};
	}
	
	sort(edg+1, edg+m+1, cmp);
	
	ll ans = 0;
	for (i = 1; i <= m; i++) {
		if (find(edg[i].s) != find(edg[i].e)) {
			selected[i] = 1;
			ans += edg[i].w;
			unionset(edg[i].s, edg[i].e);
		}
	}
	
	if (k == 2) {
		for (i = m; i >= 1; i--) {
			if (selected[i]) {
				ans -= edg[i].w;
				break;
			}
		}
	}
	
	cout << ans << endl;
	return 0;
}
