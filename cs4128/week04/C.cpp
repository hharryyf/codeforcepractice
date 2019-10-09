#include <bits/stdc++.h>
#define MAX_SIZE 1048592
#define MOD 1000000007

typedef long long ll;
using namespace std;

struct segt {
	ll value, lz;
};

int dfsord[300011];
int ht[300011];
vector<int> graph[300011];
int sbz[300011];

segt tree1[MAX_SIZE], tree2[MAX_SIZE];
int k = 1;
int n;

void pushdown(segt arr[], int l, int r, int index) {
	int mid = l + (r - l) / 2;
	int len1 = mid - l + 1, len2 = r - mid;
	if (arr[index].lz != 0) {
		if (l != r) {
			arr[index * 2].value = (arr[index * 2].value + len1 * arr[index].lz) % MOD; 
			arr[index * 2 + 1].value = (arr[index * 2 + 1].value + len2 * arr[index].lz) % MOD; 
			arr[index * 2].lz = (arr[index * 2].lz + arr[index].lz) % MOD;
			arr[index * 2 + 1].lz = (arr[index * 2 + 1].lz + arr[index].lz) % MOD;
		}
		arr[index].lz = 0;
	}
}

void update(segt arr[], int start, int end, int l, int r, int index, ll val) {
	if (start > end || l > r) return;
	pushdown(arr, l, r, index);
	if (start > r || l > end) return;
	if (start <= l && r <= end) {
		arr[index].value = (arr[index].value + val) % MOD;
		arr[index].lz = (arr[index].lz + val) % MOD;
		return;
	}
	
	int mid = l + (r - l) / 2;
	if (mid >= end) {
		update(arr, start, end, l, mid, index * 2, val);
	} else if (start >= mid + 1) {
		update(arr, start, end, mid + 1, r, index * 2 + 1, val);
	} else {
		update(arr, start, end, l, mid, index * 2, val);
		update(arr, start, end, mid + 1, r, index * 2 + 1, val);
	}
	arr[index].value = (arr[index * 2].value + arr[index * 2 + 1].value) % MOD;
}

ll query(segt arr[], int start, int end, int l, int r, int index) {
	if (start > end || l > r) return 0ll;
	pushdown(arr, l, r, index);
	if (start > r || l > end) return 0ll;
	if (start <= l && r <= end) return arr[index].value;
	int mid = l + (r - l) / 2;
	if (mid >= end) {
		return query(arr, start, end, l, mid, index * 2);
	} else if (start >= mid + 1) {
		return query(arr, start, end, mid + 1, r, index * 2 + 1);
	}
	
	return query(arr, start, end, l, mid, index * 2) + query(arr, start, end, mid + 1, r, index * 2 + 1); 
}

void dfs(int v, int dpt) {
	dfsord[v] = k++;
	ht[v] = dpt;
	sbz[v] = 1;
	for (auto nextv : graph[v]) {
		dfs(nextv, dpt + 1);
		sbz[v] += sbz[nextv];
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 2; i <= n; i++) {
		int v;
		scanf("%d", &v);
		graph[v].push_back(i);
	}
	
	dfs(1, 1);
	
	int m;
	scanf("%d", &m);
	
	while (m > 0) {
		int t, v;
		ll k, x;
		scanf("%d%d", &t, &v);
		if (t == 1) {
			scanf("%lld%lld", &x, &k);
			update(tree1, dfsord[v], dfsord[v] + sbz[v] - 1, 1, n, 1,((k * ht[v]) % MOD + x) % MOD);
			update(tree2, dfsord[v], dfsord[v] + sbz[v] - 1, 1, n, 1, k % MOD);
		} else {
			ll val1 = query(tree1, dfsord[v], dfsord[v], 1, n, 1);
			ll val2 = query(tree2, dfsord[v], dfsord[v], 1, n, 1);
			printf("%lld\n",((val1 - (val2 * ht[v]) % MOD) % MOD + MOD) % MOD);
		}
		
		m--;
	} 
	return 0;
}
