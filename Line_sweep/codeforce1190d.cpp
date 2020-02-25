#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 200011
typedef long long ll;
using namespace std;

struct BIT {
	   int n;
	   ll tree[MAX_SIZE];
	   
	   int shift(int x) {
	   	   return x & (-x);
	   }
	   
	   ll getans(int pos) {
	   	  ll ret = 0;
	   	  while (pos > 0) ret += tree[pos], pos -= shift(pos);
	   	  return ret;
	   }
	   
	   ll query(int l, int r) {
	   	   return getans(r) - getans(l-1);
	   }
	   
	   void update(int pos, ll val) {
	   		ll curr = query(pos, pos);
            while (pos <= n) {
   		 		  tree[pos] += val - curr;
	  			  pos += shift(pos);
			}
	   }
};

BIT t;

vector<int> disc;
int tmp[MAX_SIZE];
// y coord -> x coord
map<int, vector<int> > mp;
int main() {
	int n, i;
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		mp[-v2].push_back(v1);
		tmp[i] = v1;
	}
	
	sort(tmp + 1, tmp + 1 + n);
	
	for (i = 1; i <= n; i++) {
		if (i == 1 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
	}
	
	t.n = (int) disc.size();
	
	ll ans = 0;
	auto iter = mp.begin();
	while (iter != mp.end()) {
		  sort(iter->second.begin(), iter->second.end());
		  for (i = 0 ; i < (int) iter->second.size(); i++) {
  	            int idx = lower_bound(disc.begin(), disc.end(), iter->second[i]) - disc.begin() + 1;
  	            int idx2 = t.n;
		        if (i != (int) iter->second.size() - 1) {
  	               idx2 = lower_bound(disc.begin(), disc.end(), iter->second[i+1]) - disc.begin();
			    }
				t.update(idx, 1);
				ans += t.query(1, idx) * t.query(idx, idx2);
				
		  }
		  
		  iter++;
	}
	
	printf("%lld\n", ans);
	return 0;
}
