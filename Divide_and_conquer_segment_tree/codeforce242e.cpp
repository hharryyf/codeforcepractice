#include <bits/stdc++.h>
#define MAX_LEN 262151
#define MAX_BIT 25
typedef long long ll;

using namespace std;

// the original tree
ll tree[MAX_LEN][MAX_BIT];
// the lazy tree
ll lazy[MAX_LEN][MAX_BIT];
// the values seperated by bits
ll value[MAX_BIT][MAX_LEN >> 1];
// the total number of values inserted
int n;

// build the tree in a dimension
void build(int start, int end, int index, ll arr[], int dim);
// query start to end on tree[][dim]
ll query(int start, int end, int l, int r, int index, int dim);
// update the dim
void update(int start, int end, int l, int r, int index, int dim, ll Xor);

int main(int argc, char *argv[]) {
	cin >> n;
	int i, j, m, t, st, ed;
	ll v;
	ll ans = 0;
	for (i = 0 ; i < n; i++) {
		cin >> v;
		j = 0;
		while (v > 0) {
			value[j][i] = v % 2;
			v = v / 2;
			j++;
		}
	}
	
	for (i = 0 ; i < MAX_BIT; i++) {
		build(0, n - 1, 1, value[i], i);
	}
	
	cin >> m;
	for (i = 0 ; i < m; i++) {
		cin >> t;
		if (t == 1) {
			cin >> st >> ed;
			ans = 0;
			for (j = 0 ; j < MAX_BIT; j++) {
				v = query(st - 1, ed - 1, 0, n - 1, 1, j) * (1 << j);
				ans = ans + v;
			    // cout << v << " ";
			}
			// cout << endl;
			cout << ans << endl;
		} else if (t == 2) {
			cin >> st >> ed >> v;
			vector<ll> token = vector<ll>();
			while (v > 0) {
				token.push_back(v % 2);
				v = v / 2;
			}
			for (j = 0 ; j < (int) token.size(); j++) {
				update(st - 1, ed - 1, 0, n - 1, 1, j, token[j]);
			}
		}
	}
	/*
	for (i = 0 ; i < 25; i++) {
		cout << "index = " << i << "value = " << query(i, i, 0, n - 1, 1, 1) << endl;
	}*/
	/*
	for (i = 1 ; i < 10; i++) {
		cout << i << " " << tree[i][1] << ", " << lazy[i][1] << endl;
	}*/
	return 0;
}


void build(int start, int end, int index, ll arr[], int dim) {
	if (start > end) return;
	if (start == end) {
		tree[index][dim] = arr[start];
		return;
	}
	
	int mid = start + (end - start) / 2;
	build(start, mid, index * 2, arr, dim);
	build(mid + 1, end, index * 2 + 1, arr, dim);
	tree[index][dim] = tree[index * 2][dim] + tree[index * 2 + 1][dim];
}

ll query(int start, int end, int l, int r, int index, int dim) {
	if (start > end || l > r) return 0;
	if (lazy[index][dim] != 0) {
		// cout << " a propagation at " << dim << " th dim " << l << " to " << r << " from " << tree[index][dim];
		ll tol = r - l + 1;
		tree[index][dim] = tol - tree[index][dim];
		// cout << " to " << tree[index][dim] << endl;;
		if (l != r) {
			lazy[index * 2][dim] = 1 - lazy[index * 2][dim];
			lazy[index * 2 + 1][dim] = 1 - lazy[index * 2 + 1][dim];
		}
		lazy[index][dim] = 0;
	}
	
	if (start > r || end < l) return 0;
	
	if (start <= l && r <= end) {
	    // if (dim == 1)
	    // cout << l << " to " << r << " is queried " << tree[index][dim] << endl;
		return tree[index][dim];
	}
	
	int mid = l + (r - l) / 2;
	return query(start, end, l, mid, index * 2, dim) + query(start, end, mid + 1, r, index * 2 + 1, dim);
}

void update(int start, int end, int l, int r, int index, int dim, ll Xor) {
	if (start > end || l > r) return;
	if (Xor == 0) {
		return;
	}
	
	if (lazy[index][dim] != 0) {
		ll tol = r - l + 1;
		tree[index][dim] = tol - tree[index][dim];
		if (l != r) {
			lazy[index * 2][dim] = 1 - lazy[index * 2][dim];
			lazy[index * 2 + 1][dim] = 1 - lazy[index * 2 + 1][dim];
		}
		lazy[index][dim] = 0;
	}
	
	if (start > r || end < l) return;
	if (start <= l && r <= end) {
		ll tol = r - l + 1;
		tree[index][dim] = tol - tree[index][dim];
		if (l != r) {
			lazy[index * 2][dim] = 1 - lazy[index * 2][dim];
			lazy[index * 2 + 1][dim] = 1 - lazy[index * 2 + 1][dim];
		}
		 
		return;
	}
	
	int mid = l + (r - l) / 2;
	update(start, end, l, mid, index * 2, dim, Xor);
	update(start, end, mid + 1, r, index * 2 + 1, dim, Xor);
	tree[index][dim] = tree[index * 2][dim] + tree[index * 2 + 1][dim];
}
