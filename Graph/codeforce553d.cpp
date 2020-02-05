#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 100011
typedef long long ll;
using namespace std;

bool frt[MAX_SIZE];
vector<int> g[MAX_SIZE];
vector<int> h[MAX_SIZE];
int n, m, k;
int deg[MAX_SIZE], adj[MAX_SIZE];
int cnt, tol = 0;
int ans[MAX_SIZE];
bool del[MAX_SIZE];

double score(int v) {
    return ((double) adj[v] * 1.0) / ((double) deg[v] * 1.0);
}

bool valid(double mid) {
	 int i;
	 cnt = 0;
	 for (i = 0 ; i <= n; i++) {
	     del[i] = false;
	     h[i].clear();
	     adj[i] = 0;
	 }
	 
	 queue<int> q;
	 for (i = 1; i <= n; i++) {
	 	 if (!frt[i]) {
		  	for (auto v : g[i]) {
				if (!frt[v]) {
				   h[i].push_back(v);
				   adj[i]++;
				}  
		    }
         } else {
             del[i] = true;
         }
	 }
	 
	 for (i = 1; i <= n; i++) {
	     if (score(i) < mid) {
	         q.push(i);
	     }
	 }
	 
	 while (!q.empty()) {
	     int v = q.front();
	     q.pop();
	     if (del[v]) continue;
	     del[v] = true;
	     adj[v] = 0;
	     for (auto nv : h[v]) {
	         if (!del[nv]) {
	             adj[nv]--;
	             if (score(nv) < mid) {
	                 q.push(nv);
	             }
	         }
	     }
	 }
	 
	 for (i = 1; i <= n; i++) {
	     if (!del[i]) {
	         cnt++;
	         break;
	     }
	 }
	 
	 if (cnt > 0) {
	     tol = 0;
	     for (i = 1; i <= n; i++) {
	         if (!del[i]) {
	             ans[tol++] = i;
	         }
	     }
	 }
	 
	 return cnt > 0;
}

int main(){
	scanf("%d%d%d", &n, &m, &k);
	int i;
	for (i = 0; i < k; i++) {
		int v;
		scanf("%d", &v);
		frt[v] = true;
	}
	
	for (i = 0 ; i < m; i++) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		g[v1].push_back(v2), g[v2].push_back(v1);
		deg[v1]++, deg[v2]++;
	}
	
	double low = 0.0, high = 2.00;
	double ret = 0.00;
	for (i = 0 ; i < 30; i++) {
		double mid = (low + high) / 2.0;
		if (valid(mid)) {
		   low = mid;
		   ret = mid;
		} else {
  		   high = mid;
		}
	}
	
	valid(ret);
	printf("%d\n", tol);
	for (i = 0 ; i < tol; i++) {
		printf("%d ", ans[i]);
	}
	printf("\n");
	return 0;
}
