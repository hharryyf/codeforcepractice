#include <bits/stdc++.h>
#define MAX_SIZE 1048592
using namespace std;
typedef long long ll;
struct poke {
	ll r;	
	int s;
};

// the compressed points of each size of the pokemon
vector<int> disc;
// stores the capacity of the currently active pokemon of size si
multiset<ll> cp[MAX_SIZE];
// tree that stores the maximum, support searching for the index of the
// greatest element of that range, right-hand side first
ll tree[MAX_SIZE];

// tp = 0 means add, tp = 1 means remove
void update(int pt, int l, int r, int index, ll val, int tp) {
	if (pt < l || pt > r || l > r) return;
	if (l == r && r == pt) {
		if (tp == 0) {
			cp[disc[pt]].insert(val);
			tree[index] = max(tree[index], val);
		} else {
			cp[disc[pt]].erase(cp[disc[pt]].find(val));
			if (cp[disc[pt]].size()) {
				tree[index] = *cp[disc[pt]].rbegin();
			} else {
				tree[index] = 0;
			}
			//cout << "remove " << val << " tree is " << tree[index] << endl;
		}
		return;
	}	
	
	int mid = l + (r - l) / 2;
	if (pt <= mid) {
		update(pt, l, mid, index * 2, val, tp);
	} else {
		update(pt, mid + 1, r, index * 2 + 1, val, tp);
	}
	
	tree[index] = max(tree[index * 2], tree[index * 2 + 1]);
}
// the (maximum r, index)
pair<ll, int> query(int start, int end, int l, int r, int index) {
	if (start > end || l > r || start > r || l > end) {
		return make_pair(0, -1);
	}
	if (tree[index] <= 0) return make_pair(0, -1);
	
	int mid = l + (r - l) / 2;
	if (start <= l && r <= end) {
		if (l == r) {
			//cout << tree[index] << " " << l << endl; 
			return make_pair(tree[index], l);
		}
		if (tree[index * 2] > tree[index * 2 + 1]) {
			return query(start, end, l, mid, index * 2);
		}
		return query(start, end, mid + 1, r, index * 2 + 1);
	}
	
	return max(query(start, end, l, mid, index * 2), query(start, end, mid + 1, r, index * 2 + 1));
} 

poke pks[MAX_SIZE];

ll ball[MAX_SIZE];

static bool cmp(const poke &a, const poke &b) {
	return a.s < b.s;
}
// return the maximum index in disc such that it is no creater than val
int getindex(ll val) {
	int ret = -1;
	int l = 0, r = (int) disc.size() - 1;
	while (l <= r) {
		int mid = l + (r - l) / 2;
		if (disc[mid] <= val) {
			ret = max(mid, ret);
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	
	return ret;
}

int main() {
	int n, b, i;
	scanf("%d%d", &n, &b);
	for (i = 0; i < n; i++) {
		scanf("%d%lld", &pks[i].s, &pks[i].r);
		// cp[pks[i].s].insert(pks[i].r);
	}	
	ll ans = 0;
	for (i = 0 ; i < b; i++) {
		scanf("%lld", &ball[i]);
	}
	
	sort(ball, ball + b);
	sort(pks, pks + n, cmp);
	for (i = 0 ; i < n; i++) {
		if (i == 0 || pks[i].s != pks[i-1].s) {
			disc.push_back(pks[i].s);
		}
	}
	
	int m = (int) disc.size();
	for (i = 0 ; i < n; i++) {
		update(getindex(pks[i].s), 0, m - 1, 1, pks[i].r,0);
		//cout << "insert " << pks[i].r << " at " << getindex(pks[i].s) << endl;
	}
	
	for (i = 0; i < b; i++) {
		pair<ll, int> p = query(0, getindex(ball[i]), 0, m - 1, 1);
		//cout << "query " << getindex(ball[i]) << endl;
		ans += p.first;
		if (p.second != -1) {
			//cout << "remove " << p.first << " at " << p.second << endl; 
			update(p.second, 0, m - 1, 1, p.first, 1);
		}
	}
	
	cout << ans << endl;
	return 0;
}
