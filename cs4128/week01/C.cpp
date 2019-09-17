#include <bits/stdc++.h>
#define MAX_SIZE 24

using namespace std;

int arr[MAX_SIZE];
int n, k;
vector<int> ans;
int sm;

void dfs(int curr, vector<int> a, int index) {
	if (curr > sm) {
		sm = curr;
		ans = a;
	}
	
	for (int i = index; i <= k; i++) {
		if (arr[i] + curr <= n) {
			a.push_back(arr[i]);
			dfs(arr[i] + curr, a, i + 1);
			a.pop_back();
		}
	}
	
}

int main(int argc, char *argv[]) {
	int i;
	while (scanf("%d%d", &n, &k) == 2) {
		for (i = 1; i <= k; i++) {
			scanf("%d", &arr[i]);
		}		
		
		sm = 0;
		ans = vector<int>();
		
		dfs(sm, ans, 1);
		
		for (auto v : ans) {
			cout << v << " ";
		}
		cout << "sum:" << sm << endl;
	}
	return 0;
}
