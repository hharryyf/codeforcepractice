#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 262192
typedef long long ll;
using namespace std;

int value[MAX_SIZE], lz[MAX_SIZE];
int a[MAX_SIZE >> 1];
pair<int, int> it[401];
vector<int> add[MAX_SIZE >> 1];
vector<int> del[MAX_SIZE >> 1];

void build(int l, int r, int index) {
	 if (l > r) return;
	 if (l == r) {
	 	value[index] = a[l];
	 	return;
	 }
	 int mid = (l + r) >> 1;
	 build(l, mid, index << 1);
	 build(mid + 1, r, index << 1 | 1);
	 value[index] = max(value[index << 1], value[index << 1 | 1]);
}

void pushdown(int l, int r, int index) {
	 if (l > r) return;
	 if (lz[index]) {
	 	if (l != r) {
		   lz[index << 1] += lz[index];
		   lz[index << 1 | 1] += lz[index];
		   value[index << 1] += lz[index];
		   value[index << 1 | 1] += lz[index];
	    } 
	    lz[index] = 0;
	 }
}

void update(int start, int end, int l, int r, int index, int val) {
	 if (start > end || l > r) return;
	 pushdown(l, r, index);
	 if (start > r || l > end) return;
	 if (start <= l && r <= end) {
	 	value[index] += val;
	 	lz[index] += val;
	 	return;
	 }
	 int mid = (l + r) >> 1;
	 if (end <= mid) {
	 	update(start, end, l, mid, index << 1, val);
	 } else if (start >= mid + 1) {
	    update(start, end, mid + 1, r, index << 1 | 1, val);
	 } else {
	    update(start, end, l, mid, index << 1, val);
	    update(start, end, mid + 1, r, index << 1 | 1, val);
	 }
	 value[index] = max(value[index << 1], value[index << 1 | 1]);
}

int main() {
	int i, n, m;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n; ++i) scanf("%d", &a[i]);
	build(1, n, 1);
	for (i = 1; i <= m; ++i) {
		scanf("%d%d", &it[i].first, &it[i].second);
		add[it[i].first].push_back(i);
		del[it[i].second].push_back(i);
	}
	
	int ans = -1, idx = 0;
	int cnt = 0;
	// we check what is the maximum difference between bmax - bmin by assuming
	// the min is at index i
	for (i = 1; i <= n; ++i) {
		for (auto v : add[i]) {
			cnt++;
			update(it[v].first, it[v].second, 1, n, 1, -1);
		}
		
		int am = a[i] - cnt;
		if (ans < value[1] - am) {
		   ans = value[1] - am;
		   idx = i;
		}
		
		for (auto v : del[i]) {
			cnt--;
			update(it[v].first, it[v].second, 1, n, 1, 1);
		}
	}
	
	cnt = 0;
	vector<int> ret;
	for (i = 1; i <= m; i++) {
		if (it[i].first <= idx && idx <= it[i].second) {
		   cnt++;
		   ret.push_back(i);
        }
	}
	
	printf("%d\n%d\n", ans, cnt);
	for (auto v : ret) {
		printf("%d ", v);
	}
	printf("\n");
	return 0;
}

