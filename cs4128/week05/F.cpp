#include <bits/stdc++.h>
#define MAX_SIZE 2097292
#define INF 4194304
/*
	https://codeforces.com/contest/1132/problem/G
*/

using namespace std;

int dp[MAX_SIZE >> 1];
int n;
int arr[MAX_SIZE >> 1];
int rt[MAX_SIZE >> 1];

vector<int> g[MAX_SIZE >> 1];
int k = 1;
int dfsord[MAX_SIZE >> 1];
int subsz[MAX_SIZE >> 1];

struct segt {
	int lz;
	int value;
};

segt tree[MAX_SIZE];

void dfs(int v) {
	subsz[v] = 1;
	dfsord[v] = k++;
	for (auto nextv : g[v]) {
		dfs(nextv);
		subsz[v] += subsz[nextv];
	}
}

void pushdown(int l, int r, int index) {
	if (tree[index].lz) {
		if (l != r) {
			tree[index * 2].value += tree[index].lz;
			tree[index * 2 + 1].value += tree[index].lz;
			tree[index * 2].lz += tree[index].lz;
			tree[index * 2 + 1].lz += tree[index].lz;
		}
		tree[index].lz = 0;
	}
}

void update(int start, int end, int l, int r, int index, int val) {
	if (start > end || l > r) return;
	pushdown(l, r, index);
	if (start > r || l > end) return;
	if (start <= l && r <= end) {
		tree[index].value += val;
		tree[index].lz += val;
		return;
	}
	
	int mid = l + (r - l) / 2;
	update(start, end, l, mid, index * 2, val);
	update(start, end, mid + 1, r, index * 2 + 1, val);
	tree[index].value = max(tree[index * 2].value, tree[index * 2 + 1].value);
}

void rmv(int pt, int l, int r, int index) {
	if (l > r) return;
	pushdown(l, r, index);
	if (l == r && r == pt) {
		tree[index].value = -INF;
		return;
	}
	
	int mid = l + (r - l) / 2;
	if (pt <= mid) rmv(pt, l, mid, index * 2);
	else {
		rmv(pt, mid + 1, r, index * 2 + 1);
	}
	tree[index].value = max(tree[index * 2].value, tree[index * 2 + 1].value);
}

int query() {
	return tree[1].value;
}

int main() {
	int k;
	scanf("%d%d", &n, &k);
	stack<int> st;
	int i;
	
	for (i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
	}
	
	for (i = n; i >= 1; i--) {
		if (st.empty()) {
			rt[i] = -1;
			dp[i] = 1;
		} else {
			while (!st.empty() && arr[st.top()] <= arr[i]) {
				st.pop();
			}
			
			if (st.empty()) {
				rt[i] = -1;
				dp[i] = 1;
			} else {
				rt[i] = st.top();
				dp[i] = dp[st.top()] + 1;
			}
		}
		st.push(i);
	}
	
	for (i = 1; i <= n; i++) {
		if (rt[i] != -1) {
			g[rt[i]].push_back(i);
		}
	}
	
	for (i = n; i >= 1; i--) {
		if (!dfsord[i]) {
			dfs(i);
		}
	}
	
	vector<int> ans;
	
	for (i = n; i >= 1; i--) {
		update(dfsord[i], dfsord[i], 1, n, 1, dp[i]);
		if (i + k - 1 <= n) {
			ans.push_back(query());
			update(dfsord[i + k - 1], dfsord[i + k - 1] + subsz[i + k - 1] - 1, 1, n, 1, -1);
			rmv(dfsord[i + k - 1], 1, n, 1);
		}
	}
	
	for (i = (int) ans.size() - 1; i >= 0; i--) {
		printf("%d ", ans[i]);
	}
	printf("\n");
	return 0;
}
