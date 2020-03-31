#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 1011
#define REP(i,a,b) for(i=a;i<=b;++i)
using namespace std;

struct edge {
	int from, to, w, id;
	bool operator < (edge other) const {
		return w > other.w;
	}
};

int f[MAX_SIZE << 1];
int n, m, q;
void init() {
	int i;
	REP(i, 1, 2*n) f[i] = i;
}

int find(int x) {
	return f[x] == x ? x : f[x] = find(f[x]);
}

void unionset(int x, int y) {
	x = find(x), y = find(y);
	f[x] = y;
}

edge edg[MAX_SIZE * MAX_SIZE];

int main() {
	int i, l, r;
	scanf("%d%d%d", &n, &m, &q);
	REP(i, 1, m) {
		scanf("%d%d%d", &edg[i].from, &edg[i].to, &edg[i].w);
		edg[i].id = i;
	}
	
	sort(edg + 1, edg + 1 + m);
	
	while (q > 0) {
		init();
		scanf("%d%d", &l, &r);
		int ans = -1;
		REP(i, 1, m) {
			if (edg[i].id > r || edg[i].id < l) continue;
			int x = find(edg[i].from), y = find(edg[i].to);
			if (x == y) {
				ans = edg[i].w;
				break;
			}
			unionset(edg[i].from, edg[i].to + n);
			unionset(edg[i].to, edg[i].from + n);
		}
		printf("%d\n", ans);
		--q;
	}
	return 0;
}