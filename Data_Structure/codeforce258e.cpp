#include <bits/stdc++.h>
#define MAX_SIZE (262144 + 11)

using namespace std;

// an offline range cover problem
// this problem is a combination of codeforce1076e and codeforce610d
// a 1900 problem + 2300 problem result in a 2400 problem
typedef struct segt {
	int lazy, value;
} segmenttree;

segmenttree tree[MAX_SIZE];

int dfsorder[MAX_SIZE >> 1];
vector<int> graph[MAX_SIZE >> 1];
vector<int> qrs[MAX_SIZE >> 1];
int n, m;
int subsize[MAX_SIZE >> 1];
int k = 1;
int ans[MAX_SIZE >> 1];
// first depth-first-search, which would order the verticies in dfs order
// and find the subtree size
void dfs_0(int v, int prev);
void dfs(int v, int prev);
void update(int start, int end, int l, int r, int index, int val);

int main(int argc, char *argv[]) {
	scanf("%d%d", &n, &m);
	for (int i = 0 ; i < n - 1; i++) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		graph[v1].push_back(v2);
		graph[v2].push_back(v1);	
	}
	
	for (int i = 0 ; i < m; i++) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		qrs[v1].push_back(v2);
		qrs[v1].push_back(v1);
		qrs[v2].push_back(v1);
		qrs[v2].push_back(v2);
	}
	
	dfs_0(1, -1);
	
	dfs(1, -1);
	
	for (int i = 1; i <= n; i++) {
		printf("%d ", ans[i]);
	}
	cout << endl;
	return 0;
}

void dfs_0(int v, int prev) {
	subsize[v] = 1;
	dfsorder[v] = k++;
	for (auto nextv : graph[v]) {
		if (nextv != prev) {
			dfs_0(nextv, v);
			subsize[v] += subsize[nextv];
		}
	}
}

void dfs(int v, int prev) {
	for (auto nq : qrs[v]) {
		update(dfsorder[nq], dfsorder[nq] + subsize[nq] - 1, 1, n, 1, 1);
	}
	
	ans[v] = (tree[1].value > 0 ? tree[1].value - 1 : 0);
	for (auto nextv : graph[v]) {
		if (nextv != prev) {
			dfs(nextv, v);
		}
	}
	
	for (auto nq : qrs[v]) {
		update(dfsorder[nq], dfsorder[nq] + subsize[nq] - 1, 1, n, 1, -1);
	}
}

void update(int start, int end, int l, int r, int index, int val) {
	if (start > end || l > r || start > r || l > end) return;
	if (start <= l && r <= end) {
		tree[index].lazy += val;
		if (tree[index].lazy > 0) {
			tree[index].value = r - l + 1;	
		} else {
			if (l == r) {
				tree[index].value = 0;
			} else {
				tree[index].value = tree[index * 2].value + tree[index * 2 + 1].value;
			}
		}	
		return;
	}
	
	int mid = l + (r - l) / 2;
	update(start, end, l, mid, index * 2, val);
	update(start, end, mid + 1, r, index * 2 + 1, val);
	if (tree[index].lazy > 0) {
		tree[index].value = r - l + 1;	
	} else {
		if (l == r) {
			tree[index].value = 0;
		} else {
			tree[index].value = tree[index * 2].value + tree[index * 2 + 1].value;
		}
	}
}
