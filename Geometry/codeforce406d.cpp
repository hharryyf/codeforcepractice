#include <bits/stdc++.h>
#define MAX_SIZE 101111
using namespace std;
typedef long long ll;
struct point {
	ll x, y;
};

typedef point Vector;
Vector operator -(Vector v1, Vector v2) {
	return Vector{v1.x - v2.x, v1.y - v2.y};
}

ll cross(Vector v1, Vector v2) {
	return v1.x * v2.y - v1.y * v2.x;
}

point p[MAX_SIZE];
int hull[MAX_SIZE];
int n;
vector<int> g[MAX_SIZE];
int height[MAX_SIZE], parent[MAX_SIZE][18];

void dfs(int v, int pre) {
	height[v] = height[pre] + 1;
	parent[v][0] = pre;
	int i;
	for (i = 1 ; i <= 16; ++i) {
		parent[v][i] = parent[parent[v][i-1]][i-1];
	}
	
	for (auto nv : g[v]) {
		if (nv != pre) {
			dfs(nv, v);
		}
	}
}

int LCA(int u, int v) {
	if (height[u] < height[v]) swap(u, v);
	int i;
	for (i = 16; i >= 0; --i) {
		if (height[u] - (1 << i) >= height[v]) {
			u = parent[u][i];
		}
	}
	
	if (u == v) return u;
	for (i = 16; i >= 0; --i) {
		if (parent[u][i] != parent[v][i]) {
			u = parent[u][i];
			v = parent[v][i];
		}
	}
	
	return parent[u][0];
}

int main() {
	int i, sz = 0;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) {
		scanf("%I64d%I64d", &p[i].x, &p[i].y);
	}
	
	for (i = n; i >= 1; --i) {
		while (sz >= 2 && (cross(p[hull[sz-1]] - p[i], p[hull[sz-2]] - p[i]) > 0)) --sz;
		hull[sz++] = i;
		if (sz >= 2) {
			g[hull[sz-2]].push_back(hull[sz-1]);
			// cout << "edge " << hull[sz-2] << " " << hull[sz-1] << endl;
		}
	}
	
	dfs(n, 0);
	
	int q;
	scanf("%d", &q);
	while (q > 0) {
		int u, v;
		scanf("%d%d", &u, &v);
		printf("%d ", LCA(u, v));
		--q;
	}
	printf("\n");
	return 0;
}