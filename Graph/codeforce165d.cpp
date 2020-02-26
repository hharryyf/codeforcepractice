#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 131092
typedef long long ll;
using namespace std;

int tree[MAX_SIZE << 1];
int parent[MAX_SIZE][18];
int height[MAX_SIZE];
int visited[MAX_SIZE];
vector<int> g[MAX_SIZE];
int cnt = 1;
pair<int, int> edg[MAX_SIZE];

void dfs(int v, int pre) {
	 height[v] = height[pre] + 1;
	 visited[v] = cnt++;
	 parent[v][0] = pre;
	 for (int i = 1; i < 18; i++) parent[v][i] = parent[parent[v][i-1]][i-1];
	 for (auto nv : g[v]) {
	 	 if (!visited[nv]) {
         	dfs(nv, v);
		 }
	 }
}

int kthparent(int u, int k) {
	int i;
	for (i = 17; i >= 0; i--) {
		if (k >= (1 << i)) {
		   k -= (1 << i), u = parent[u][i];
		}
	}
	return u;
}

int LCA(int u, int v) {
	if (height[u] < height[v]) swap(u, v);
	int i;
	for (i = 17; i >= 0; i--) {
		if (height[u] >= height[v] + (1 << i)) u = parent[u][i];
	}
	
	if (u == v) return u;
	
	for (i = 17; i >= 0; i--) {
		if (parent[u][i] != parent[v][i]) {
		   u = parent[u][i], v = parent[v][i];
		}
	}
	return parent[u][0];
}

void build(int l, int r, int index) {
	 if (l > r) return;
	 if (l == r) {
	 	tree[index] = 1; 
	    return;
     }
     
     int mid = l + (r - l) / 2;
     build(l, mid, index * 2);
     build(mid + 1, r, index * 2 + 1);
     tree[index] = tree[index * 2] + tree[index * 2 + 1];
}

void update(int pos, int l, int r, int index, int val) {
	 if (pos < l || l > r || pos > r) return;
	 if (l == r && pos == l) {
	 	tree[index] = val;
	 	return;
	 }
	 
	 int mid = l + (r - l) / 2;
	 if (pos <= mid) update(pos, l, mid, index * 2, val);
	 else {
	 	  update(pos, mid + 1, r, index * 2 + 1, val);
	 }
	 
	 tree[index] = tree[index * 2] + tree[index * 2 + 1];
}

int query(int start, int end, int l, int r, int index) {
	 if (start > end || l > r || start > r || l > end) return 0;
	 if (start <= l && r <= end) return tree[index];
	 int mid = l + (r - l) / 2;
	 if (end <= mid) return query(start, end, l, mid, index * 2);
	 if (start >= mid + 1) return query(start, end, mid + 1, r, index * 2 + 1);
	 return query(start, end, l, mid, index * 2) + query(start, end, mid + 1, r, index * 2 + 1);
}

int main() {
	int n, m;
	scanf("%d", &n);
	int i;
	for (i = 1; i < n; i++) {
		scanf("%d %d", &edg[i].first, &edg[i].second);
		g[edg[i].first].push_back(edg[i].second);
		g[edg[i].second].push_back(edg[i].first);
	}
	
	int v = 1, mx = (int) g[1].size();
	for (i = 1; i <= n; i++) {
		if ((int) g[i].size() >= mx) {
		   v = i, mx = (int) g[i].size();
		}
	}
	
	dfs(v, 0);
	build(1, n, 1);
	
	scanf("%d", &m);
	while (m > 0) {
		  int tp, v1, v2;
		  scanf("%d", &tp);
		  if (tp == 1) {
		  	 scanf("%d", &i);
		  	 if (height[edg[i].first] > height[edg[i].second]) swap(edg[i].first, edg[i].second);
		  	 update(visited[edg[i].second], 1, n, 1, 1);
		  } else if (tp == 2) {
		  	 scanf("%d", &i);
		  	 if (height[edg[i].first] > height[edg[i].second]) swap(edg[i].first, edg[i].second);
		  	 update(visited[edg[i].second], 1, n, 1, 0);
		  } else {
		  	 scanf("%d%d", &v1, &v2);
		  	 if (v1 == v2) {
			 	printf("0\n");  
	         } else {
			    int lca = LCA(v1, v2);
			    if (lca == v1) {
				   int p = kthparent(v2, height[v2] - height[v1] - 1);
				   int ret = query(visited[p], visited[v2], 1, n, 1);
				   if (ret == height[v2] - height[v1]) {
				   	  printf("%d\n", ret);
				   } else {
				   	  printf("-1\n");
				   }
				} else if (lca == v2) {
				   int p = kthparent(v1, height[v1] - height[v2] - 1);
				   int ret = query(visited[p], visited[v1], 1, n, 1);
				   if (ret == height[v1] - height[v2]) {
				   	  printf("%d\n", ret);
				   } else {
				   	  printf("-1\n");
				   }
				} else {
				   int p1 = kthparent(v1, height[v1] - height[v] - 1);
				   int p2 = kthparent(v2, height[v2] - height[v] - 1);
				   int ret = query(visited[p1], visited[v1], 1, n, 1) + query(visited[p2], visited[v2], 1, n, 1);
				   if (ret == height[v1] + height[v2] - 2) {
				   	  printf("%d\n", ret);
				   } else {
				   	  printf("-1\n");
				   }
				}
			 }
		  }
		  
		  m--;
	}
	return 0;
}
