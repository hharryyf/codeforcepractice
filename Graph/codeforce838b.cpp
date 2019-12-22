#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 524312

typedef long long ll;
using namespace std;

struct segt {
    ll value, lz;	   
};

struct edge {
    int from, to;
    ll w;
};

edge edg[MAX_SIZE];

segt tree1[MAX_SIZE], tree2[MAX_SIZE];
// the dfsorder of all nodes and the subtree size
int dfsord[MAX_SIZE >> 1];
int subsz[MAX_SIZE >> 1];
int height[MAX_SIZE >> 1];
// backward i
ll backward[MAX_SIZE >> 1];
// we only store the spanning tree
vector<pair<int, ll> > g[MAX_SIZE >> 1];
// the weighted depth of the nodes to the root
ll depth[MAX_SIZE >> 1];
int k = 1;
int parent[MAX_SIZE >> 1][19];
int remap[MAX_SIZE >> 1];

void dfs(int v, int pre, ll w, int ht) {
	 parent[v][0] = pre;
	 int i;
	 dfsord[v] = k++;
	 remap[k-1] = v;
	 subsz[v] = 1;
	 height[v] = ht;
	 depth[v] = w;
	 for (i = 1; i <= 18; i++) {
	 	 parent[v][i] = parent[parent[v][i-1]][i-1];
	 }
	 
	 for (auto p : g[v]) {
	 	 int nv = p.first;
	 	 if (nv != pre) {
		 	 dfs(nv, v, w + p.second, ht + 1);
			 subsz[v] += subsz[nv]; 
         }
	 }
}

int LCA(int u, int v) {
	if (height[u] < height[v]) {
	   swap(u, v);
	}
	
	int i;
	for (i = 18; i >= 0; i--) {
		if (height[u] >= (1 << i) + height[v]) {
		   u = parent[u][i];
		}
	}
	
	if (u == v) return u;
	
	for (i = 18; i >= 0; i--) {
		if (parent[u][i] != parent[v][i]) {
			u = parent[u][i];
			v = parent[v][i];
		}
	}
	
	return parent[u][0];
}

void pushdown(segt tree[], int l, int r, int index) {
	 if (l > r) return;
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

// increment [start, end] by val
void update(segt tree[], int start, int end, int l, int r, int index, ll val) {
	 if (start > end || l > r) return;
	 pushdown(tree, l, r, index);
	 if (start > r || l > end) return;
	 if (start <= l && r <= end) {
	 	tree[index].value += val;
	 	tree[index].lz += val;
	 	return;
	 }
	 
	 int mid = l + (r - l) / 2;
	 update(tree, start, end, l, mid, index * 2, val);
	 update(tree, start, end, mid + 1, r, index * 2 + 1, val);
	 tree[index].value = min(tree[index * 2].value, tree[index * 2 + 1].value);
}

// query the range max
ll query(segt tree[], int start, int end, int l, int r, int index) {
   if (start > end || l > r) return 10000000000000ll;
   pushdown(tree, l, r, index);
   if (start > r || l > end) return 10000000000000ll;
   if (start <= l && r <= end) return tree[index].value;
   int mid = l + (r - l) / 2;
   if (end <= mid) {
   	  return query(tree, start, end, l, mid, index * 2);
   } 
   
   if (start >= mid + 1) {
   	  return query(tree, start, end, mid + 1, r, index * 2 + 1);
   }
   
   return min(query(tree, start, end, l, mid, index * 2), 
	          query(tree, start, end, mid + 1, r, index * 2 + 1));
}

void build(int l, int r, int index) {
	 if (l > r) return;
	 if (l == r) {
	 	tree1[index].value = depth[remap[l]];
	 	tree2[index].value = backward[remap[l]] + tree1[index].value;
	 	return;
	 }
	 
	 int mid = l + (r - l) / 2;
	 build(l, mid, index * 2);
	 build(mid + 1, r, index * 2 + 1);
	 tree1[index].value = min(tree1[index * 2].value, tree1[index * 2 + 1].value);
	 tree2[index].value = min(tree2[index * 2].value, tree2[index * 2 + 1].value);
}


int n;

int main() {
	int m;
	scanf("%d%d", &n, &m);
	int i;
	for (i = 1; i <= 2 * n - 2; i++) {
		scanf("%d%d%lld", &edg[i].from, &edg[i].to, &edg[i].w);
		if (i <= n-1) {
		   g[edg[i].from].emplace_back(edg[i].to, edg[i].w);
		} else {
		   backward[edg[i].from] = edg[i].w;
		}
	}
	
	dfs(1, 0, 0, 0);
	build(1, n, 1);
	while (m > 0) {
		  int tp;
		  scanf("%d", &tp);
		  if (tp == 1) {
		  	 int id;
			 ll wei;
			 scanf("%d%lld", &id, &wei);
			 if (id <= n-1) {
			 	update(tree1, dfsord[edg[id].to], dfsord[edg[id].to] + subsz[edg[id].to] - 1, 1, n, 1, wei - edg[id].w);
			 	update(tree2, dfsord[edg[id].to], dfsord[edg[id].to] + subsz[edg[id].to] - 1, 1, n, 1, wei - edg[id].w);
			 	edg[id].w = wei;
			 } else {
                update(tree2, dfsord[edg[id].from], dfsord[edg[id].from], 1, n, 1, wei - edg[id].w);
			 	edg[id].w = wei;
			 } 
		  } else {
		  	 int u, v;
			 scanf("%d%d", &u, &v);
			 int anc = LCA(u, v);
			 if (anc == u) {
			    printf("%lld\n", query(tree1, dfsord[v], dfsord[v], 1, n, 1) - query(tree1, dfsord[u], dfsord[u], 1, n, 1));
			 } else {
			    printf("%lld\n", query(tree2, dfsord[u], dfsord[u] + subsz[u] - 1, 1, n, 1) -  query(tree1, dfsord[u], dfsord[u], 1, n, 1) + query(tree1, dfsord[v], dfsord[v], 1, n, 1));
			 }	 
		  }
		  m--;
	}
	return 0;
}

