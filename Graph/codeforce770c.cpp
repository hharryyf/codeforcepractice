#include <bits/stdc++.h>
#define MAX_SIZE (100000 + 11)

using namespace std;

vector<int> graph[MAX_SIZE];
vector<int> arr;
int visited[MAX_SIZE];
bool fail = false;
vector<int> ans;
void dfs(int v);

int main(int argc, char *argv[]) {
	int n, k, i;
	scanf("%d%d", &n, &k);
	for (i = 0; i < k; i++) {
		int v;
		scanf("%d", &v);
		arr.push_back(v);
	}
	
	for (i = 1 ; i <= n; i++) {
		int m;
		scanf("%d", &m);
		while (m > 0) {
			int v;
			scanf("%d", &v);
			graph[i].push_back(v);
			m--;
		}
	}
	
	for (auto cu : arr) {
		fail = false;
		dfs(cu);
		if (fail) {
			printf("-1\n");
			return 0;
		}
	}
	
	printf("%d\n", (int) ans.size());
	for (auto num : ans) {
		printf("%d ", num);
	}
	printf("\n");
	return 0;
}

void dfs(int v) {
	if (visited[v] == 2) return;
	visited[v] = 1;
	for (auto nextv : graph[v]) {
		if (visited[nextv] == 1) {
			fail = true;
		}
		
		if (!visited[nextv]) {
			dfs(nextv);
		}
	}
	
	ans.push_back(v);
	visited[v] = 2;
}
