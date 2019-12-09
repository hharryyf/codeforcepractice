#include <bits/stdc++.h>
#define MAX_SIZE 524292
using namespace std;

int n, q;
// oper[i][0]=0, insert
// oper[i][0]=1, query
// oper[i][1]=i, query
// oper[i][1]=w, oper[i][2]=h, insert
int oper[MAX_SIZE >> 1][3];

pair<int, int> box[MAX_SIZE >> 1];

unordered_map<int, unordered_map<int, int> > mp;


set<int> wt[MAX_SIZE >> 1];

int tree[MAX_SIZE];

vector<int> disc;

int tmp[MAX_SIZE >> 1];

char str[3];

// insert val into pt
void update(int pt, int l, int r, int index, int val, int tp) {
	if (l > r) return;
	if (pt == l && r == pt) {
		if (tp == 0) {
			wt[l].insert(val);
			tree[index] = max(tree[index], *wt[l].rbegin());
		} else {
			wt[l].erase(val);
			if (wt[l].size()) {
				tree[index] = *wt[l].rbegin();
			} else {
				tree[index] = 0;
			}
		}
		return;
	}
	
	int mid = l + (r - l) / 2;
	if (pt <= mid) update(pt, l, mid, index * 2, val, tp);
	else {
		update(pt, mid + 1, r, index * 2 + 1, val, tp);
	}
	
	tree[index] = max(tree[index * 2], tree[index * 2 + 1]);
}

// w/h, w at least val
pair<int, int> query(int start, int end, int l, int r, int index, int val) {
	if (start > end || l > r || start > r || l > end) return make_pair(0, 0);
	if (tree[index] < val) return make_pair(0, 0);
	int mid = l + (r - l) / 2;
	if (start <= l && r <= end) {
		if (l == r) {
			return make_pair(*wt[l].lower_bound(val), disc[l]);
		}
		if (tree[index * 2] >= val) {
			return query(start, end, l, mid, index * 2, val);
		}
		return query(start, end, mid + 1, r, index * 2 + 1, val);
	}
	
	pair<int, int> p1 = query(start, end, l, mid, index * 2, val);
	pair<int, int> p2 = query(start, end, mid + 1, r, index * 2 + 1, val);
	if (p1.second) {
		return p1;
	}
	
	if (p2.second) {
		return p2;
	}
	
	return make_pair(0, 0);
}

void add(int w, int h) {
	int index = lower_bound(disc.begin(), disc.end(), h) - disc.begin();
	int m = (int) disc.size();
	update(index, 0, m - 1, 1, w, 0);
}



void remove(int w, int h) {
	int index = lower_bound(disc.begin(), disc.end(), h) - disc.begin();
	int m = (int) disc.size();
	update(index, 0, m - 1, 1, w, 1);
}

int getindex(int idx) {
	remove(box[idx].first, box[idx].second);
	int index = lower_bound(disc.begin(), disc.end(), box[idx].second) - disc.begin();
	int m = (int) disc.size();
	pair<int, int> p = query(index, m - 1, 0, m - 1, 1, box[idx].first);
	add(box[idx].first, box[idx].second);
	if (p.first == 0 || p.second == 0) return 0;
	return mp[p.first][p.second];
}

int main() {
	scanf("%d", &q);
	int i;
	for (i = 1; i <= q; i++) {
		scanf("%s", str);
		int v, w, h;
		if (str[0] == 'D') {
			scanf("%d%d", &w, &h);
			oper[i][0] = 0, oper[i][1] = w, oper[i][2] = h;
			tmp[++n] = h;
			box[n] = make_pair(w, h);
			mp[w][h] = n;
		} else {
			scanf("%d", &v);
			oper[i][0] = 1;
			oper[i][1] = v;
		}
	}
	
	sort(tmp + 1, tmp + 1 + n);
	for (i = 1; i <= n; i++) {
		if (i == 1 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
	}
	
	for (i = 1; i <= q; i++) {
		if (oper[i][0] == 0) {
			add(oper[i][1], oper[i][2]);
		} else {
			int ret = getindex(oper[i][1]);
			if (ret) {
				printf("%d\n", ret);
			} else {
				printf("RIP\n");
			}
		}
	}
	return 0;
}
