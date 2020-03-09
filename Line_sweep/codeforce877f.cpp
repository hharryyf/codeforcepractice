#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 100011
typedef long long ll;
using namespace std;

unordered_map<ll, int> cnt;
ll prefix[MAX_SIZE];
int t[MAX_SIZE];
int block_size;

struct qrs {
    int l, r, id;
    bool operator < (qrs other) const {
        int b1 = l / block_size, b2 = other.l / block_size;
        return (b1 ^ b2) ? b1 < b2 : ((b1 & 1) ? r < other.r : r > other.r);
    }
};

qrs q[MAX_SIZE];
ll ret[MAX_SIZE];

int main() {
	int n, i;
	ll k;
	scanf("%d%lld", &n, &k);
	block_size = sqrt(n);
	for (i = 1; i <= n; ++i) scanf("%d", &t[i]);
	for (i = 1; i <= n; ++i) {
		ll v;
		scanf("%lld", &v);
		prefix[i] = (t[i] == 1 ? v : -v) + prefix[i-1];
	}
	
	int m;
	scanf("%d", &m);
	for (i = 1; i <= m; ++i) {
		scanf("%d%d", &q[i].l, &q[i].r);
		q[i].id = i;
	}
	
	sort(q + 1, q + 1 + m);
	 
	ll ans = 0; 
    int l = 1, r = 0;
    cnt[0] = 1;
    for (i = 1; i <= m; ++i) {
		while (r < q[i].r) {
			  ans += cnt[prefix[++r] - k];
			  cnt[prefix[r]]++;
		}
		
		while (r > q[i].r) {
			  cnt[prefix[r]]--;
			  ans -= cnt[prefix[r--] - k];
		}
		
		while (l < q[i].l) {
			   cnt[prefix[l-1]]--;
			   ans -= cnt[prefix[l-1] + k];
			   l++;
		}
		
		while (l > q[i].l) {
              ans += cnt[prefix[l-2] + k];
			  cnt[prefix[l-2]]++;
			  --l;
		}
		
		ret[q[i].id] = ans;
	}
	
	for (i = 1; i <= m; ++i) printf("%lld\n", ret[i]);
	
	return 0;
}
