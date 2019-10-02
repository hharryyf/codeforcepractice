#include <bits/stdc++.h>
#define INF 2000000000ll
#define MAX_SIZE 511
typedef long long ll;

using namespace std;

ll dist[MAX_SIZE][MAX_SIZE];
ll arr[MAX_SIZE][MAX_SIZE];
vector<int> current;
stack<int> rv;
/*
	Let's work backward, everytime when adding in a new point 
	we calculate the pairwise distance and then do the floyd relaxation procedure
*/

stack<ll> ans;

int main() {
	int n, i, j;
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			cin >> arr[i][j];
			if (i != j) {
				dist[i][j] = INF;
			}
		}
	}
	
	for (i = 0 ; i < n; i++) {
		int v;
		cin >> v;
		rv.push(v);
	}
	
	while (!rv.empty()) {
		int v = rv.top();
		rv.pop();
		for (i = 0 ; i < (int) current.size(); i++) {
			dist[v][current[i]] = min(dist[v][current[i]], arr[v][current[i]]);
			dist[current[i]][v] = min(dist[current[i]][v], arr[current[i]][v]);
		}
		current.push_back(v);
		for (i = 0 ; i < (int) current.size(); i++) {
			for (j = 0 ; j < (int) current.size(); j++) {
				dist[v][current[j]] = min(dist[v][current[j]], dist[v][current[i]] + dist[current[i]][current[j]]);
				dist[current[j]][v] = min(dist[current[j]][v], dist[current[j]][current[i]] + dist[current[i]][v]);
			}
		}
		/*
		cout << "size: " << current.size() << endl;
		for (i = 0 ; i < (int) current.size(); i++) {
			cout << current[i] << " ";
		}
		cout << endl;*/
		
		for (i = 0 ; i < (int) current.size(); i++) {
			for (j = 0 ; j < (int) current.size(); j++) {
				dist[current[i]][current[j]] = min(dist[current[i]][current[j]], dist[current[i]][v] + dist[v][current[j]]);
			}
		}
		
		ll curr = 0ll;
		// cout << v << endl;
		for (i = 1 ; i <= n; i++) {
			for (j = 1; j <= n; j++) {
				if (dist[i][j] < INF) {
					// cout << i << "->" << j << ": " << dist[i][j] << endl;
					curr = curr + dist[i][j];
				}
			}
		}
		ans.push(curr);
	}
	
	while (!ans.empty()) {
		cout << ans.top() << " ";
		ans.pop();
	}
	cout << endl;
	return 0;
}
