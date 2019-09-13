#include <bits/stdc++.h>
#define MAX_SIZE (1048576 + 11)
#define INF 10000007

using namespace std;

typedef struct qr {
	int l, r, id;
} Query;

int tree[MAX_SIZE];
// the pred same element of the element at index i, INF as default
int pred[MAX_SIZE >> 1];
// the nextv same element of the element at index i, INF as default
int nextv[MAX_SIZE >> 1];
// the original array
int arr[MAX_SIZE >> 1];

unordered_map<int, vector<int> > h;

vector<Query> qrs;

int ans[MAX_SIZE >> 1];

static bool cmp(const Query &a, const Query &b) {
	return a.l < b.l;
}

void build(int l, int r, int index);
int query(int start, int end, int l, int r, int index);
void update(int pt, int l, int r, int index, int val);

int main(int argc, char *argv[]) {
	int i, j, n, m;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
		h[arr[i]].push_back(i);
	}
	
	unordered_map<int, vector<int> > :: iterator iter = h.begin();
	while (iter != h.end()) {
		for (i = 0 ; i < (int) iter->second.size(); i++) {
			if (i == 0) {
				pred[iter->second[i]] = -INF;	
			} else {
				pred[iter->second[i]] = iter->second[i-1];
			}
			
			if (i == (int) iter->second.size() - 1) {
				nextv[iter->second[i]] = -INF;	
			} else {
				nextv[iter->second[i]] = iter->second[i+1];
			}
		}
		
		iter++;
	}
	
	build(1, n, 1);
	
	for (i = 0 ; i < m; i++) {
		int l, r;
		scanf("%d%d", &l, &r);
		qrs.push_back((Query){l, r, i + 1});
	}
	
	sort(qrs.begin(), qrs.end(), cmp);
	/*
	for (i = 1; i <= n; i++) {
		cout << pred[i] << " ";
	}
	cout << endl;
	for (i = 1; i <= n; i++) {
		cout << nextv[i] << " ";
	}
	cout << endl;*/
	j = 1;
	for (i = 0 ; i < m; i++) {
		while (j < qrs[i].l) {
			if (nextv[j] != -INF) {
				// cout << "update " << nextv[j] << endl;
				update(nextv[j], 1, n, 1, INF);
			}
			j++;
		}
		
		int ret = query(qrs[i].l, qrs[i].r, 1, n, 1);
		// cout << "query " << qrs[i].l << " " << qrs[i].r << " gives " << ret << endl;
		ans[qrs[i].id] = (ret < INF ? ret : -1);
	}
	
	for (i = 1; i <= m; i++) {
		printf("%d\n", ans[i]);
	}
	return 0;
}

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index] = l - pred[l];
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	tree[index] = min(tree[index * 2], tree[index * 2 + 1]);
}

int query(int start, int end, int l, int r, int index) {
	// cout << "l= " << l << " " << "r= " << r << endl;
	if (start > end || l > r || start > r || l > end) return INF;
	if (start <= l && r <= end) return tree[index];
	int mid = l + (r - l) / 2;
	return min(query(start, end, l, mid, index * 2), 
			   query(start, end, mid + 1, r, index * 2 + 1));
}

void update(int pt, int l, int r, int index, int val) {
	if (l > r) return;
	if (l == r && pt == l) {
		tree[index] = val;
		return;
	}
	
	int mid = l + (r - l) / 2;
	if (pt <= mid) {
		update(pt, l, mid, index * 2, val);
	} else {
		update(pt, mid + 1, r, index * 2 + 1, val);
	}
	
	tree[index] = min(tree[index * 2], tree[index * 2 + 1]);
}
