#include <bits/stdc++.h>
#define MAX_SIZE (262145 + 11)
using namespace std;

vector<int> graph[MAX_SIZE];

int dfsord[MAX_SIZE];
int height[MAX_SIZE];
int pos[MAX_SIZE];
int tree[MAX_SIZE << 2];
vector<int> tour;
int k = 0;

void dfs(int v, int p, int h) {
	dfsord[v] = k++;
	pos[v] = (int) tour.size();
	height[v] = h;
	tour.push_back(v);
	for (auto nextv : graph[v]) {
		if (nextv != p) {
			dfs(nextv, v, h + 1);
			tour.push_back(v);
		}
	}
}

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index] = tour[l];
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	tree[index] = 
	(dfsord[tree[index * 2]] < dfsord[tree[index * 2 + 1]] ? tree[index * 2] : tree[index * 2 + 1]);
}

int query(int start, int end, int l, int r, int index) {
	if (start > end || l > r || l > end || start > r) return -1;
	if (start <= l && r <= end) return tree[index];
	int mid = l + (r - l) / 2;
	int t1 = query(start, end, l, mid, index * 2);
	int t2 = query(start, end, mid + 1, r, index * 2 + 1);
	if (t1 == -1) return t2;
	if (t2 == -1) return t1;
	return dfsord[t1] < dfsord[t2] ? t1 : t2;
}

int LCA(int v1, int v2) {
	int t1 = pos[v1], t2 = pos[v2];
	if (t1 > t2) swap(t1, t2);
	return query(t1, t2, 0, (int) tour.size() - 1, 1);
}

// get the ans when choosing s->f and t->f
int getans(int s, int t, int f) {
	int v1 = LCA(s, f);
	int v2 = LCA(s, t);
	int v3 = LCA(f, t);
	int d_sf = height[s] + height[f] - 2 * height[v1];
	int d_st = height[s] + height[t] - 2 * height[v2];
	int d_ft = height[f] + height[t] - 2 * height[v3];
	int ret = 1 + max((d_sf + d_st - d_ft), max((d_sf + d_ft - d_st), (d_st + d_ft - d_sf))) / 2;
	return ret;
}

int main(int argc, char *argv[]) {
	int n, q;
	scanf("%d%d", &n, &q);
	for (int i = 2; i <= n; i++) {
		int v;
		scanf("%d", &v);
		graph[v].push_back(i);
		graph[i].push_back(v);
	}
	
	dfs(1, -1, 0);
	
	build(0, (int) tour.size() - 1, 1);
	
	while (q > 0) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		printf("%d\n", getans(a,b,c));
		q--;
	}
	return 0;
}
