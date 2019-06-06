#include <bits/stdc++.h>
#define MAX_VERTEX 1025

using namespace std;

// dist from A->B in graph1
long long dist1[MAX_VERTEX][MAX_VERTEX];
// the dist from src to all the other vertex
long long dist[MAX_VERTEX];
vector<pair<int, long long> > graph[MAX_VERTEX];
// taxi reachable graph
vector<pair<int, long long> > rgraph[MAX_VERTEX];
// taxi distance
long long taxirange;
// taxi money
long long taximoney;
// do dijkstra on graph g which starting vertex is g and fill the d array
void Dijkstra(vector<pair<int, long long> > g[MAX_VERTEX], int nV, int src, long long d[]);

int main(int argc, char *argv[]) {
	int nV, nE, src, dest;
	long long INF = 2000000000002;
	int i, j;
	// vertex, edge
	cin >> nV >> nE;
	// source, destination
	cin >> src >> dest;
	
	for (i = 1 ; i <= nV ; i++) {
		for (j = 1; j <= nV; j++) {
			if (i != j) {
				dist1[i][j] = INF;
			}
		}
	}
	
	for (i = 0 ; i < nE; i++) {
		int st, ed;
		long long w;
		cin >> st >> ed >> w;
		dist1[st][ed] = min(dist1[st][ed], w);
		dist1[ed][st] = min(dist1[ed][st], w);
	}
	
	for (i = 1; i <= nV; i++) {
		for (j = 1; j <= nV; j++) {
			if (dist1[i][j] < INF && i != j) {
				graph[i].push_back(pair<int, long long>(j, dist1[i][j]));
			}
		}
	}
	
	
	for (i = 1; i <= nV; i++) {
		// cout << graph[i].size() << endl;
		Dijkstra(graph, nV, i, dist1[i]);
	}
	
	for (i = 1; i <= nV; i++) {
		// input the taxirange at vertex i and taximoney at i
		cin >> taxirange >> taximoney;
		for (j = 1; j <= nV; j++) {
			if (i == j) {
				continue;
			} 
			
			if (dist1[i][j] <= taxirange) {
				rgraph[i].push_back(pair<int, long long>(j, taximoney));
			}
		}
	}
	
	
	Dijkstra(rgraph, nV, src, dist);
	
	if (dist[dest] >= INF) {
		cout << -1 << endl;
		return 0;
	}
	cout << dist[dest] << endl;
	return 0;
}

struct cmp {
	bool operator()(const pair<int, long long> &p1, const pair<int, long long> &p2) {
		return p1.second > p2.second;	
	}
};

// do dijkstra on graph g which starting vertex is g and fill the d array
void Dijkstra(vector<pair<int, long long> > g[], int nV, int src, long long d[]) {
	int i;
	long long INF = 2000000000002;
	priority_queue<pair<int, long long> , vector<pair<int, long long> >, cmp> q =  
			priority_queue<pair<int, long long> , vector<pair<int, long long> >, cmp>();
	unordered_set<int> visited = unordered_set<int>();
	for (i = 1; i <= nV; i++) {
		d[i] = INF;
	}
	d[src] = 0;
	visited.insert(src);
	for (auto p : g[src]) {
		if (p.second != INF && p.first != src) {
			q.push(p);
		}
	}
	
	for (i = 1; i < nV; i++) {
		int index = -1;
		long long weight = INF;
		while (!q.empty()) {
			pair<int, long long> p = q.top();
			q.pop();
			// the vertex has not been visited
			if (visited.find(p.first) == visited.end()) {
				weight = p.second;
				index = p.first;
				break;
			}
		}
		
		// no remaining vertex
		if (index == -1) return;
		// update the shortest path from src to index as weight
		visited.insert(index);
		d[index] = weight;
		
		// relexation
		for (auto it : g[index]) {
			if (visited.find(it.first) == visited.end()) {
				q.push(pair<int, long long>(it.first, it.second + weight));
			}
		}
	}
}
