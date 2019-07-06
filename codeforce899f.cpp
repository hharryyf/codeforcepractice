#include <bits/stdc++.h>
#define MAX_LEN 524330
using namespace std;
unordered_map<char, set<int> > mymap;

int tree[MAX_LEN];
char str[MAX_LEN >> 1];
int n, m;

void build(int l, int r, int index);
// query would return the minimum index such that the prefixsum
// of the 0 to index is equal to target
int query(int l, int r, int index, int target);
void eliminate(int pos, int l, int r, int index);

int main(int argc, char *argv[]) {
	mymap = unordered_map<char, set<int> >();
	scanf("%d%d", &n, &m);
	scanf("%s", str);
	int i;
	for (i = 0 ; i < (int) strlen(str); i++) {
		mymap[str[i]].insert(i);
	}
	
	build(0, n - 1, 1);
	unordered_map<char, set<int> > :: iterator it;
	for (i = 0 ; i < m; i++) {
		// cout << "round " << i << endl;
		int l, r;
		char ch;
		scanf("%d%d %c", &l, &r, &ch);
		
		int leftmost = query(0, n - 1, 1, l);
		int rightmost = query(0, n - 1, 1, r);
		set<int> :: iterator iter = mymap[ch].lower_bound(leftmost);
		// cout << "wipe out " << ch;
		// cout << "l = " << l << " r = " << r << " "<< leftmost << " " << rightmost << endl;
		vector<int> current = vector<int>();
		it = mymap.find(ch);
		if (it == mymap.end()) continue;
		while (iter != it->second.end()) {
			if (*iter > rightmost) break;
			if (*iter >= leftmost && *iter <= rightmost) {
				current.push_back(*iter);
				it->second.erase(iter++);
				
			} else {
				break;
			}
		}
		// cout << "error is after" << endl;
		for (auto v : current) {
			// cout << v << endl;
			eliminate(v, 0, n - 1, 1);
		}
		
	}
	
	vector<pair<int, char> > ans = vector<pair<int, char> >();
	it = mymap.begin();
	while (it != mymap.end()) {
		for (auto num : it->second) {
			ans.push_back(pair<int, char>(num, it->first));
		}
		it++;
	}
	
	sort(ans.begin(), ans.end());
	
	for (i = 0 ; i < (int) ans.size(); i++) {
		printf("%c", ans[i].second);
	}
	
	printf("\n");
	return 0;
}

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index] = 1;
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	tree[index] = tree[index * 2] + tree[index * 2 + 1];
}

void eliminate(int pos, int l, int r, int index) {
	if (l > r) return;
	if (pos == l && pos == r) {
		tree[index] = 0;
		return;
	}
	
	int mid = l + (r - l) / 2;
	if (pos <= mid) {
		eliminate(pos, l, mid, index * 2);
	} else {
		eliminate(pos, mid + 1, r, index * 2 + 1);
	}
	tree[index] = tree[index * 2] + tree[index * 2 + 1];
}

// query would return the minimum index such that the prefixsum
// of the 0 to index is equal to target
int query(int l, int r, int index, int target) {
	if (l > r || tree[index] < target || target == 0) {
		return -1;
	}
	
	if (l == r) {
		if (tree[index] == target) {
			return l;
		}
		return -1;
	}
	
	int mid = l + (r - l) / 2;
	if (tree[index * 2] >= target) {
		return query(l, mid, index * 2, target);
	}
	
	return query(mid + 1, r, index * 2 + 1, target - tree[index * 2]);
}
