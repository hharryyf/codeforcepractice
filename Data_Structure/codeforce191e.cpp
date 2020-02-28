#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 131092
#define REP(i, a, b) for(i=a; i<=b; ++i)
typedef long long ll;
using namespace std;

struct BIT {
	   ll tree[MAX_SIZE];
	   int n;
	   
	   void clear() {
	   		memset(tree, 0ll, sizeof(tree));
	   }
	   
	   void setsize(int n) {
	   		this->n = n;
	   }
	   
	   int shift(int x) {
	   	   return x & (-x);
	   }
	   
	   void update(int index, int val) {
	   		if (index <= 0) return;
	   		while (index <= n) {
                tree[index] += 1ll * val;
			    index += shift(index);   
	        }
	   }
	   
	   ll query(int index) {
	   	    ll ret = 0;
	   	    while (index > 0) {
		        ret += tree[index];
		        index -= shift(index);   
	        }
	        
	        return ret;
	   }
};

BIT t;
ll prefix[MAX_SIZE];
int n;
ll k;
vector<ll> disc;
ll tmp[MAX_SIZE];

int valid(ll mid) {
	t.clear();
	int idx = lower_bound(disc.begin(), disc.end(), 0ll) - disc.begin() + 1;
	t.update(idx, 1);
	int i;
	ll cnt = 0;
	for (i = 1; i <= n; ++i) {
		   int idx = lower_bound(disc.begin(), disc.end(), prefix[i] - mid) - disc.begin();
		   cnt += t.query(idx);
		   idx = lower_bound(disc.begin(), disc.end(), prefix[i]) - disc.begin() + 1;
		   t.update(idx, 1);	   
	}
	
	return cnt < k;
}

int main() {
	int i;
	ios::sync_with_stdio(false);
    cin.tie(NULL);
	cin >> n >> k;
	for (i = 1; i <= n; ++i) {
		cin >> prefix[i];
		prefix[i] += prefix[i-1];
		tmp[i] = prefix[i];
	}
	tmp[n+1] = 0;
	sort(tmp+1, tmp+2+n);
	
	for (i = 1; i <= n + 1; i++) {
        if (i == 1 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
	}
	
	t.setsize((int) disc.size());
	
	ll low = -100000000000000, high = 100000000000000;
	ll ans = high;
	while (low <= high) {
		  ll mid = (low + high) >> 1ll;
		  if (valid(mid)) {
		  	 ans = mid;
		  	 high = mid - 1;
		  } else {
		  	 low = mid + 1;
		  }
	}
	
	cout << ans << endl;
	return 0;
}
