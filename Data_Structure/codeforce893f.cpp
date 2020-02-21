#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define INF 1000000007
#define MAX_SIZE 262192
typedef long long ll;
using namespace std;

int cnt = 0;
struct segt {
	   // left is the left pointer, right is the right pointer
	   // value is the range max
	   int left, right, value;
};

int height[MAX_SIZE];
vector<int> level[MAX_SIZE];
segt tree[MAX_SIZE * 40];
int root[MAX_SIZE << 1];
int a[MAX_SIZE];
int subsz[MAX_SIZE], visited[MAX_SIZE];
int rmp[MAX_SIZE];
int depth[MAX_SIZE];
int k = 1;
int n;

int build(int l, int r) {
	if (l > r) return 0;
	int curr = ++cnt;
	if (l == r) {
	   tree[curr].left = tree[curr].right = 0;
	   tree[curr].value = INF;
	   return curr;
	}
	int mid = l + (r - l) / 2;
	tree[curr].left = build(l, mid);
	tree[curr].right = build(mid + 1, r);
	tree[curr].value = INF;
	return curr;
}

int update(int rt, int pos, int l, int r, int val) {
	int curr = ++cnt;
	tree[curr] = tree[rt];
	if (l > r || pos < l || pos > r || rt == 0) return curr;
	if (l == r && pos == l) {
	   tree[curr].value = val;
	   return curr;
	}
	
	int mid = l + (r - l) / 2;
	if (pos <= mid) {
	   tree[curr].left = update(tree[rt].left, pos, l, mid, val);
	} else {
	   tree[curr].right = update(tree[rt].right, pos, mid + 1, r, val);
	}
	tree[curr].value = min(tree[tree[curr].left].value, tree[tree[curr].right].value);
	return curr;
}

int query(int rt, int start, int end, int l, int r) {
	if (rt == 0 || start > end || l > r) return INF;
	if (start <= l && r <= end) return tree[rt].value;
	int mid = l + (r - l) / 2;
	if (end <= mid) return query(tree[rt].left, start, end, l, mid);
	if (start >= mid + 1) return query(tree[rt].right, start, end, mid + 1, r);
	return min(query(tree[rt].left, start, end, l, mid), 
	           query(tree[rt].right, start, end, mid + 1, r));
}

void upd(int version, int pos, int val) {
	 root[version] = update(root[version - 1], pos, 1, n, val);
}

vector<int> g[MAX_SIZE];
void dfs(int v, int dpt) {
	 height[v] = dpt;
	 level[height[v]].push_back(k);
	 visited[v] = k++;
	 rmp[visited[v]] = v;
	 subsz[v] = 1;
	 for (auto nv : g[v]) {
	 	 if (!visited[nv]) {
		 	 dfs(nv, dpt + 1);
			 subsz[v] += subsz[nv]; 
         	 depth[v] = max(depth[v], 1 + depth[nv]);
		 }
	 }
}

int nvs[MAX_SIZE];

int main() {
	int src;
	scanf("%d%d", &n, &src);
	int i;
	for (i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	
	for (i = 1; i < n; i++) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		g[v1].push_back(v2);
		g[v2].push_back(v1);
	}
	
	dfs(src, 1);
	root[0] = build(1, n);
	queue<int> q;
	int vs = 1;
	q.push(src);
	while (!q.empty()) {
		  int v = q.front();
		  q.pop();
		  if (nvs[v]) continue;
		  nvs[v] = vs++;
		  upd(vs-1, visited[v], a[v]);
		  for (auto nv : g[v]) {
		  	  if (!nvs[nv]) q.push(nv);
		  }
	}
	
	int xi, ki, m;
	int lst = 0;
	scanf("%d", &m);
	while (m > 0) {
		  scanf("%d%d", &xi, &ki);
		  xi = ((xi + lst) % n) + 1;
		  ki = (ki + lst) % n;
		  int l = visited[xi], r = visited[xi] + subsz[xi] - 1;
		  if (depth[xi] < ki) {
		  	  vs = n;
		  	  lst = query(root[vs], l, r, 1, n);
		  } else {
	   	  	  int mxdp = height[xi] + ki;
		  	  int idx = level[mxdp].back();
		  	  vs = nvs[rmp[idx]];
		  	  lst = query(root[vs], l, r, 1, n);
		  }
		  printf("%d\n", lst);
		  m--;
	}
	return 0;
}
