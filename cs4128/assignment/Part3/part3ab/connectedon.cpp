#include <bits/stdc++.h>
#define MAX_SIZE 600011

using namespace std;

int n, m;

// t->f
vector<pair<int, int> > f[MAX_SIZE];
// t->subsz
vector<pair<int, int> > subsz[MAX_SIZE];

vector<pair<int, pair<int, int> > > builds;

void preprocess() {
	int i;
	for (i = 1; i <= n; i++) {
		f[i].emplace_back(0, i);
		subsz[i].emplace_back(0, 1);
	}		
}

int parent(int x, int ti) {
	int low = 0, high = (int) f[x].size() - 1;
	int index = 0;
	while (low <= high) {
		int mid = low + (high - low) / 2;
		if (f[x][mid].first <= ti) {
			index = max(index, mid);
			low = mid + 1;
		} else {
			high = mid - 1;
		}
	}	
	
	return f[x][index].second;
}

int size(int x, int ti) {
	int low = 0, high = (int) subsz[x].size() - 1;
	int index = 0;
	while (low <= high) {
		int mid = low + (high - low) / 2;
		if (subsz[x][mid].first <= ti) {
			index = max(index, mid);
			low = mid + 1;
		} else {
			high = mid - 1;
		}
	}	
	
	return subsz[x][index].second;
}

int find(int x, int ti) {
	int p = parent(x, ti);
	if (p == x) {
		return x;
	}
	
	return find(p, ti);
}

void unionset(int v1, int v2, int ti) {
	int x = find(v1, ti), y = find(v2, ti);
	if (x != y) {
		int szx = size(x, ti);
		int szy = size(y, ti);
		if (szx < szy) {
			f[x].emplace_back(ti, y);
			subsz[y].emplace_back(ti, szx + szy);	
		} else {
			f[y].emplace_back(ti, x);
			subsz[x].emplace_back(ti, szx + szy);
		}
	}
}

int getsize(int v, int ti) {
	int x = find(v, ti);
	return size(x, ti);
}

int main() {
	scanf("%d%d", &n, &m);
	int q;
	scanf("%d", &q);
	int i;
	for (i = 0 ; i < m; i++) {
		int v1, v2, ti;
		scanf("%d%d%d", &v1, &v2, &ti);
		builds.push_back(make_pair(ti, make_pair(v1, v2)));
	}	
	
	sort(builds.begin(), builds.end());
	
	preprocess();
	
	for (auto p : builds) {
		int ti = p.first;
		int v1 = p.second.first, v2 = p.second.second;
		unionset(v1, v2, ti);
	}
	
	int lst = 0;
	while (q > 0) {
		int ti, ci;
		scanf("%d%d", &ci, &ti);
		ci = ci ^ lst;
		ti = ti ^ lst;
		lst = getsize(ci, ti);
		printf("%d\n", lst);
		q--;
	}
	return 0;
}
