#include <bits/stdc++.h>
#define MAX_SIZE (100000 + 11)

using namespace std;

// original graph
vector<int> graph[MAX_SIZE];
// the scc the point belongs
int scc[MAX_SIZE];
// low link value, dfs order, whether the point is in the stack
int low[MAX_SIZE], visited[MAX_SIZE], instack[MAX_SIZE]; 
stack<int> st;

// graph that is modified with all cycles compressed as one single point
// and all the edges reversed
vector<int> g2[MAX_SIZE];
// in degree of each verticies in the modified graph
int indegree[MAX_SIZE];
// stores all the leafs that are not roots
vector<pair<int, vector<int> > > leafs;
// a vector that stores all the ids of the root node of the sccs
vector<int> roots;
// a vector that stores all the useful ids in the scc graph
vector<int> useful;

// int treeid[MAX_SIZE];

set<pair<int, int> > ret;

int k = 1;

/*
	tarjan's scc algorithm and in the end we will get the scc of each
	
*/
void tarjan(int v) {
	instack[v] = 1;
	visited[v] = low[v] = k;
	k++;
	st.push(v);
	for (auto nextv : graph[v]) {
		if (!visited[nextv]) {
			tarjan(nextv);
			low[v] = min(low[v], low[nextv]);
		} else if (instack[nextv]) {
			low[v] = min(low[v], visited[nextv]);
		}
	}
	
	if (low[v] == visited[v]) {
		while (st.top() != v) {
			scc[st.top()] = v;
			instack[st.top()] = 0;
			st.pop();
		}
		instack[st.top()] = 0;
		scc[st.top()] = v;
		useful.push_back(v);
		st.pop();
	}
}

void dfs(int v, int ancestor) {
	if ((int) g2[v].size() == 0) {
		leafs[(int) leafs.size() - 1].second.push_back(v);
	}
	
	for (auto nextv : g2[v]) {
		dfs(nextv, ancestor);
	}
}

int main(int argc, char *argv[]) {
	int n, i, j;
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		int v;
		scanf("%d", &v);
		graph[i].push_back(v);
	}
	
	for (i = 1; i <= n; i++) {
		if (!visited[i]) {
			tarjan(i);
		}
	}
	
	// this would compressed the original functional graph to a forest
	for (i = 1; i <= n; i++) {
		for (auto v : graph[i]) {
			// i---->v
			if (scc[v] != scc[i]) {
				g2[scc[v]].push_back(scc[i]);
				indegree[scc[i]]++;
			}
		}
	}
	
	for (auto v : useful) {
		if (indegree[v] == 0) {
			roots.push_back(v);
			leafs.push_back(make_pair(v, vector<int>()));
			dfs(v, v);
		}
	}
	
	for (i = 0 ; i < (int)  leafs.size(); i++) {
		for (j = 1; j < (int) leafs[i].second.size(); j++) {
			if (leafs[i].first != leafs[i].second[j]) {
				ret.insert(make_pair(leafs[i].first, leafs[i].second[j]));
			}
		}
		if (leafs[i].second.size() == 1) {
			if (leafs[i].first != leafs[(i+1) % (int) leafs.size()].second[0]) {
				ret.insert(make_pair(leafs[i].first
									  , leafs[(i+1) % (int) leafs.size()].second[0]));
			}
		} else {	
			if (leafs[i].second[(int) leafs[i].second.size() - 1] !=  leafs[(i+1) % (int) leafs.size()].second[0]) {
				ret.insert(make_pair(leafs[i].second[(int) leafs[i].second.size() - 1]
									  , leafs[(i+1) % (int) leafs.size()].second[0]));
			}
		}
	}
	
	
	
	if ((int) leafs.size() == 1 && (int) leafs[0].second.size() == 1) {
		if (leafs[0].first != leafs[0].second[0]) {
			ret.insert(make_pair(leafs[0].first, leafs[0].second[0]));
		}
	}
		
	printf("%d\n", (int) ret.size());
	for (auto p : ret) {
		cout << p.first << " " << p.second << endl;
	}
	
	return 0;
}
