#include <bits/stdc++.h>
#define MAX_SIZE 1011
#define INF 1000000000000000
typedef long long ll;
using namespace std;

vector<pair<int, ll> > g[MAX_SIZE];

bool visited[MAX_SIZE];
ll dist[MAX_SIZE];

struct edge {
	int start, end;
	ll w;
};

vector<edge> edg;
vector<edge> ans;

void addedge(int st, int ed, ll w) {
	g[st].emplace_back(ed, w);
	g[ed].emplace_back(st, w);
}

void init() {
	int i;
	for (i = 0 ; i < MAX_SIZE; i++) {
		dist[i] = INF;
		visited[i] = false;
	}
}

ll Dijkstra(int s, int t) {
	init();	
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int> >> q;
	dist[s] = 0;
	q.push(make_pair(0, s));
	while (!q.empty()) {
		pair<ll, int> p = q.top();
		q.pop();
		if (visited[p.second]) continue;
		visited[p.second] = true;
		dist[p.second] = p.first;
		for (auto nv : g[p.second]) {
			if (!visited[nv.first] && nv.second + dist[p.second] < dist[nv.first]) {
				dist[nv.first] = nv.second + dist[p.second];
				q.push(make_pair(dist[nv.first], nv.first));
			}
		}
	}
	
	return dist[t];
}

int main() {
	int n, m, s, t, i;
	ll 	L;
	scanf("%d%d%lld%d%d", &n, &m, &L, &s, &t);
	for (int i = 1; i <= m; i++) {
		int v1, v2;
		ll w;
		scanf("%d%d%lld", &v1, &v2, &w);
		if (w != 0) {
			addedge(v1, v2, w);
			ans.push_back(edge{v1, v2, w});
		} else {
			edg.push_back(edge{v1, v2, w});	
		}
	}
	
	ll ret = Dijkstra(s, t);
	if (ret < L) {
		printf("NO\n");
		return 0;
	} else if (ret == L) {
		printf("YES\n");
		for (auto e : ans) {
			printf("%d %d %lld\n", e.start, e.end, e.w);
		}
		
		for (auto e : edg) {
			printf("%d %d 1000000000000000\n", e.start, e.end);
		}
		return 0;
	}	
	
	for (i = (int) edg.size() - 1; i >= 0; i--) {
		addedge(edg[i].start, edg[i].end, 1);
		ans.push_back(edge{edg[i].start, edg[i].end, 1});
		ret = Dijkstra(s, t);
		if (ret <= L) {
			ans[ans.size() - 1].w = L - ret + 1;
			int j;
			for (j = i - 1; j >= 0; j--) {
				ans.push_back(edge{edg[j].start, edg[j].end, INF});
			}
			printf("YES\n");
			for (auto e : ans) {
				printf("%d %d %lld\n", e.start, e.end, e.w);
			}
			return 0;
		}
	}
	
	printf("NO\n");
	return 0;
}
