#include <bits/stdc++.h>
#define MOD 1000000007
typedef long long ll;
#define MAX_SIZE 101111
using namespace std;

/*
  this problem is eqivalent to find the least lexigraphical top-sort 
  order of a DAG
  
  we need to use the bfs-version of the top-sort algorithm
  
  implement top-sort in a reverse order, and the resulting sequence is the answer
*/
vector<int> g[MAX_SIZE];
int visited[MAX_SIZE];
int label[MAX_SIZE];
int n;
int outdegree[MAX_SIZE];
 
int main() {
	int i, m;
	scanf("%d%d", &n, &m);
	/*
	  always find a vertex with outdegree of 0
	*/	
	
	priority_queue<int> q;
	for (i = 0 ; i < m; i++) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		g[v2].push_back(v1);
		outdegree[v1]++;
	}
	
	for (i = 1; i <= n; i++) {
		if (!outdegree[i]) {
		   q.push(i);
		}
	}
	
	int ans = n;
	
	while (!q.empty()) {
 		  int v = q.top();
 		  q.pop();
 		  if (visited[v]) {
		  	 continue; 
          }
          
          label[v] = ans--;
          visited[v] = 1;
          for (auto nv : g[v]) {
		  	  if (!visited[nv]) {
			  	 outdegree[nv]--;
			  	 if (!outdegree[nv]) {
				 	q.push(nv);  
			     }
	          }
		  }
	}
	
	for (i = 1; i <= n; i++) {
		printf("%d ", label[i]);
	}
	return 0;
}

