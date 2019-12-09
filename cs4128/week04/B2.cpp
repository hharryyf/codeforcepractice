#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define MAX_SIZE 524312

typedef tree <int, null_type, less <int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

ordered_set rt[MAX_SIZE];

vector<int> g[MAX_SIZE >> 1];

int subsz[MAX_SIZE >> 1];
int arr[MAX_SIZE >> 1];
int dfsord[MAX_SIZE >> 1];
int k = 0;
void dfs(int v, int pre) {
	subsz[v] = 1;
	dfsord[v] = k++;
	for (auto nv : g[v]) {
		if (nv != pre) {
			dfs(nv, v);
			subsz[v] += subsz[nv];
		}
	}
}

void update(int pt, int l, int r, int index, int val) {
	if (l > r) return;
	
	if (l <= pt && pt <= r) {
		rt[index].insert(val);
	}
	
	if (l == r) return;
	
	int mid = l + (r - l) / 2;
	if (pt <= mid) {
		update(pt, l, mid, index * 2, val);
	} else {
		update(pt, mid + 1, r, index * 2 + 1, val);
	}
}

int query(int start, int end, int l, int r, int index, int val) {
	if (start > end || l > r) return 0;
	if (start > r || l > end) return 0;
	if (start <= l && r <= end) return rt[index].order_of_key(val);
	int mid = l + (r - l) / 2;
	return query(start, end, l, mid, index * 2, val) +  query(start, end, mid + 1, r, index * 2 + 1, val);
}

int n;

int main() {
	int q, i;
	scanf("%d%d", &n, &q);
	for (i = 0 ; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	
	for (i = 1; i < n; i++) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		g[v1].push_back(v2);
		g[v2].push_back(v1);
	}
	
	dfs(0, -1);
	
	for (i = 0 ; i < n; i++) {
		update(dfsord[i], 0, n - 1, 1, arr[i]);
	}
	
	for (i = 0 ; i < q; i++) {
		int v, p;
		scanf("%d%d", &v, &p);
		// cout << v << " " << dfsord[v] << " " << dfsord[v] + sbz[v] - 1 << endl; 
		
		update(dfsord[v], 0, n - 1, 1, p);
		printf("%d\n", query(dfsord[v], dfsord[v] + subsz[v] - 1, 0, n - 1, 1, p));
	}
	return 0;	
}
