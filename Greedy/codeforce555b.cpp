#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 200011
typedef long long ll;
using namespace std;

struct gap {
	ll len;
	ll mxlen;
	int id;  
};
vector<gap> a;
vector<pair<ll, int> > b;
int ans[MAX_SIZE];
static bool cmp(const gap &g1, const gap &g2) {
	   return g1.mxlen < g2.mxlen;
}

int main() {
	int n, m, i, j;
	ll l, r;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n; i++) {
		if (i == 1) {
		   scanf("%lld%lld", &l, &r);
		} else {
		   ll v1, v2;
		   scanf("%lld%lld", &v1, &v2);
		   a.push_back(gap{v1 - r, v2 - l, i - 1});
		   l = v1, r = v2;
		}
	}
	
	for (i = 1; i <= m; i++) {
		scanf("%lld", &l);
		b.emplace_back(l, i);
	}
	
	sort(a.begin(), a.end(), cmp);
	sort(b.begin(), b.end());
	
	set<pair<ll, int> > st;
	int cnt = 0;
	for (i = 0, j = 0 ; i < (int) a.size(); i++) {
		while (j < (int) b.size() && a[i].mxlen >= b[j].first) {
			  st.insert(b[j++]);
		}
		
		auto iter = st.lower_bound(make_pair(a[i].len, 0));
		if (iter != st.end()) {
		   ans[a[i].id] = iter->second;
		   cnt++;
		   st.erase(iter);
		}
	}
	
	if (cnt != (int) a.size()) {
	   printf("No\n");
	   return 0;
	}
	printf("Yes\n");
	for (i = 1; i <= n - 1; i++) {
		printf("%d ", ans[i]);
	}
	printf("\n");
	return 0;
}
