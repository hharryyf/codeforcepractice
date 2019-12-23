#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 513
#define INF 1000000000000ll

typedef long long ll;
using namespace std;

vector<pair<int, ll> > g[MAX_SIZE];
vector<pair<int, ll> > h[MAX_SIZE];
ll dist[MAX_SIZE][2];
int visited[MAX_SIZE];
int pre[MAX_SIZE][2];
int n;

void init() {
	 int i;
	 for (i = 0 ; i < MAX_SIZE; i++) {
	 	 g[i].clear();
	 	 h[i].clear();
	 }
}

void dijkstra(int src, int dim) {
	 priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll,int> > > q;
	 int i;
	 for (i = 0 ; i < MAX_SIZE; i++) {
	 	 dist[i][dim] = INF;
	 	 visited[i] = 0;
	 	 pre[i][dim] = 0;
	 }
	 
	 dist[src][dim] = 0;
	 q.push(make_pair(0, src));
	 
	 while (!q.empty()) {
	 	   auto p = q.top();
	 	   q.pop();
	 	   if (visited[p.second]) continue;
	 	   visited[p.second] = 1;
	 	   dist[p.second][dim] = p.first;
	 	   for (auto np : g[p.second]) {
		   	   if (!visited[np.first]) {
			   	  if (dist[np.first][dim] > np.second + p.first) {
				  	   dist[np.first][dim] = np.second + p.first; 			  	 
					   q.push(make_pair(np.second + p.first, np.first));	 
				       pre[np.first][dim] = p.second; 
				  }	  
               }	
		   }
	 }
}

int main() {
	int s, e;
	int cnt = 0;
	while (scanf("%d%d%d", &n, &s, &e) != EOF) {
        init();
        cnt++;
        if (cnt != 1) {
		   printf("\n");
		}
        int m, k;
		scanf("%d", &m);
		int i;
		for (i = 0 ; i < m; i++) {
			int v1, v2;
			ll w;
			scanf("%d%d%lld", &v1, &v2, &w);
			g[v1].emplace_back(v2, w);
			g[v2].emplace_back(v1, w);
		} 
		
		dijkstra(s, 0);
		dijkstra(e, 1);
		
		scanf("%d", &k);
		for (i = 0 ; i < k; i++) {
			int v1, v2;
			ll w;
			scanf("%d%d%lld", &v1, &v2, &w);
			h[v1].emplace_back(v2, w);
			h[v2].emplace_back(v1, w);
		}
		// ans without the special ticket
		ll ans = dist[e][0];
		int opts = -1, opte = -1;
		// extract the final answer
		for (i = 1 ; i <= n; i++) {
			for (auto np : h[i]) {
				if (dist[i][0] + np.second + dist[np.first][1] < ans) {
				   opts = i;
				   opte = np.first;
				   ans = dist[i][0] + np.second + dist[np.first][1];
				}
			}
		}
		
		stack<int> st;
		int curr = -1;
		// we don't need the special ticket
		if (opts == -1) {
		   curr = e;
		   while (curr != 0) {
  		        st.push(curr);
  		        curr = pre[curr][0];
		   }
		   printf("%d", st.top());
		   st.pop();
		   while (!st.empty()) {
		   		 printf(" %d", st.top());
		   		 st.pop();
		   }
		   printf("\n");
		   printf("Ticket Not Used\n");
		   printf("%lld\n", ans);
		} else {
           curr = opts;
           while (curr != 0) {
  		        st.push(curr);
  		        curr = pre[curr][0];
		   }
		   printf("%d", st.top());
		   st.pop();
		   while (!st.empty()) {
		   		 printf(" %d", st.top());
		   		 st.pop();
		   }
		   curr = opte;
		   while (curr != 0) {
		   		 printf(" %d", curr);
		   		 curr = pre[curr][1];
		   }
		   printf("\n");
		   printf("%d\n", opts);
		   printf("%lld\n", ans);
		}
	}
	return 0;
}
