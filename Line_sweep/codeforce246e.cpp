#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 262192
typedef long long ll;
using namespace std;

unordered_map<string, int> h;
// queries[r] =  [l, id]
vector<pair<int, int> > qr[MAX_SIZE];
int dep[MAX_SIZE];
vector<int> rt;
int parent[MAX_SIZE][18];
vector<int> g[MAX_SIZE];
vector<int> level[MAX_SIZE];
int tree[MAX_SIZE];
// hash value of each bfs order v
int value[MAX_SIZE];
int n, cnt = 1;
// bfs order of each v, rid[id[i]] = i
int id[MAX_SIZE], rid[MAX_SIZE];
int pre[MAX_SIZE];
char name[MAX_SIZE][22];

void update(int pos, int l, int r, int index, int val) {
	 if (pos < l || pos > r || l > r) return;
	 if (pos == l && l == r) {
	 	tree[index] = val;
	 	return;
	 }
	 int mid = (l + r) >> 1;
	 if (pos <= mid) {
	 	update(pos, l, mid, index << 1, val);
	 } else {
	    update(pos, mid + 1, r, index << 1 | 1, val);
	 }
	 tree[index] = tree[index * 2] + tree[index * 2 + 1];
}

int query(int start, int end, int l, int r, int index) {
	 if (start > end || l > r || start > r || l > end) return 0;
	 if (start <= l && r <= end) return tree[index];
	 int mid = (l + r) >> 1;
	 if (end <= mid) return query(start, end, l, mid, index << 1);
	 if (start >= mid + 1) return query(start, end, mid + 1, r, index << 1 | 1);
	 return query(start, end, l, mid, index << 1) + query(start, end, mid + 1, r, index << 1 | 1);
}

int kthparent(int v, int k) {
	int i;
	for (i = 17; i >= 0; i--) {
		if (k >= (1 << i)) v = parent[v][i], k -= (1 << i);
	}
	return v;
}

pair<int, int> kthson(int v, int k) {
    int lv = dep[v] + k;
    int L = n + 1, R = 0;
    if (level[lv].empty()) {
	   return make_pair(L, R);
	}
	
	int sz = (int) level[lv].size();
	int low = 0, high = sz - 1;
	while (low <= high) {
		  int mid = low + (high - low) / 2;
		  int nv = rid[level[lv][mid]];
		  int tv = kthparent(nv, k);
		  if (id[tv] < id[v]) {
		  	 low = mid + 1;
		  } else if (id[tv] > id[v]) {
		  	 high = mid - 1;
		  } else {
		  	 high = mid - 1;
		  	 L = level[lv][mid];
		  }
	}
	low = 0, high = sz - 1;
	while (low <= high) {
		  int mid = low + (high - low) / 2;
		  int nv = rid[level[lv][mid]];
		  int tv = kthparent(nv, k);
		  if (id[tv] < id[v]) {
		  	 low = mid + 1;
		  } else if (id[tv] > id[v]) {
		  	 high = mid - 1;
		  } else {
		  	 low = mid + 1;
		  	 R = level[lv][mid];
		  }
	}
	return make_pair(L, R);
}

void bfs(int src) {
	 int i;
	 queue<pair<int, int> > q;
	 q.push(make_pair(src, 1));
	 while (!q.empty()) {
	 	   auto p = q.front();
	 	   q.pop();
	 	   id[p.first] = cnt++;
	 	   dep[p.first] = p.second;
	 	   level[dep[p.first]].push_back(id[p.first]);
		   rid[id[p.first]] = p.first;
	 	   value[id[p.first]] = h[name[p.first]];
	 	   for (i = 1; i <= 17; i++) {
		   	   parent[p.first][i] = parent[parent[p.first][i-1]][i-1];	
		   }
		   for (auto nv : g[p.first]) {
			   q.push(make_pair(nv, p.second + 1));
		   }
	 }
}

int ans[MAX_SIZE];

int main() {
	int i;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) {
		int v;
		scanf("%s%d", name[i], &v);
		if (v == 0) {
		   rt.push_back(i);
		} else {
		   g[v].push_back(i);
		   parent[i][0] = v;
		}
		h[name[i]] = 1;
	}
	
	int ct = 1;
	auto iter = h.begin();
	while (iter != h.end()) {
		  iter->second = ct++;
		  iter++;
	}
	
	for (auto v : rt) {
		bfs(v);
	}
	
	int q;
	scanf("%d", &q);
	for (i = 1; i <= q; i++) {
		int v, k;
		scanf("%d%d", &v, &k);
		auto p = kthson(v, k);
		// cout << "query " << p.first << " " << p.second << endl;
		if (p.first <= p.second) {
		   qr[p.second].emplace_back(p.first, i);
		}
	}
	/*
	for (i = 1; i <= n; i++) printf("%d ", value[i]);
	printf("\n");
	*/
	for (i = 1; i <= n; i++) {
		if (pre[value[i]]) {
		   update(pre[value[i]], 1, n, 1, 0);
		}
		pre[value[i]] = i;
		update(i, 1, n, 1, 1);
		for (auto qq : qr[i]) {
			ans[qq.second] = query(qq.first, i, 1, n, 1);
		}
	}
	
	for (i = 1; i <= q; i++) {
		printf("%d\n", ans[i]);
	}
	return 0;
}
