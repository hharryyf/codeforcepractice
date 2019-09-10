#include <bits/stdc++.h>
#define MAX_SIZE (100000 + 11)

typedef long long ll;

using namespace std;

ll price[MAX_SIZE];

int n, m;

vector<int> graph[MAX_SIZE];

vector<int> rgraph[MAX_SIZE];

bool visited[MAX_SIZE];

stack<int> s;

void dfs_1(int v);

void dfs_2(int v);

vector<vector<int> > arr;

int main(int argc, char *argv[]) {
	int i;
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		scanf("%lld", &price[i]);
	}
	
	scanf("%d", &m);
	
	memset(visited, false, sizeof(visited));
	
	while (m > 0) {
		int v, u;
		scanf("%d%d", &v, &u);
		graph[v].push_back(u);
		rgraph[u].push_back(v);
		m--;
	}
	
	for (i = 1; i <= n; i++) {
		if (!visited[i]) {
			dfs_1(i);
		}
	}
	
	memset(visited, false, sizeof(visited));
	
	
	while (!s.empty()) {
		if (!visited[s.top()]) {
			arr.push_back(vector<int>());
			dfs_2(s.top());
		}
		s.pop();
	}
	
	ll ans = 1ll;
	ll pp = 0ll;
	for (auto vc : arr) {
		pair<ll, int> p = pair<ll, int>(price[vc[0]], 0);
		for (auto num : vc) {
			if (p.first > price[num]) {
				p = pair<ll, int>(price[num], 1);
			} else if (p.first == price[num]) {
				p = pair<ll, int>(p.first, p.second + 1);
			}
		}
		ans *= p.second;
		ans = ans % 1000000007;
		pp = (pp + p.first);
	}
	
	cout << pp << " " << ans << endl;
	return 0;
}

void dfs_1(int v) {
	if (visited[v]) return;
	visited[v] = true;
	for (auto nextv : graph[v]) {
		if (!visited[nextv]) {
			dfs_1(nextv);
		}
	}
	s.push(v);
}

void dfs_2(int v) {
	if (visited[v]) return;
	visited[v] = true;
	arr[(int) arr.size() - 1].push_back(v);
	for (auto nextv : rgraph[v]) {
		if (!visited[nextv]) {
			dfs_2(nextv);
		}
	} 
}
