#include <bits/stdc++.h>

using namespace std;

class Graph {
public:
	Graph(int n) {
		this->graph = vector<vector<int> >(n, vector<int>());
		this->nV = n;
	}
	
	void addEdge(int v1, int v2) {
		graph[v1].push_back(v2);
		graph[v2].push_back(v1);
	}
	
	vector<vector<int> > bridges() {
		ret = vector<vector<int> >();
		this->low = vector<int>(nV, 0);
		this->visited = vector<int>(nV, 0);
		this->timest = 1;
		for (int i = 0 ; i < this->nV; i++) {
			if (!visited[i]) {	
				dfs(i, -1);
			}
		}
		return ret;
	}
private:
	int nV;
	int timest;
	vector<vector<int> > graph;
	vector<vector<int> > ret;
	vector<int> visited;
	vector<int> low;
	void dfs(int v, int prev) {
		visited[v] = timest++;
		low[v] = visited[v];
		for (auto nextv : graph[v]) {
			if (nextv != prev) {
				if (!visited[nextv]) {
					dfs(nextv, v);
					low[v] = min(low[v], low[nextv]);
					if (visited[v] < low[nextv]) {
						vector<int> p = vector<int>(2, 0);
						p[0] = v;
						p[1] = nextv;
						ret.push_back(p);
					}
				} else {
					low[v] = min(low[v], visited[nextv]);
				}
			}
		}
	}
};

int main(int argc, char *argv[]) {
	Graph g = Graph(8);
	g.addEdge(0,1);
	g.addEdge(1,2);
	g.addEdge(2,0);
	g.addEdge(2,3);
	g.addEdge(3,4);
	g.addEdge(4,5);
	g.addEdge(5,6);
	g.addEdge(6,4);
	cout << "the bridges of the graph are " << endl;
	for (auto e : g.bridges()) {
		cout << e[0] << "--" << e[1] << endl; 
	}
	return 0;
}
