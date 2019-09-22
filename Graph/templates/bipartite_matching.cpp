#include <bits/stdc++.h>
#define MAX_SIZE 200011

using namespace std;

vector<int> p1;
vector<int> p2;

vector<int> graph[MAX_SIZE];

int visited[MAX_SIZE];

int dp[2001][2001];

bool bfs(int v) {
	queue<pair<int, int> > q;
	q.push(make_pair(v, 1));
	while (!q.empty()) {
		pair<int, int> p = q.front();
		q.pop();
		if (visited[p.first]) continue;
		visited[p.first] = p.second; 
		if (p.second == 2) {
			p2.push_back(p.first);
		} else {
			p1.push_back(p.first);
		}
		for (auto nextv : graph[p.first]) {
			if (visited[nextv] && visited[nextv] == p.second) return false;
			if (!visited[nextv]) {
				q.push(make_pair(nextv, (p.second == 1 ? 2 : 1)));
			}
		}
	}
	
	return true;
}

int main() {
	int l, r;
	int c, n;
	cin >> l >> r >> n >> c;
	if (l + r > n) {
		cout << "impossible" << endl;
		return 0;
	}
	
	if (c == 0) {
		cout << "yes" << endl;
		return 0;
	}
	
	for (int i = 0 ; i < c; i++) {
		int v1, v2;
		cin >> v1 >> v2;
		graph[v1].push_back(v2);
		graph[v2].push_back(v1);
	}
	vector<pair<int, int> > vc;
	vc.push_back(make_pair(0,0));
	for (int i = 1; i <= n; i++) {
		if (!visited[i]) {
			p1 = vector<int>();
			p2 = vector<int>();
			if (bfs(i)) {
				vc.push_back(make_pair((int) p1.size(), (int) p2.size()));
			} else {
				cout << "impossible" << endl;
				return 0;
			}
		}
	}
	
	
	dp[0][vc[0].first] = 1;
	dp[0][vc[0].second] = 1;
	
	for (int i = 1; i < (int) vc.size(); i++) {
		dp[i][0] = 1;
	}
	
	int j;
	for (int i = 1; i < (int) vc.size(); i++) {
		for (j = 0; j <= n; j++) {
			if (vc[i].first + j <= n) {
				dp[i][vc[i].first + j] = dp[i-1][j];
			}
			
			if (vc[i].second + j <= n) {
				dp[i][vc[i].second + j] = dp[i-1][j];
			}
		}
	}
	
	for (int i = 1; i <= l; i++) {
		if (dp[(int) vc.size() - 1][i] == 1 && n - i <= r) {
			cout << "yes" << endl;
			return 0;
		}
	}
	
	cout << "false" << endl;
	return 0;
}


