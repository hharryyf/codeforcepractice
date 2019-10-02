#include <bits/stdc++.h>
#define MAX_SIZE (524288 + 12)
#define INF 900000000000000ll

typedef long long ll;

using namespace std;

vector<pair<int, ll> > graph[MAX_SIZE];


vector<ll> dist = vector<ll>(MAX_SIZE, INF);
int visited[MAX_SIZE];
// 0 means it is not the original graph's vertex
int mymap[MAX_SIZE];
int n;

int getdown(int index) {
	return index * 2 - 1;
}

int getup(int index) {
	return index * 2;
}

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		mymap[l] = getdown(index);
		return;
	}	
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	graph[getdown(index)].push_back(make_pair(getdown(index * 2), 0ll));
	graph[getdown(index)].push_back(make_pair(getdown(index * 2 + 1), 0ll));
	if (l != mid) {
		graph[getup(index * 2)].push_back(make_pair(getup(index), 0ll));
	} else {
		graph[getdown(index * 2)].push_back(make_pair(getup(index), 0ll));
	}
	if (mid + 1 != r) {
		graph[getup(index * 2 + 1)].push_back(make_pair(getup(index), 0ll));
	} else {
		graph[getdown(index * 2 + 1)].push_back(make_pair(getup(index), 0ll));
	}
}

void update(int start, int end, int l, int r, int index, int ver, int tp, ll val) {
	if (start > end || l > r || start > r || l > end) return;
	if (start <= l && r <= end) {
		if (tp == 2) {
			graph[mymap[ver]].push_back(make_pair(getdown(index), val));
		} else if (tp == 3) {
			if (l == r) {
				graph[getdown(index)].push_back(make_pair(mymap[ver], val));
			} else {
				graph[getup(index)].push_back(make_pair(mymap[ver], val));
			}
		}
		return;
	}
	
	int mid = l + (r - l) / 2;
	update(start, end, l, mid, index * 2, ver, tp, val);
	update(start, end, mid + 1, r, index * 2 + 1, ver, tp, val);
}

void dijkatra(int s) {
	priority_queue<pair<ll, int> , vector<pair<ll, int> >, greater<pair<ll, int> > > q;
	q.push(make_pair(0ll, mymap[s]));
	dist[mymap[s]] = 0ll;
	while (!q.empty()) {
		pair<ll, int> nextp = q.top();
		int nextv = nextp.second;
		ll ds = nextp.first;
		q.pop();
		if (visited[nextv]) continue;
		visited[nextv] = 1;
		dist[nextv] = ds;
		for (auto np : graph[nextv]) {
			if (!visited[np.first] && dist[np.first] > ds + np.second) {
				dist[np.first] = ds + np.second;
				q.push(make_pair(dist[np.first], np.first));
			}
		}
	}
}

int main(int argc, char *argv[]) {
	int q, s;
	scanf("%d%d%d", &n, &q, &s);
	build(1, n, 1);
	while (q > 0) {
		int t, u, v, l, r;
		ll val;
		scanf("%d", &t);
		if (t == 1) {
			scanf("%d%d%lld", &u, &v, &val);
			graph[mymap[u]].push_back(make_pair(mymap[v], val));
		} else {
			scanf("%d%d%d%lld", &u, &l, &r, &val);
			update(l, r, 1, n, 1, u, t, val);
		}
		q--;
	}
	/*
	for (int i = 1; i <= n; i++) {
		cout << mymap[i] << ": ";
		for (auto nextv : graph[mymap[i]]) {
			cout << nextv.first << " ";
		}
		cout << endl;
	}*/
	
	dijkatra(s);
	
	
	for (int i = 1; i <= n; i++) {
		if (dist[mymap[i]] < INF) {
			printf("%lld ", dist[mymap[i]]);
		} else {
			printf("-1 ");
		}
	}
	cout << endl;
	return 0;
}
