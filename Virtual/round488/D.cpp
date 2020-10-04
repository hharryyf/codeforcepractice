// @Tom solved this problem
#include <bits/stdc++.h>
#define ii pair<int, int>
#define iiii pair<ii, ii>
#define x first
#define y second
#define ID if (0)
using namespace std;

int n, m;

// what alice sent to bob
// what bob sent to alice
vector<ii> a_sent;
vector<ii> b_sent;

// what we know alice might have (due to a valid corresponding pair from bob)
// what we know bob might have (due to a valid corresponding pair from alice)
set<ii> a_possible;
set<ii> b_possible;

// what digits have duplicates
int vis[10];

bool certain(ii a, vector<ii> sent) {
	bool can_x = false;
	bool can_y = false;
	for (ii b : sent) {
		ID {
			printf("has: [%d, %d], try: [%d, %d]\n", a.x, a.y, b.x, b.y);
		}
	 	if (a.x == b.x && a.y == b.y) continue;
		if (a.x == b.y && a.y == b.x) continue;
		if (a.x != b.x && a.y != b.y && a.x != b.y && a.y != b.x) continue;
		if (a.x == b.x || a.x == b.y) can_x = true;
		if (a.y == b.x || a.y == b.y) can_y = true;
	}
	ID printf("can_x: %d, can_y: %d\n", can_x, can_y);
	return (can_x && !can_y) || (can_y && !can_x);
}

int main() {
	cin >> n >> m;
	while (n--) {
		ii pair;
		cin >> pair.x >> pair.y;
		if (pair.x < pair.y) swap(pair.x, pair.y);
		a_sent.push_back(pair);
	}

	while (m--) {
		ii pair;
		cin >> pair.x >> pair.y;
		if (pair.x < pair.y) swap(pair.x, pair.y);
		b_sent.push_back(pair);
	}

	for (ii a : a_sent) {
		for (ii b : b_sent) {
		 	if (a.x == b.x && a.y == b.y) continue;
			if (a.x == b.y && a.y == b.x) continue;
			if (a.x != b.x && a.y != b.y && a.x != b.y && a.y != b.x) continue;
			if (a.x == b.x) vis[a.x]++;
			if (a.y == b.y) vis[a.y]++;
			if (a.x == b.y) vis[a.x]++;
			if (a.y == b.x) vis[a.y]++;
			a_possible.insert(a);
			b_possible.insert(b);
		}
	}

	int cnt = 0;
	for (int i = 1; i <= 9; ++i) {
		cnt += vis[i] >= 1;
		ID printf("vis[%d] = %d\n" , i , vis[i]);
	}
	ID cout << cnt << endl;

	// check if can determine common number
	if (cnt == 1) {
		for (int i = 1; i <= 9; ++i) {
			if(vis[i] >= 1){
				cout << i << endl;
				return 0;
			}
		}
	}

	for (ii a : a_possible) {
		if (!certain(a, b_sent)) {
			cout << -1 << endl;
			return 0;
		}
	}

	for (ii b : b_possible) {
		if (!certain(b, a_sent)) {
			cout << -1 << endl;
			return 0;
		}
	}

	cout << 0 << endl;
}