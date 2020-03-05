#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 100011
typedef long long ll;
using namespace std;

int n, len, k;
int a[MAX_SIZE];
// we can greedily solve this problem
// firstly, we change no more than k negative
// numbers in the given interval to positive
// and calculate the maximum expression value
// secondly, we change no more than k positive
// numbers in the given interval to neagtive
// and calculate the maximum expression value
// we can proof that we just need to change
// the k values with the largest absolute value
ll ans = 0;
// value, index
set<pair<int, int> > s1, s2;
// invariant, currently the window size is k
void balance() {
	 // s1 size is less than k
	 while ((int) s1.size() < k && !s2.empty()) {
  	 	   auto p = *s2.begin();
  	 	   s1.insert(p);
  	 	   s2.erase(p);
  	 	   ans -= 1ll * 2 * p.first;
	 } 	 	 
	 
	 while ((int) s1.size() > k) {
	 	   auto p = *s1.rbegin();
	 	   s1.erase(p);
	 	   ans += 1ll * 2 * p.first;
	 	   s2.insert(p);
	 }
	 
	 while (!s1.empty() && !s2.empty()) {
	 	   auto p1 = *s1.rbegin();
	 	   auto p2 = *s2.begin();
	 	   if (p1 > p2) {
		   	  	s1.erase(p1);
		   	  	ans += 1ll * 2 * p1.first;
		   	  	ans -= 1ll * 2 * p2.first;
		   	  	s2.insert(p1);
		   	  	s1.insert(p2);
		   	  	s2.erase(p2);
		   } else {
		   	    break;
		   }
	 }
}

void del(int idx) {
	if (s1.find(make_pair(a[idx], idx)) != s1.end()) {
	   s1.erase(make_pair(a[idx], idx));
	   ans += a[idx];
	} else {
       ans -= a[idx];
 	   s2.erase(make_pair(a[idx], idx));
	}
	
	balance();
}

void add(int idx) {
	if (a[idx] >= 0) {
	   ans += a[idx];   
	} else {
	   ans -= a[idx];
	   s1.insert(make_pair(a[idx], idx));
	}
	
	balance();
}

ll solve() {
	 ll ret = -1000000000000000;
	 int i;
	 // invariant, s1, s2 only stores [len-i+1, i]
	 // s1 stores at most k numbers, s2 stores
	 s1.clear(), s2.clear();
	 ans = 0;
	 for (i = 1; i <= n; i++) {
	 	  if (i > len) {
		   	 del(i-len);
          }
          add(i);
          if (i >= len) {
		  	 ret = max(ret, ans);
		  	 
		  }  
		 //  cout << i << " " << ans << endl;      
	 }
	 return ret;
}

int main() {
	scanf("%d%d", &n, &len);
	int i;
	for (i = 1; i <= n; i++) scanf("%d", &a[i]);
	scanf("%d", &k);
	ll ret = solve();
	for (i = 1; i <= n; i++) a[i] *= -1;
	ret = max(ret, solve());
	printf("%lld\n", ret);
	return 0;
}
