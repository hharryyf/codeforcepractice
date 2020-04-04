#include <bits/stdc++.h>
#define MAX_SIZE 1000111
#define LEFT (index << 1)
#define RIGHT (index << 1 | 1)
typedef long long ll;
using namespace std;

int n;
vector<int> tree[MAX_SIZE];
vector<ll> prefix[MAX_SIZE];
int dis[MAX_SIZE];
void build(int index) {
	if (index > n) return;
	tree[index].push_back(0);
	prefix[index].push_back(0);
	if (LEFT > n && RIGHT > n) return;
	build(LEFT);
	build(RIGHT);
	int i = 0, j = 0, sz1 = tree[LEFT].size(), sz2 = tree[RIGHT].size();
	int d1 = dis[LEFT - 1], d2 = dis[RIGHT - 1];
	while (i < sz1 && j < sz2) {
		if (d1 + tree[LEFT][i] <= d2 + tree[RIGHT][j]) {
			tree[index].push_back(d1 + tree[LEFT][i]);
			prefix[index].push_back(prefix[index].back() + d1 + tree[LEFT][i]);
			++i;
		} else {
			tree[index].push_back(d2 + tree[RIGHT][j]);
			prefix[index].push_back(prefix[index].back() + d2 + tree[RIGHT][j]);
			++j;
		}
	}
	
	while (i < sz1) {
		tree[index].push_back(d1 + tree[LEFT][i]);
		prefix[index].push_back(prefix[index].back() + d1 + tree[LEFT][i]);
		++i;
	}
	
	while (j < sz2) {
		tree[index].push_back(d2 + tree[RIGHT][j]);
		prefix[index].push_back(prefix[index].back() + d2 + tree[RIGHT][j]);
		++j;
	}
}

pair<int, ll> total(int index, int h) {
	if (index == 0) return make_pair(0, 0);
	int idx = upper_bound(tree[index].begin(),  tree[index].end(), h) - tree[index].begin() - 1;
	if (idx == -1) {
		return make_pair(idx + 1, 0);
	}
	return make_pair(idx + 1, prefix[index][idx]);
}

int parent(int v) {
	return v >> 1;
}

int sibling(int v) {
	return v ^ 1;
}

// query the total sum of all dist sum with dist to v less than h
// and the number of such vertices
ll query(int h, int v) {
	pair<int, ll> ret = total(v, h);
	int limit = h;
	int d = 0;
	while (v != 0) {
		auto p = total(sibling(v), limit - dis[v - 1] - dis[sibling(v) - 1]);
		ret.first += p.first;
		ret.second += p.second + 1ll * p.first * (d + dis[v - 1] + dis[sibling(v) - 1]);
		if (v != 1 && dis[v-1] <= limit) {
			ret.first++;
			ret.second += d + dis[v-1];
		}
		limit = limit - dis[v - 1];
		d += dis[v-1];
		v = parent(v);
	}
	
	return 1ll * h * ret.first - ret.second;
}

int main() {
	int q;
	scanf("%d%d", &n, &q);
	int i;
	for (i = 1; i <= n-1; ++i) scanf("%d", &dis[i]);
	build(1);
	/*
	for (i = 1; i <= n; ++i) {
		cout << i << ": ";
		for (auto v : tree[i]) {
			printf("%d ", v);
		}
		printf("\n");
	}*/
	while (q > 0) {
		int v, h;
		scanf("%d%d", &v, &h);
		printf("%I64d\n", query(h, v));
		q--;
	}
	return 0;
}