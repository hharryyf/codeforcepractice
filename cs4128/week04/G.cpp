#include <bits/stdc++.h>
#define MAX_SIZE 524312
#define ADD 0
#define REMOVE 1
#define FIND 2

using namespace std;

struct opt {
	int op, x, y;
};

set<int> pt[MAX_SIZE >> 1];
// stores the maximum y coordiate in the range
int tree[MAX_SIZE];
opt arr[MAX_SIZE >> 1];
vector<int> disc;
vector<int> tmp;
int q;
int n;
char s[10];

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index] = -1;
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	tree[index] = -1;
}

void update(int p, int l, int r, int index, int val, int tp) {
	if (l > r) return;
	if (l == r && p == l) {
		if (tp == ADD) {
			// cout << val << " " << tree[index] << endl;
			tree[index] = max(val, tree[index]);
			
		} else {
			// cout << "remove " << val << endl;
			pt[p].erase(val);
			if (pt[p].empty()) {
				tree[index] = -1;
			} else {
				tree[index] = *pt[p].rbegin();
			}
		}
		return;
	}
	
	int mid = l + (r - l) / 2;
	if (p <= mid) {
		update(p, l, mid, index * 2, val, tp);
	} else {
		update(p, mid + 1, r, index * 2 + 1, val, tp);
	}
	
	tree[index] = max(tree[index * 2], tree[index * 2 + 1]);
}

int query(int start, int end, int l, int r, int index, int val) {
	if (start > end || l > r || start > r || l > end) return MAX_SIZE;
	int mid = l + (r - l) / 2;
	if (start <= l && r <= end) {
		if (tree[index] <= val) return MAX_SIZE;
		if (l == r) return l;
		if (tree[index * 2] > val) {
			return query(start, end, l, mid, index * 2, val);
		}
		return query(start, end, mid + 1, r, index * 2 + 1, val);
	}
	
	return min(query(start, end, l, mid, index * 2, val), query(start, end, mid + 1, r, index * 2 + 1, val));
}

int main() {
	scanf("%d", &q);
	int i;
	for (i = 0 ; i < q; i++) {
		int x, y;
		scanf("%s%d%d", s, &x, &y);
		if (s[0] == 'r') {
			arr[i].op = REMOVE;
		} else if (s[0] == 'f') {
			arr[i].op = FIND;
		} else {
			arr[i].op = ADD;
		}
		
		arr[i].x = x;
		arr[i].y = y;
		tmp.push_back(arr[i].x);		
	}
	
	sort(tmp.begin(), tmp.end());
	for (i = 0 ; i < (int) tmp.size(); i++) {
		if (i == 0 || tmp[i] != tmp[i-1]) {
			disc.push_back(tmp[i]);
		}
	} 
	n = (int) disc.size();
	build(0, n - 1, 1);
	for (i = 0 ; i < q; i++) {
		int index;
		if (arr[i].op == ADD) {
			index = lower_bound(disc.begin(), disc.end(), arr[i].x) - disc.begin();
			// cout << arr[i].y << "*****" << (pt[index].empty() ? -1 : *pt[index].rbegin()) << endl;
			if (pt[index].empty() || (*pt[index].rbegin() < arr[i].y)) {
				update(index, 0, n - 1, 1, arr[i].y, ADD);
			}
			pt[index].insert(arr[i].y);
		} else if (arr[i].op == REMOVE) {
			index = lower_bound(disc.begin(), disc.end(), arr[i].x) - disc.begin();
			update(index, 0, n - 1, 1, arr[i].y, REMOVE);
			// cout << pt[index].size() << endl;
		} else {
			vector<int> :: iterator iter = upper_bound(disc.begin(), disc.end(), arr[i].x);
			if (iter == disc.end()) {
				printf("-1\n");
			} else {
				index = iter - disc.begin();
				int idk = query(index, n - 1, 0, n - 1, 1, arr[i].y);
				if (idk >= n) {
					printf("-1\n");
				} else {
					printf("%d %d\n", disc[idk], *pt[idk].upper_bound(arr[i].y));
				}
			}
		}
	}
	return 0;
}
