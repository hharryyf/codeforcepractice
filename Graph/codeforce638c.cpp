#include <bits/stdc++.h>
#define MAX_SIZE 200011

using namespace std;

vector<int> graph[MAX_SIZE];
map<pair<int, int>, int> mymap;
vector<int> ans[MAX_SIZE];
int anssize = 0;

void dfs(int v, int prev, int prevday);

int main(int argc, char *argv[]) {
	int n, i;
	scanf("%d", &n);
	for (i = 0 ; i < n - 1; i++) {
		int v, u;
		scanf("%d%d", &v, &u);
		graph[v].push_back(u);
		graph[u].push_back(v);
		mymap[pair<int, int>(u, v)] = i + 1;
		mymap[pair<int, int>(v, u)] = i + 1;
	}		
	
	dfs(1, -1, 0);
	printf("%d\n", anssize);
	for (i = 1; i <= anssize; i++) {
		printf("%d", (int) ans[i].size());
		for (auto num : ans[i]) {
			printf(" %d", num);
		}
		
		printf("\n");
	}	
	
	return 0;
}

void dfs(int v, int prev, int prevday) {
	int day = 0;
	for (auto nextnode : graph[v]) {
		if (nextnode == prev) continue;
		day++;
		if (day == prevday) {
			day++;
		}
		
		ans[day].push_back(mymap[pair<int, int>(nextnode, v)]);
		dfs(nextnode, v, day);
	}
	
	anssize = max(anssize, day);
}
