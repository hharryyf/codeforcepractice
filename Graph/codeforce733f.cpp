#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 262192

typedef long long ll;
using namespace std;

int parent[MAX_SIZE][19];
ll maxp[MAX_SIZE][19];
int f[MAX_SIZE];
vector<pair<int, ll> > g[MAX_SIZE]; 
struct edge {
    int from, to;
    ll w, c;
    int id;
    bool selected;
};
edge edg[MAX_SIZE];
int n, m;
ll S;
int height[MAX_SIZE];

void precompute() {
	 int i;
	 for (i = 0 ; i < MAX_SIZE; i++) {
	 	 f[i] = i;
	 }
}

int find(int x) {
	if (f[x] == x) return x;
	return f[x] = find(f[x]);
}

void unionset(int a, int b) {
	 int x = find(a), y = find(b);
	 f[x] = y;
}

void dfs(int v, int pre, int ht) {
	 parent[v][0] = pre;
	 height[v] = ht;
	 int i;
	 for (i = 1; i <= 18; i++) {
	 	 parent[v][i] = parent[parent[v][i-1]][i-1];
	 	 maxp[v][i] = max(maxp[v][i-1], maxp[parent[v][i-1]][i-1]);
	 }
	 
	 for (auto np : g[v]) {
	 	 if (np.first != pre) {
		  	maxp[np.first][0] = np.second;
		    dfs(np.first, v, ht + 1);
         }
	 }
}

static bool cmp(const edge &a, const edge &b) {
	   return a.w < b.w;
}

ll Kruskal(int index=0) {
	ll mst = 0;
	precompute();
	if (index != 0) {
	   unionset(edg[index].from, edg[index].to);
	   edg[index].w = edg[index].w - S / edg[index].c;
	   edg[index].selected = true;
	   mst += edg[index].w;
	}
	int i;
	for (i = 1; i <= m; i++) {
		if (find(edg[i].from) != find(edg[i].to)) {
		   unionset(edg[i].from, edg[i].to);
		   mst += edg[i].w;
		   if (index != 0) {
		   	  edg[i].selected = true;
		   } else {
		   	  g[edg[i].from].emplace_back(edg[i].to, edg[i].w);
		   	  g[edg[i].to].emplace_back(edg[i].from, edg[i].w);
		   }
		}
	}
	
	return mst;
}

// find the maximum weighted edge in the path from u->LCA(u, v) and v->LCA(u, v)
ll LCA(int u, int v) {
   if (height[u] < height[v]) {
   	  swap(u, v);
   }
   ll ret = 0;
   int i;
   for (i = 18; i >= 0; i--) {
   	   if (height[u] >= (1 << i) + height[v]) {
	   	  ret = max(ret, maxp[u][i]);
		  u = parent[u][i];	  
	   }
   }
   
   if (u == v) return ret;
   
   for (i = 18; i >= 0; i--) {
   	   if (parent[u][i] != parent[v][i]) {
			 ret = max(ret, max(maxp[u][i], maxp[v][i]));
			 u = parent[u][i];
			 v = parent[v][i];	  
	   }
   }
   
   ret = max(ret, max(maxp[u][0], maxp[v][0]));
   return ret;
}

int main() {
	scanf("%d%d", &n, &m);
	int i;
	for (i = 1; i <= m; i++) {
		scanf("%lld", &edg[i].w);
	}
	
	for (i = 1; i <= m; i++) {
		scanf("%lld", &edg[i].c);
	}
	
	for (i = 1; i <= m; i++) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		edg[i].from = v1;
		edg[i].to = v2;
		edg[i].id = i;
	}
	
	scanf("%lld", &S);
	sort(edg + 1, edg + 1 + m, cmp);
	ll mst = Kruskal();
	int index = 1;
	dfs(1, 0, 1);
	ll ans = mst;
	for (i = 1; i <= m; i++) {
		ll tmp = mst - LCA(edg[i].from, edg[i].to) + (edg[i].w - S / edg[i].c);
		if (tmp <= ans) {
		   index = i;
		   ans = tmp;
		}
	}
	
	mst = Kruskal(index);
	printf("%lld\n", mst);
	for (i = 1; i <= m; i++) {
		if (edg[i].selected) {
		   printf("%d %lld\n", edg[i].id, edg[i].w);
		}
	}
	return 0;
}

