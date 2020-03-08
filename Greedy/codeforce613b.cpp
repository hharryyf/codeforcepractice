#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 100011
typedef long long ll;
using namespace std;

struct people {
	ll skill;   
    int id;
	bool operator < (people other) const {
		 return skill < other.skill;
	}
};

ll prefix[MAX_SIZE];
ll A;
people p[MAX_SIZE];
ll result[MAX_SIZE];
int n;



ll getmax(ll m, int up) {
   ll low = p[1].skill, high = A;
   ll ret = A;
   while (low <= high) {
   		 ll mid = (low + high) >> 1;
   		 int idx = upper_bound(p + 1, p + up + 1, people{mid, 1}) - p - 1;
   		 // cout << mid << "---" << idx << " --> " << mid * idx - prefix[idx] << endl;
   		 if (mid * idx - prefix[idx] <= m) {
         	ret = mid;
         	low = mid + 1;
		 } else {
		    high = mid - 1;
		 }
   }
   return ret;
}

int main() {
	ll ans = 0;
	int cm, cf, i;
	ll m;
	scanf("%d%lld%d%d%lld", &n, &A, &cf, &cm, &m);
	for (i = 1; i <= n; i++) {
		scanf("%lld", &p[i].skill);
		p[i].id = i;
	}
	
	sort(p + 1, p + 1 + n);
	
	for (i = 1; i <= n; i++) prefix[i] = prefix[i-1] + p[i].skill;
	
	int select = n+1;
	ans = getmax(m, n) * cm;
	// we try to make [i, n] to range max
	for (i = n; i >= 1; i--) {
		ll delta = A * (n - i + 1) - prefix[n] + prefix[i-1];
		if (delta > m) break;
		ll tmp = 1ll * cf * (n - i + 1) + getmax(m - delta, i - 1) * cm;
		if (tmp > ans) {
		   ans = tmp, select = i;
		}
	}
	
	printf("%lld\n", ans);
    ll delta = A * (n - select + 1) - prefix[n] + prefix[select-1];
    ll rmin = getmax(m - delta, select - 1);
    for (i = n; i >= 1; i--) {
		result[p[i].id] = max(p[i].skill, rmin);
		if (i >= select) result[p[i].id] = A;
	}
	
	for (i = 1; i <= n; i++) printf("%lld ", result[i]);
	printf("\n");
	return 0;
}

