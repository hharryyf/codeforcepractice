#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 262192
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
using namespace std;
typedef long long ll;
struct line {
    ll m, b;
};

ll floordiv (ll a, ll b) {
    return a / b - (a%b && ((a <0) ^ (b <0) )) ;
}
	
ll intersect ( line a, line b) {
    return floordiv (b.b - a.b, a.m - b.m);
}

struct Convex {
	vector<line> cht;
	
	void insert(line l) {
		auto n = cht.size();
        while ((n >= 1 &&  l.m == cht[n-1].m && l.b <= cht[n-1].b) 
		|| (n >= 2 && intersect(cht[n-1], cht[n-2]) >= intersect(cht[n-1], l))) {
			cht.pop_back();
			n = cht.size();
            // cout << "pop line " << endl;
		}
		cht.push_back(l);
        // cout << "insert line finish " << endl;
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
		
		return cht[ret].m * x + cht[ret].b;
	}
};

Convex tree[MAX_SIZE];

void insert(int pos, int l, int r, int index, line L) {
    if (pos < l || pos > r || l > r) return;
    // cout << "start insert " << endl;
    tree[index].insert(L);
    // cout << l << " " << r << " " << pos << endl;
    if (l == r) return;
    if (pos <= MID) {
        insert(pos, l, MID, LEFT, L);
    } else {
        insert(pos, MID + 1, r, RIGHT, L);
    }
}

ll query(int start, int end, int l, int r, int index, int x) {
    if (start > end || l > r || start > r || l > end) return 1e18;
    if (start <= l && r <= end) return tree[index].query(x);
    if (end <= MID) {
        return query(start, end, l, MID, LEFT, x);
    } else if (start >= MID + 1) {
        return query(start, end, MID + 1, r, RIGHT, x);
    }

    return min(query(start, end, l, MID, LEFT, x), query(start, end, MID + 1, r, RIGHT, x));
}

pair<pair<int, int>, int> a[MAX_SIZE];
int pre[MAX_SIZE];
int n, m;



int main() {
    int i;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &a[i].first.first);
        a[i].second = i;
        pre[i] = pre[i-1] + a[i].first.first;
        a[i].first.second = i * a[i].first.first - pre[i];
    }

    sort(a + 1, a + n + 1, greater<pair<pair<int, int>, int>>());

    for (i = 1; i <= n; ++i) {
        // cout << "insert " << a[i].first << " " << a[i].second * a[i].first - pre[a[i].second] << " pos " << a[i].second <<endl;
        insert(a[i].second, 1, n, 1, line{a[i].first.first, a[i].first.second});
    }
    scanf("%d", &m);
    while (m > 0) {
        int x, y;
        scanf("%d%d", &x, &y);
        printf("%I64d\n", query(y - x + 1, y, 1, n, 1, x - y) + pre[y]);
        --m;
    }

    return 0;
}