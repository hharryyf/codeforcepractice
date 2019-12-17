#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 262192
typedef long long ll;
using namespace std;

// adjaency list using a hashmap, pair.first is the vertex id, pair.second is the edge id
unordered_map<int, vector<pair<int, int> > > g;
// the visited set
unordered_set<int> h;

struct edge {
	   int id, from, to;
};

struct component {
	int invertex, edgeid, start, end;
};

vector<component> ans;

edge edg;

bool visited(int v) {
	 return h.find(v) != h.end();
}

void dfs(int v) {
	 h.insert(v);
	 for (auto p : g[v]) {
	 	 if (!visited(p.first)) {
	 	 	edg.from = v, edg.to = p.first, edg.id = p.second;
		    dfs(p.first);
		 }
	 }
}

int main() {
	int T, n, i;
	scanf("%d", &T);
	while (T > 0) {
		  g.clear();
		  h.clear();
		  ans.clear();
		  scanf("%d", &n);
		  for (i = 1; i <= n; i++) {
		  	  int v1, v2;
		  	  scanf("%d%d", &v1, &v2);
		  	  g[v1].emplace_back(v2, i);
		  	  g[v2].emplace_back(v1, i);
		  }
		  
		  unordered_map<int, vector<pair<int, int> > > :: iterator iter = g.begin();
		  while (iter != g.end()) {
		  		int v = iter->first;
		  		if (!visited(v)) {
				   dfs(v);
				   ans.push_back(component{v, edg.id, edg.from, edg.to}); 
				   // cout << v << " " << edg.id << " " << edg.from << " " << edg.to << endl; 
  		        }
		  		iter++;
		  }
		  
		  printf("%d\n", (int) ans.size() - 1);
		  
		  for (i = 0 ; i < (int) ans.size() - 1; i++) {
		  	  printf("%d %d %d\n", ans[i].edgeid, ans[i].end, ans[i+1].invertex);
		  }
		  T--;
	}	
	return 0;
}
