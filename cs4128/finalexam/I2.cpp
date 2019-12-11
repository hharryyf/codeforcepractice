#include <bits/stdc++.h>
#define MAX_SIZE 4011
using namespace std;

vector<int> disc;
vector<int> tmp;

unordered_set<int> g[MAX_SIZE];
int visited[MAX_SIZE];
int n, m;

char st[3];
int oper[MAX_SIZE >> 1][3];

int getindex(int val) {
	return lower_bound(disc.begin(), disc.end(), val) - disc.begin();
}

void addbridge(int v, int u) {
	int v1 = getindex(v), v2 = getindex(u);
	g[v1].insert(v2);
	g[v2].insert(v1);
}



void removeroad(int u, int v) {
	if (u > v) swap(u, v);
	int id1 = getindex(u), id2 = getindex(v);
	if (u <= n && v <= n) {
		g[id1].erase(id2);	
	} else {
		g[id2].erase(id1);
	}
}

void dfs(int v) {
	visited[v] = 1;
	for (auto nv : g[v]) {
		if (!visited[nv]) {
			dfs(nv);
		}
	}
}

bool connected(int u, int v) {
	memset(visited, 0, sizeof(visited));
	int id1 = getindex(u), id2 = getindex(v);
	dfs(id1);
	return visited[id2];
}

int main() {
	scanf("%d%d", &n, &m);
	int i;
	for (i = 0 ; i < m; i++) {
		scanf("%s%d%d", st, &oper[i][1], &oper[i][2]);
		if (st[0] == 'A') {
			oper[i][0] = 0;
		} else if (st[0] == 'Q') {
			oper[i][0] = 1;
		} else {
			oper[i][0] = 2;
		}
		tmp.push_back(oper[i][1]);
		tmp.push_back(oper[i][2]);
	}
	
	sort(tmp.begin(), tmp.end());
	for (i = 0 ; i < (int) tmp.size(); i++) {
		if (i == 0 || tmp[i] != tmp[i-1]) {
			disc.push_back(tmp[i]);
		}
	}
	int q = disc.size();
	for (i = 0; i < q - 1; i++) {
		if (disc[i] <= n && disc[i+1] <= n) {
			g[i].insert(i+1);
		    //cout << "add road " << disc[i] << " " << disc[i + 1] << endl;
		}
		
		if (disc[i] > n && disc[i+1] > n) {
			g[i+1].insert(i);
			//cout << "add road " << disc[i+1] << " " << disc[i] << endl;
		}
	}
	
	for (i = 0; i < m; i++) {
		if (oper[i][0] == 0) {
			addbridge(oper[i][1], oper[i][2]);
		}  else if (oper[i][0] == 2) {
			removeroad(oper[i][1], oper[i][2]);
		} else {
			cout << connected(oper[i][1], oper[i][2]) << endl;
		}
	}
	return 0;
}
