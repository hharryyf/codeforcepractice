#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;
typedef long long ll;
const ll inf = 1e18;
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
		}
		cht.push_back(l);
	}
	
	ll query(ll x) {
		int low = 0, high = (int) cht.size() - 2;
		int ret = (int) cht.size() - 1;
        if (ret < 0) return inf;
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

ll ans[MAX_SIZE];
Convex cht[MAX_SIZE];
vector<int> add[MAX_SIZE << 3], qrs[MAX_SIZE << 3];
pair<int, int> edg[MAX_SIZE];
int N, M;

int main() {
    int i;
    scanf("%d%d", &N, &M);
    for (i = 1; i <= M; ++i) {
        int a, b, s, e;
        scanf("%d%d%d%d", &a, &b, &s, &e);
        qrs[s].emplace_back(i);
        add[e].emplace_back(i);
        edg[i].first = a, edg[i].second = b;
    }

    cht[1].insert(line{0, 0});
    for (i = 0; i <= 1000000; ++i) {
        for (auto id : qrs[i]) {
            ans[id] = cht[edg[id].first].query(i) + 1ll * i * i;
        }

        for (auto id : add[i]) {
            cht[edg[id].second].insert(line{1ll * -2 * i, ans[id] + 1ll * i * i});
        }
    }

    ll ret = inf;
    for (i = 1; i <= M; ++i) {
        if (edg[i].second == N) {
            ret = min(ret, ans[i]);
        }
    }

    if (ret < 1e18) {
        cout << ret << endl;
    } else {
        cout << (-1) << endl;
    }
    return 0;
}