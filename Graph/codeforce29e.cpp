#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 502
typedef long long ll;
using namespace std;

struct state {
	   int x, y;
};
vector<int> g[MAX_SIZE];
int dist[MAX_SIZE][MAX_SIZE];
pair<int, int> pre[MAX_SIZE][MAX_SIZE];
int n, m;

int main() {
	int i;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= m; i++) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		g[v1].push_back(v2), g[v2].push_back(v1);
	} 
	
	queue<pair<int, int> > q;
	q.push(make_pair(1, n));
	dist[1][n] = 1;
	while (!q.empty()) {
		  auto s = q.front();
		  q.pop();
		  for (auto v1 : g[s.first]) {
		  	  for (auto v2 : g[s.second]) {
				 if (v1 != v2 && !dist[v1][v2]) {
				 	q.push(make_pair(v1, v2));
				 	dist[v1][v2] = dist[s.first][s.second] + 1;
				 	pre[v1][v2] = {s.first, s.second};
				 }
	          }
		  }
	}
	
	if (!dist[n][1]) {
	   printf("-1\n");
	   return 0;
	}
	
	printf("%d\n", dist[n][1] - 1);
	vector<int> s1, s2;
	int v1 = n, v2 = 1;
	while (v1 != 1 || v2 != n) {
		  s1.push_back(v1), s2.push_back(v2);
		  auto p = pre[v1][v2];
		  v1 = p.first, v2 = p.second;	  
	}
	
	s1.push_back(1), s2.push_back(n);
	for (i = (int) s1.size() - 1; i >= 0; i--) {
		printf("%d ", s1[i]);
	}
	printf("\n");
	
	for (i = (int) s2.size() - 1; i >= 0; i--) {
		printf("%d ", s2[i]);
	}
	printf("\n");
	return 0;
}
