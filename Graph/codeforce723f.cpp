#include <bits/stdc++.h>
#define MAX_SIZE 200011

using namespace std;

struct Edge {
	int x, y;
};

int f[MAX_SIZE];


vector<int> g[MAX_SIZE];

vector<Edge> ret;

set<int> sset;
set<int> tset;

int n, m;
int s, t, ds, dt;

int find(int x) {
	if (f[x] == x) return f[x];
	return f[x] = find(f[x]);
}

void unionset(int a, int b) {
	int x = find(a), y = find(b);
	if (rand() % 2) {
		f[x] = y;
	} else {
		f[y] = x;
	}
}

bool Kruskal() {
	int i;
	for (i = 1; i <= n; i++) f[i] = i;
	// not connecting to s and t
	for (i = 1; i <= n; i++) {
		if (i == s || i == t) continue;
		for (auto nextv : g[i]) {
			if (nextv != s && nextv != t) {
				if (find(nextv) != find(i)) {
					ret.push_back(Edge{i, nextv});
					unionset(nextv, i);
				}
			}
		}
	}
	
	// connect to only s but not t
	for (auto nextv : g[s]) {
		if (nextv != t && tset.find(nextv) == tset.end() && find(nextv) != find(s)) {
			unionset(nextv, s);
			ret.push_back(Edge{s, nextv});
			ds--;
		}
	}
	// connect to only t but not s
	
	for (auto nextv : g[t]) {
		if (nextv != s && sset.find(nextv) == sset.end() && find(nextv) != find(t)) {
			unionset(nextv, t);
			ret.push_back(Edge{t, nextv});
			dt--;
		}
	}
	
	if (ds < 0 || dt < 0) return false;
	// otherwise
	for (auto nextv : g[s]) {
		if (ds > 0) {
			if (nextv != t && find(nextv) != find(s)) {
				unionset(nextv, s);
				ret.push_back(Edge{s, nextv});
				ds--;
			}
		}
	}
	
	for (auto nextv : g[t]) {
		if (dt > 0) {
			if (nextv != s && find(nextv) != find(t)) {
				unionset(nextv, t);
				ret.push_back(Edge{t, nextv});
				dt--;
			}
		}
	}
	
	if (ds < 0 || dt < 0) return false;
	if (sset.find(t) != sset.end()) {
		if (find(s) != find(t)) {
			ret.push_back(Edge{t, s});
			unionset(s, t);
			dt--;
			ds--;
		}
	}
	
	if (ds < 0 || dt < 0) return false;
	
	for (i = 1; i <= n; i++) {
		if (find(i) != find(1)) return false;
	}
	
	return true;
}

int main() {
	cin >> n >> m;
	
	for (int i = 0 ; i < m; i++) {
		int v1, v2;
		cin >> v1 >> v2;
		g[v1].push_back(v2);
		g[v2].push_back(v1);				
	}
	
	cin >> s >> t >> ds >> dt;
	
	for (auto nextv : g[s]) {
		sset.insert(nextv);
	}
	
	for (auto nextv : g[t]) {
		tset.insert(nextv);
	}
	
	if (!Kruskal()) {
		cout << "No" << endl;
	} else {
		cout << "Yes" << endl;
		for (auto edge : ret) {
			cout << edge.x << " " << edge.y << endl;
		}
	}
	return 0;
}
