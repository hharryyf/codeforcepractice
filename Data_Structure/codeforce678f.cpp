#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 1048597 
using namespace std;
#define LEFT (index << 1)
#define RIGHT (index << 1 | 1)
#define MID ((l+r)>>1)
typedef long long ll;

const ll inf = 2e18 + 17;
struct line {
    ll m, b;
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
        if (cht.empty()) return -inf;
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

void update(int start, int end, int l, int r, int index, line li) {
    if (start > end || l > r || start > r || l > end) return;
    if (start <= l && r <= end) {
        tree[index].insert(li);
        return;
    }

    if (end <= MID) {
        update(start, end, l, MID, LEFT, li);
    } else if (start >= MID + 1) {
        update(start, end, MID + 1, r, RIGHT, li);
    } else {
        update(start, end, l, MID, LEFT, li);
        update(start, end, MID + 1, r, RIGHT, li);
    }
}

ll query(int pt, int l, int r, int index, ll x) {
    if (pt < l || pt > r || l > r) return -inf;
    ll ret = tree[index].query(x);
    if (l == r) return ret;
    if (pt <= MID) {
        ret = max(ret, query(pt, l, MID, LEFT, x));
    } else {
        ret = max(ret, query(pt, MID + 1, r, RIGHT, x));
    }

    return ret;
}

struct event {
    int from, to, tp;
    int a, b;
};

event evt[MAX_SIZE >> 1];
vector<pair<pair<int, int>, pair<int, int>>> add;

int main() {
    int i, n;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &evt[i].tp);
        if (evt[i].tp == 1) {
            scanf("%d%d", &evt[i].a, &evt[i].b);
            evt[i].from = i;
        } else if (evt[i].tp == 2) {
            int x;
            scanf("%d", &x);
            evt[x].to = i;
        } else {
            scanf("%d", &evt[i].b);
        }
    }

    for (i = 1; i <= n; ++i) {
        if (evt[i].tp == 1 && evt[i].from != 0 && evt[i].to == 0) {
            evt[i].to = n;
        }
    }

    for (i = 1; i <= n; ++i) {
        if (evt[i].tp == 1) {
            add.push_back(make_pair(make_pair(evt[i].a, evt[i].b), make_pair(evt[i].from, evt[i].to)));
        }
    }
       
    sort(add.begin(), add.end());

    for (auto &e : add) {
        line li = line{e.first.first, e.first.second};
        update(e.second.first, e.second.second, 1, n, 1, li);
        // cout << "add line " << li.m << " " << li.b << " to " << e.second.first << " " << e.second.second << endl;
    }

    for (i = 1; i <= n; ++i) {
        if (evt[i].tp == 3) {
            ll ret = query(i, 1, n, 1, evt[i].b);
            if (ret <= -inf) {
                printf("EMPTY SET\n");
            } else {
                printf("%I64d\n", ret);
            }
        }
    }
    return 0;
}