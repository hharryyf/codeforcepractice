#include <bits/stdc++.h>

using namespace std;

struct Edge {
	int vx, vy;
	double dist;
};


static bool cmp(Edge &a, Edge &b) {
	return a.dist < b.dist;
}

vector<Edge> edges;

int s, t; 

pair<double, double> vc[601];

int f[601];

int find(int x) {
	if (x == f[x]) return x;
	return f[x] = find(f[x]);
}

void unionset(int x, int y) {
	int a = find(x), b = find(y);
	f[a] = b; 
}

double Kruskal() {
	int i;
	for (i = 0 ; i < t; i++) {
		f[i] = i;
	}
	sort(edges.begin(), edges.end(), cmp);
	int cnt = t - s;
	double current = 0.0;
	for (auto edg : edges) {
		if (cnt <= 0) break;
		if (find(edg.vx) != find(edg.vy)) {
			cnt--;
			current = edg.dist;
			unionset(edg.vx, edg.vy);
		}
	}
	
	return current;	
}

int main() {
	int T;
	cin >> T;
	while (T > 0) {
		cin >> s >> t;
		edges = vector<Edge>();
		for (int i = 0 ; i < t; i++) {
			cin >> vc[i].first >> vc[i].second;
		}
		
		for (int i = 0 ; i < t; i++) {
			for (int j = i + 1 ; j < t; j++) {
				edges.push_back(Edge{i, j, sqrt((vc[i].first - vc[j].first) * (vc[i].first - vc[j].first) 
				+ (vc[i].second - vc[j].second) * (vc[i].second - vc[j].second))});
			}
		}
		
		printf("%.2lf\n", Kruskal());
		T--;
	}
	return 0;
}
