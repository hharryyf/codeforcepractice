#include <bits/stdc++.h>
#define MAX_SIZE 111
using namespace std;

int deg[MAX_SIZE];
char g[MAX_SIZE][MAX_SIZE];
int n;
bool visited[MAX_SIZE];

int main() {
	int i;
	scanf("%d", &n);
	for (i = 0; i < n; ++i) {
		scanf("%s", g[i]);
	}
	
	for (i = 0; i < n; ++i) {
		scanf("%d", &deg[i]);
		deg[i] = -deg[i];
	}
	
	vector<int> ans;
	set<pair<int, int>> s;
	for (i = 0 ; i < n; ++i) {
		s.insert(make_pair(deg[i], i));
	}
	
	while (!s.empty()) {
		auto t = s.lower_bound(make_pair(0, -1));
		if (t == s.end() || t->first != 0) break;
		auto p = *t;
		if (visited[p.second]) {
			printf("-1\n");
			return 0;
		}
		visited[p.second] = 1;
		ans.push_back(p.second);
		for (i = 0; i < n; ++i) {
			if (g[p.second][i] == '1') {
				s.erase(make_pair(deg[i], i));
				deg[i]++;
				s.insert(make_pair(deg[i], i));
			}
		}
	}
	
	printf("%d\n", (int) ans.size());
	if (!ans.empty()) {
		for (auto v : ans) {
			printf("%d ", v+1);
		}
		printf("\n");
	}
	return 0;
}