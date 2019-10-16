#include <bits/stdc++.h>
#define MAX_SIZE 1048596

typedef long long ll;
using namespace std;

struct segt {
	ll value, lz;
};

segt tree[MAX_SIZE];
int dfsord[MAX_SIZE >> 1], subsize[MAX_SIZE >> 1], rmap[MAX_SIZE >> 1];
int arr[MAX_SIZE];
int k = 1;
vector<int> g[MAX_SIZE >> 1];
int n;
/* change color means change all the numbers between l and r with 1 << c */
/* query means count all the number of bits of all the numbers between l and r */

void dfs(int v, int pre) {
	subsize[v] = 1;
	dfsord[v] = k++;
	rmap[dfsord[v]] = v;
	for (auto nextv : g[v]) {
		if (nextv != pre) {
			dfs(nextv, v);
			subsize[v] += subsize[nextv];
		}
	}
}

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index].value = (1ll << arr[rmap[l]]);
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	tree[index].value = tree[index * 2].value | tree[index * 2 + 1].value;
}

void pushdown(int l, int r, int index) {
	if (tree[index].lz) {
		if (l != r) {
			tree[index * 2].value = tree[index * 2 + 1].value = tree[index * 2].lz 
								  = tree[index * 2 + 1].lz = tree[index].lz;
		}
		tree[index].lz = 0;
	}
}

void update(int start, int end, int l, int r, int index, int val) {
	if (start > end || l > r) return;
	pushdown(l, r, index);
	if (start > r || l > end) return;
	if (start <= l && r <= end) {
		tree[index].lz = (1ll << val);
		tree[index].value = tree[index].lz;
		return;
	}
	
	int mid = l + (r - l) / 2;
	update(start, end, l, mid, index * 2, val);
	update(start, end, mid + 1, r, index * 2 + 1, val);
	tree[index].value = tree[index * 2].value | tree[index * 2 + 1].value;
}

ll query(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return 0ll;
	pushdown(l, r, index);
	if (start > r || l > end) return 0ll;
	if (start <= l && r <= end) return tree[index].value;
	int mid = l + (r - l) / 2;
	return (query(start, end, l, mid, index * 2) | query(start, end, mid + 1, r, index * 2 + 1));
}

int main() {
	int m, i;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
	}
	
	for (i = 0; i < n - 1; i++) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		g[v1].push_back(v2);
		g[v2].push_back(v1);
	}
	
	dfs(1, -1);
	build(1, n, 1);
	
	while (m > 0) {
		int t, v, c;
		scanf("%d", &t);
		if (t == 1) {
			scanf("%d%d", &v, &c);
			update(dfsord[v], dfsord[v] + subsize[v] - 1, 1, n, 1, c);
		} else {
			scanf("%d", &v);
			ll ans = query(dfsord[v], dfsord[v] + subsize[v] - 1, 1, n, 1);
			int cnt = 0;
			for (i = 1; i <= 60; i++) {
				if ((ans & (1ll << i)) != 0) {
					cnt++;
				}
			}
			
			printf("%d\n", cnt);
		}
		m--;
	}
	
	return 0;
}
