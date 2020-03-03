#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 200011
typedef long long ll;
using namespace std;

struct interval {
	   int l, r, id;
	   bool operator < (interval other) const {
	   		return r < other.r;
	   }
};

static bool cmp(const interval &a, const interval &b) {
	   return a.l < b.l;
}

int ans[MAX_SIZE];

int countcomponent(vector<interval> &a) {
	int ret = 0;
	int r = a[0].l - 1;
	for (auto it : a) {
		if (it.l > r) ret++;
		r = max(r, it.r);
	}
	return ret;
}

int solve(vector<interval> &a) {
	vector<interval> itv;
	vector<int> disc;
	int n = (int) a.size();
	int cnt = 0;
	int i, j;
	for (i = 0 ; i < n; i++) {
		ans[i] = 0;
		itv.push_back(a[i]);
	}
	
	sort(itv.begin(), itv.end(), cmp);
	for (i = 0 ; i < n; i++) {
		if (i == 0 || itv[i].l != itv[i-1].l) {
		   disc.push_back(itv[i].l);
        }
	}
	
	int ret = countcomponent(itv);	
	multiset<interval> s;
	priority_queue<int> rt;
	int sz = (int) disc.size();
	
	for (i = 0, j = 0 ; i < sz; i++) {
		while (!s.empty()) {
  			  auto iter = s.begin();
			  if (iter->r < disc[i]) {
			  	 rt.push(iter->r);
		         s.erase(iter);
			  } else {
			  	 break;
			  }
		}
		
		if ((int) s.size() == 1) {
		   if (!rt.empty() && rt.top() >= s.begin()->l) {
		   	  ans[s.begin()->id]++;
		   }
		}
		
		while (j < n && itv[j].l == disc[i]) {
			  s.insert(itv[j++]);
		}
		
		if ((int) s.size() == 1) {
		   if (j >= n || s.begin()->r < itv[j].l) {
		   	  	 ans[s.begin()->id] = -1;
				 rt.push(s.begin()->r);
				 s.erase(s.begin());
		   }
		}
	}
	
	cnt = ans[0];
	for (i = 0 ; i < n; i++) {
		cnt = max(ans[i], cnt);
	}
	
	return ret + cnt;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T > 0) {
		  int i, n;
		  vector<interval> itv;
		  scanf("%d", &n);
		  for (i = 0 ; i < n; i++) {
		  	  int l, r;
		  	  scanf("%d%d", &l, &r);
		  	  itv.push_back(interval{l, r, i});
		  }
		  printf("%d\n", solve(itv));
		  T--;
	}
	return 0;
}

