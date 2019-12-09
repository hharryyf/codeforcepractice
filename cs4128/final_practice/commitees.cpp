#include <bits/stdc++.h>
#define MAX_SIZE 101111
using namespace std;

multiset<int> c[MAX_SIZE * 10];

int ans = 0;
// (c, v) that should be inserted
vector<pair<int, int> > st[MAX_SIZE];
// (c, v) that should be deleted
vector<pair<int, int> > ed[MAX_SIZE];

int getmax(int index) {
	if ((int) c[index].size() == 0) return 0;
	return *c[index].rbegin();
}

int main() {
	int n, q, i;
	cin >> n >> q;
	for (i = 1; i <= n; i++) {
		int start, end, vi, ci;
		scanf("%d%d%d%d", &start, &end, &vi, &ci);
		end--;
		st[start].emplace_back(ci, vi);
		ed[end].emplace_back(ci, vi);
	}
	
	for (i = 0; i <= q-1; i++) {
		for (auto p : st[i]) {
			int ci = p.first, vi = p.second;
			int mx = getmax(ci);
			if (mx < vi) {
				ans += vi - mx;	
			}
			
			c[ci].insert(vi);
		}
		
		cout << ans << endl;
	
		for (auto p : ed[i]) {
			int ci = p.first, vi = p.second;
			int mx_pre = getmax(ci);
			c[ci].erase(c[ci].find(vi));
			int mx_end = getmax(ci);
			ans -= mx_pre - mx_end;
		}
	}
	return 0;
}
