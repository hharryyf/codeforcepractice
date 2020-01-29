#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 262192
typedef long long ll;
using namespace std;

struct BIT {
	int n;
	ll sm[MAX_SIZE];
	int cnt[MAX_SIZE];   
	
	void setsize(int n) {
	    this->n = n;
	}
	
	int shift(int x) {
	    return x & (-x);
	}
	
	void update(int index, ll ds, int dc) {
	    while (index <= n) {
		 	cnt[index] += dc;
		 	sm[index] += ds;
		    index += shift(index);	   	   
		}
	}
	
	pair<int, ll> query(int index) {
	    int r1 = 0;
	    ll r2 = 0;
	    while (index > 0) {
	        r1 += cnt[index], r2 += sm[index];
	        index -= shift(index);
	    }
	    return make_pair(r1, r2);
	}
};

BIT tree;
vector<ll> disc;
int n, q;
ll op[MAX_SIZE << 1][3];
ll h[MAX_SIZE << 1];
ll tmp[MAX_SIZE];

int getindex(double v) {
    return lower_bound(disc.begin(), disc.end(), v) - disc.begin(); 
}

bool valid(double v, ll tol) {
    auto p = tree.query(getindex(v));
    return (1.0 * v * p.first) >= (1.0 * tol + 1.0 * p.second);
}

int main() {
	scanf("%d%d", &n, &q);
	int i, j = 0;
	for (i = 1; i <= n; i++) {
	    scanf("%lld", &h[i]);
	    tmp[j++] = h[i];
	}
	
	for (i = 1; i <= q; i++) {
	    scanf("%lld", &op[i][0]);
	    if (op[i][0] == 1) {
	        scanf("%lld%lld", &op[i][1], &op[i][2]);
	        tmp[j++] = op[i][2];
	    } else {
	        scanf("%lld", &op[i][1]);
	    }
	}
	
	sort(tmp, tmp + j);
	for (i = 0 ; i < j; i++) {
	    if (i == 0 || tmp[i] != tmp[i-1]) {
	        disc.push_back(tmp[i]);
	    }
	}
	int m = disc.size();
	tree.setsize(m);
	
	for (i = 1; i <= n; i++) {
	    tree.update(getindex(h[i]) + 1, h[i], 1);
	}
	
	for (i = 1; i <= q; i++) {
	    if (op[i][0] == 1) {
	        tree.update(getindex(h[op[i][1]]) + 1, -h[op[i][1]], -1);
	        h[op[i][1]] = op[i][2];
	        tree.update(getindex(h[op[i][1]]) + 1, h[op[i][1]], 1);
	    } else {
	        // we want to query op[i][2]
	        double low = 0.0, high = 1e16;
	        double ans = 1e16;
	        for (j = 1; j <= 80; j++) {
	            double mid = low + (high - low) / 2.0;
	            if (valid(mid, op[i][1])) {
	                high = mid;
	                ans = mid;
	            } else {
	                low = mid;
	            }
	        }
	        printf("%.5lf\n", ans);
	    }
	}
	
	return 0;
}
 
