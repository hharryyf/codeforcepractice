#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int> > sol;

int visited[9];

void dfs(int step, vector<int> curr) {
	if (step > 1 && step <= 9) {
		for (int i = 1; i < step - 1; i++) {
			if (abs(curr[step - 1] - curr[i]) == abs(step - 1 - i)) {
				return;
			}
		}
	}
	
	if (step == 9) {
		sol.push_back(curr);
		return;
	}
	
	for (int i = 1; i <= 8; i++) {
		if (!visited[i]) {
			curr[step] = i;
			visited[i] = 1;
			dfs(step + 1, curr);
			visited[i] = 0;
		}
	}
}

int main() {
	dfs(1, vector<int>(9, 0));
	// cout << sol.size() << endl;
	int i = 1;
	vector<int> vc = vector<int>(9, 0);
	while (scanf("%d%d%d%d%d%d%d%d", &vc[1], &vc[2], &vc[3], &vc[4], &vc[5], &vc[6], &vc[7], &vc[8]) != EOF) {
		int ans = 8;
		for (auto v : sol) {
			int cnt = 0;
			for (int i = 1; i <= 8; i++) {
				if (v[i] != vc[i]) cnt++;
			}
			ans = min(ans, cnt);
		}
		cout << "Case " << i << ": " << ans << endl;
		i++;
	}
	return 0;
}
