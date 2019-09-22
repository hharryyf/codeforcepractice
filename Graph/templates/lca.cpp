#include <bits/stdc++.h>
#define MAX_SIZE (262145 + 11)
using namespace std;

vector<int> graph[MAX_SIZE];

// pos[i] refers to the first occurence of 
// dfsord[i] in the euler tour 
int pos[MAX_SIZE];
// dfsord[i] refers to the dfsorder ot the ith node 
int dfsord[MAX_SIZE];
vector<int> tour;
int k = 0;
// problem statement: give a tree with n (n <= 100,000) vertices and q (q <= 100,000)
// queries (v1i, v2i), return q numbers which represent ans_i = lca(v1i, v2i). 
// let node 1 to be the root of the tree

int tree[MAX_SIZE << 1];

void dfs(int v, int p) {
	dfsord[v] = k++;
	pos[v] = tour.size();
	tour.push_back(v);
	for (auto nextv : graph[v]) {
		if (nextv != p) {
			dfs(nextv, v);
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
	if (start > end || l > r || start > r || l > end) return -1;
	if (start <= l && r <= end) return tree[index];
	int mid = l + (r - l) / 2;
	int t1 = query(start, end, l, mid, index * 2);
	int t2 = query(start, end, mid + 1, r, index * 2 + 1);
	if (t1 == -1) return t2;
	if (t2 == -1) return t1;
	return (dfsord[t1] < dfsord[t2] ? t1 : t2);
}

int LCA(int v1, int v2) {
	int t1 = pos[v1], t2 = pos[v2];
	if (t1 > t2) {
		swap(t1, t2);
	}
	
	return query(t1, t2, 0, (int) tour.size() - 1, 1);
}

int main(int argc, char *argv[]) {
	int n, q, i;
	scanf("%d%d", &n, &q);
	
	for (i = 0 ; i < n - 1; i++) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		graph[v1].push_back(v2);
		graph[v2].push_back(v1);
	}
	
	dfs(1, -1);
	
	build(0, (int) tour.size() - 1, 1);
	
	while (q > 0) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		printf("%d\n", LCA(v1, v2));
		q--;
	}
	return 0;
}
