#include <bits/stdc++.h>
#define MAX_SIZE 200011

using namespace std;

// queries (time, city, query id) 
vector<pair<pair<int, int>, int > > qrs;

vector<pair<int, pair<int, int> > > builds;

int f[MAX_SIZE], subsz[MAX_SIZE];

int n, m;

int find(int x) {
	if (f[x] == x) return x;
	return f[x] = find(f[x]);
}


void unionset(int a, int b) {
	int x = find(a), y = find(b);
	if (x != y) {
		if (subsz[x] < subsz[y]) {
			f[x] = y;
			subsz[y] += subsz[x];
		} else {
			f[y] = x;
			subsz[x] += subsz[y];
		}
	}
}


void preprocess() {
	for (int i = 1; i <= n; i++) {
		f[i] = i;
		subsz[i] = 1;
	}
}

int ans[MAX_SIZE];

int main() {
	scanf("%d%d", &n, &m);
	preprocess();
	int i, j;
	for (i = 0 ; i < m; i++) {
		int v1, v2, ti;
		scanf("%d%d%d", &v1, &v2, &ti);
		builds.push_back(make_pair(ti, make_pair(v1, v2)));
	}	
	
	int q;
	scanf("%d", &q);
	for (i = 0 ; i < q; i++) {
		int ci, ti;
		scanf("%d%d", &ti, &ci);
		qrs.push_back(make_pair(make_pair(ti, ci), i));
	}
	
	sort(builds.begin(), builds.end());
	sort(qrs.begin(), qrs.end());
	
	for (i = 0, j = 0; i < m && j < q; j++) {
		while (i <= m && builds[i].first <= qrs[j].first.first) {
			unionset(builds[i].second.first, builds[i].second.second);
			i++;
		}
		
		ans[qrs[j].second] = subsz[find(qrs[j].first.second)];
	}
	
	for (i = 0 ; i < q; i++) {
		printf("%d\n", ans[i]);
	}
	
	return 0;
}
