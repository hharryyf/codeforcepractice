#include <bits/stdc++.h>
#define MAX_SIZE 1611
typedef long long ll;

using namespace std;

vector<double> pt;
vector<double> disc;
vector<ll> dist = vector<ll>(MAX_SIZE, 4000000000ll);
pair<int, int> seg[MAX_SIZE];
vector<pair<int, ll> > g[MAX_SIZE];
int m;

/* the system has solution iff no negative cycle occurs */

bool SPFA() {
	dist = vector<ll>(MAX_SIZE, 4000000000ll);
	vector<bool> visited = vector<bool>(MAX_SIZE, false);
	vector<int> relax = vector<int>(MAX_SIZE, 0);
	queue<int> q;
	dist[0] = 0ll;
	visited[0] = true;
	relax[0] = 1;
	q.push(0);
	while (!q.empty()) {
		auto pr = q.front();
		q.pop();
		visited[pr] = false;
		if (relax[pr] >= m + 1) {
			return false;
		}
		
		for (auto nextp : g[pr]) {
			if (nextp.second + dist[pr] < dist[nextp.first]) {
				dist[nextp.first] = nextp.second + dist[pr];
				if (!visited[nextp.first]) {
					visited[nextp.first] = true;
					q.push(nextp.first);
					relax[nextp.first]++;
				}
			}
		}
	}	
	/*
	for (int i = 0; i <= m; i++) {
		cout << dist[i] << " ";
	}
	cout << endl;*/
	return true;
}

int main() {
	int n, i;
	cin >> n;
	for (i = 0 ; i < n; i++) {
		int v;
		cin >> seg[i].first >> seg[i].second >> v;
		pt.push_back((seg[i].first * 1.0) + 0.1);
		pt.push_back((seg[i].second * 1.0) - 0.1);
		
	}
	
	sort(pt.begin(), pt.end());
	
	for (i = 0 ; i < (int) pt.size(); i++) {
		if (i == 0 || pt[i] != pt[i-1]) {
			disc.push_back(pt[i]);
		}
	}
	
	
	m = (int) disc.size() * 2;
	
	for (i = 0; i < n; i++) {
		double v1 = seg[i].first * 1.0 + 0.1;
		double v2 = seg[i].second * 1.0 - 0.1;
		seg[i].first = ((lower_bound(disc.begin(), disc.end(), v1) - disc.begin()) + 1) * 2;
		seg[i].second = ((lower_bound(disc.begin(), disc.end(), v2) - disc.begin()) + 1) * 2;
	}
	
	int low = 1, high = n;
	int ans = n;
	while (low <= high) {
		int mid = low + (high - low) / 2;
		for (i = 0 ; i < MAX_SIZE; i++) {
			g[i].clear();
		}
		
		for (i = 0 ; i < n; i++) {
			g[seg[i].first - 1].push_back(make_pair(seg[i].second, -1));
			g[seg[i].second].push_back(make_pair(seg[i].first - 1, (ll) mid));
		}
		
		for (i = 1; i <= m; i++) {
			g[i-1].push_back(make_pair(i, 0));
		}
		
		if (SPFA()) {
			ans = min(ans, mid);
			high = mid - 1;
		} else {
			low = mid + 1;
		}
	}
	
	cout << ans << endl;
	return 0;
}
