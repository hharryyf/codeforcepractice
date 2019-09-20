#include <bits/stdc++.h>

using namespace std;

class Graph {
public:
	Graph(int n) {
		this->graph = vector<vector<int> >(n, vector<int>());
		this->nV = n;
	}
	
	void addEdge(int v1, int v2) {
		assert(v1 < nV && v1 >= 0 && v2 < nV && v2 >= 0);
		graph[v1].push_back(v2);
		graph[v2].push_back(v1);
	}
	
	vector<int> tarjan_ap() {
		this->parent = vector<int>(nV, -1);
		this->visited = vector<int>(nV, 0);
		this->low = vector<int>(nV, 0);
		this->timest = 1;
		for (int i = 0 ; i < nV; i++) {
			if (!visited[i]) {
				dfs(i);	
			}
		}
		
		vector<int> ret = vector<int>();
		for (auto nextv : arps) {
			ret.push_back(nextv);
		}
		return ret;
	}
	
private:
	vector<vector<int> > graph;
	int nV;
	// parent of a vertex
	vector<int> parent;
	// dfs order
	vector<int> visited;
	// low link value of a vertex
	vector<int> low;
	// articulation points
	unordered_set<int> arps;
	int timest;
	
	void dfs(int v) {
		visited[v] = timest++;
		low[v] = visited[v];
		int childcount = 0;
		bool isap = false;
		for (auto nextv : graph[v]) {
			if (!visited[nextv]) {
				parent[nextv] = v;
				childcount++;
				dfs(nextv);
				low[v] = min(low[v], low[nextv]);
				if (visited[v] <= low[nextv]) {
					isap = true;
				}
			} else if (nextv != parent[v]) {
				low[v] = min(low[v], visited[nextv]);
			}
		}
		
		if (parent[v] == -1 && childcount >= 2) {
			arps.insert(v);
		}
		
		if (parent[v] != -1 && isap) {
			arps.insert(v);
		}
	}
};

int main(int argc, char *argv[]) {
	Graph g = Graph(8);
	g.addEdge(0,1);
	g.addEdge(0,2);
	g.addEdge(1,2);
	g.addEdge(2,3);
	g.addEdge(3,4);
	g.addEdge(4,5);
	g.addEdge(5,6);
	g.addEdge(4,6);
	g.addEdge(5,7);
	cout << "the articulation points are " << endl;
	for (auto v : g.tarjan_ap()) {
		cout << v << " ";
	}
	cout << endl;
	return 0;
}
