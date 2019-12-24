#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 401111

typedef long long ll;
using namespace std;

int cmpid[MAX_SIZE];
vector<pair<int, int> > g[MAX_SIZE];
int low[MAX_SIZE];
int visited[MAX_SIZE];
int instack[MAX_SIZE];
stack<int> s;
int k = 1;
// use tarjan's algorithm to extract the biconnected components
// and then use a dfs from the largest biconnected component 
// and stores the edges in ans
pair<int, int> ans[MAX_SIZE];
int n, m;

void tarjan(int v, int pre) {
	 visited[v] = k++;
	 low[v] = visited[v];
	 s.push(v);
	 instack[v] = 1;
	 for (auto np : g[v]) {
	 	 int nv = np.first;
	 	 if (nv != pre) {
		 	if (!visited[nv]) {
			    tarjan(nv, v);
			    low[v] = min(low[v], low[nv]);
	        } else if (instack[nv]) {
			    low[v] = min(low[v], visited[nv]);
			} 
         }
	 }
	 
	 if (low[v] == visited[v]) {
	 	while (s.top() != v) {
	        cmpid[s.top()] = v;
			instack[s.top()] = 0;
			s.pop(); 
	    }
	    
	    cmpid[s.top()] = v;
		instack[s.top()] = 0;
		s.pop();
	 }
}

void dfs(int v, int pre) {
	visited[v] = low[v] = k++;
	for (auto np : g[v]) {
		if (np.first != pre) {
		   if (!visited[np.first]) {
		   	  dfs(np.first, v);
		   	  low[v] = min(low[v], low[np.first]);
		   	  ans[np.second].first = v;
			  ans[np.second].second = np.first;
		   	  if (low[np.first] > visited[v]) {
			  	  ans[np.second].first = np.first;
				  ans[np.second].second = v;		 
	          }
		   } else {
		   	   low[v] = min(low[v], visited[np.first]);
		   	   if (visited[v] > visited[np.first]) {
			   	  ans[np.second].first = v;
				  ans[np.second].second = np.first;	  
			   }
		   }
		}
	} 
}

int main() {
	scanf("%d%d", &n, &m);
	int i;
	
	for (i = 1; i <= m; i++) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		g[v1].emplace_back(v2, i);
		g[v2].emplace_back(v1, i);
	} 
	
	tarjan(1, 0);
	
	unordered_map<int, int> cnt;
	for (i = 1; i <= n; i++) cnt[cmpid[i]]++;
	unordered_map<int, int> :: iterator iter = cnt.begin();
	int sz = 0, index = 0;
	while (iter != cnt.end()) {
		  if (sz <= iter->second) {
		  	 sz = iter->second;
		  	 index = iter->first;
		  }
 		  iter++;
	}
	
	memset(visited, 0, sizeof(visited));
	memset(low, 0, sizeof(low));
	k = 1;
	dfs(index, 0);
	
	printf("%d\n", sz);
	for (i = 1; i <= m; i++) {
		printf("%d %d\n", ans[i].first, ans[i].second);
	}
	return 0;
}

