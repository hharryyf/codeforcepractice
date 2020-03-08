#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 262192
using namespace std;
typedef long long ll;
struct line {
    ll m, b;
    int id;
};

ll floordiv (ll a, ll b) {
    return a / b - (a%b && ((a <0) ^ (b <0) )) ;
}
	
ll intersect ( line a, line b) {
    return floordiv (b.b - a.b, a.m - b.m);
}

pair<int, int> org[MAX_SIZE >> 1];
pair<pair<int, int>, int> ist[MAX_SIZE >> 1];

struct Convex {
	vector<line> cht;
	
	void insert(line l) {
		auto n = cht.size();
		while ((n >= 1 &&  l.m == cht[n-1].m && l.b >= cht[n-1].b) 
		|| (n >= 2 && intersect(cht[n-1], cht[n-2]) >= intersect(cht[n-1], l))) {
			cht.pop_back();
			n = cht.size();
		}
		cht.push_back(l);
	}
	
	ll query(ll x) {
		int low = 0, high = (int) cht.size() - 2;
		int ret = (int) cht.size() - 1;
		while (low <= high) {
			int mid = low + (high - low) / 2;
			if (intersect(cht[mid], cht[mid + 1]) >= x) {
				ret = mid;
				high = mid - 1;
			} else {
				low = mid + 1;
			}
		}
		
		return cht[ret].id;
	}
};

Convex tree[MAX_SIZE];

void insert(int pos, int l, int r, int index, line li) {
	 if (l > r || pos < l || pos > r) return;
	 tree[index].insert(li);
	 if (l == r) return;
	 int mid = (l + r) >> 1;
	 if (pos <= mid) {
	 	insert(pos, l, mid, index << 1, li);
	 } else {
	    insert(pos, mid + 1, r, index << 1 | 1, li);
	 }
}

int query(int start, int end, int l, int r, int index, ll t) {
	 if (start > end || l > r || start > r || l > end) return 0;
	 if (start <= l && r <= end) return tree[index].query(t);
	 int mid = (l + r) >> 1;
	 if (end <= mid) return query(start, end, l, mid, index * 2, t);
	 if (mid + 1 <= start) return query(start, end, mid + 1, r, index * 2 + 1, t);
	 int id1 = query(start, end, l, mid, index * 2, t);
	 int id2 = query(start, end, mid + 1, r, index * 2 + 1, t);
	 ll y1 = 1ll * org[id1].first * t + org[id1].second;
	 ll y2 = 1ll * org[id2].first * t + org[id2].second;
	 if (y1 > y2) return id1;
	 return id2;
}

int main() {
	int n, m, i;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n; i++) {
		scanf("%d%d", &org[i].second, &org[i].first);
		ist[i].first = org[i], ist[i].second = i;
    }
    sort(ist + 1, ist + n + 1);
    for (i = 1; i <= n; i++) {
		insert(ist[i].second, 1, n, 1, line{ist[i].first.first, ist[i].first.second, ist[i].second});
	}
	
	while (m > 0) {
		  int l, r, t;
		  scanf("%d%d%d", &l, &r, &t);
		  printf("%d\n", query(l, r, 1, n, 1, t));
		  m--;
	}
	return 0;
}

