#include <bits/stdc++.h>
#define MAX_SIZE 524292
typedef long long ll;

using namespace std;

ll gs[MAX_SIZE];
int f[MAX_SIZE]; 

vector<ll> people[MAX_SIZE];

map<ll, int> cnt;

pair<pair<int, int>, int> edges[MAX_SIZE];

// ops[i][0] refers to operation order
// ops[i][1] refers to population 
ll ops[MAX_SIZE][3];

ll ans[MAX_SIZE];

char str[4];



int find(int x) {
	if (f[x] == x) return x;
	return f[x] = find(f[x]);
}

void grow(int x, ll dt) {
	int a = find(x);
	cnt[gs[a]]--;
	if (cnt[gs[a]] == 0) cnt.erase(gs[a]);
	gs[a] += dt;
	cnt[gs[a]]++;
} 

void unionset(int a, int b) {
	int x = find(a), y = find(b);
	f[x] = y;
	// 
	cnt[gs[x]]--;
	if (cnt[gs[x]] == 0) cnt.erase(gs[x]);
	cnt[gs[y]]--;
	if (cnt[gs[y]] == 0) cnt.erase(gs[y]);
	gs[y] = gs[x] + gs[y];
	cnt[gs[y]]++;
}

ll query() {
	return cnt.rbegin()->first;
}

int main() {
	int n, m, q, i;
	cin >> n >> m >> q;
	for (i = 1; i <= n; i++) {
		f[i] = i;
	}
	
	for (i = 1; i <= n; i++) {
		ll v;
		cin >> v;
		people[i].push_back(v);
		cnt[v]++;
	}
	
	for (i = 1; i <= m; i++) {
		int v1, v2;
		cin >> v1 >> v2;
		edges[i] = make_pair(make_pair(v1, v2), 1);
	}
	
	for (i = 1; i <= q; i++) {
		ll v1, v2;
		cin >> str >> v1;
		if (str[0] == 'P') {
			ops[i][0] = 2;
			ops[i][1] = v1;
			cin >> v2;
			ops[i][2] = v2;
			people[v1].push_back(v2);
		} else {
			ops[i][0] = 1;
			ops[i][1] = v1;
			edges[v1].second = 0;
		}
	}
	
	for (i = 1; i <= n; i++) {
		// cout << i << " " << people[i].last() << endl;
		cnt[people[i][(int) people[i].size() - 1]]++;
		gs[i] = people[i][(int) people[i].size() - 1];
	}
		
	for (i = 1; i <= m; i++) {
		if (edges[i].second == 1) {
			if (find(edges[i].first.first) != find(edges[i].first.second)) {
				unionset(edges[i].first.first, edges[i].first.second);
			}
		}
	}
	
	for (i = q; i >= 1; i--) {
		ans[i] = query();
		if (ops[i][0] == 1) {
			if (find(edges[ops[i][1]].first.first) != find(edges[ops[i][1]].first.second)) {
				unionset(edges[ops[i][1]].first.first, edges[ops[i][1]].first.second);
			}
		} else {
			ll pt = people[ops[i][1]][(int) people[ops[i][1]].size() - 1];
			people[ops[i][1]].pop_back();
			ll pt2 = people[ops[i][1]][(int) people[ops[i][1]].size() - 1];
			grow(ops[i][1], pt2 - pt);
		}
	}
	
	for (i = 1; i <= q; i++) {
		cout << ans[i] << endl;
	}
	return 0;
}
