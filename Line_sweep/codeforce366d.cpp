#include <bits/stdc++.h>
#define MAX_SIZE 1011
using namespace std;

struct edge {
	int from, to, l, r;
	bool operator < (edge other) const {
		return r < other.r;
	}
};

static bool cmp(const edge &a, const edge &b) {
	return a.l < b.l;
}

vector<edge> st;
int f[MAX_SIZE];
edge edg[MAX_SIZE << 2];

void init() {
	int i;
	for (i = 1; i < MAX_SIZE; ++i) f[i] = i;
	st.clear();
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
	int ans = -1;
	int n, m, i, j;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= m; ++i) {
		scanf("%d%d%d%d", &edg[i].from, &edg[i].to, &edg[i].l, &edg[i].r);
	}
	
	sort(edg + 1, edg + 1 + m, cmp);
	
	for (i = 1; i <= m; ++i) {
		init();
		for (j = 1; j <= i; ++j) {
			if (edg[j].r >= edg[i].l) {
				st.push_back(edg[j]);
			}
		}
	
		sort(st.begin(), st.end());
		
		int sz = st.size();
		for (j = sz - 1; j >= 0; --j) {
			unionset(st[j].from, st[j].to);
			//cout << i << endl;
			//cout << "union " << st[j].from << " " << st[j].to << endl;
			if (find(1) == find(n)) {
				ans = max(ans, st[j].r - edg[i].l + 1);
				//cout << edg[i].l << " " << edg[j].r << endl;
				break;
			}
		}
	}
	
	if (ans > 0) {
		printf("%d\n", ans);
	} else {
		printf("Nice work, Dima!\n");
	}
	return 0;
}