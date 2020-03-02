#include <bits/stdc++.h>
// #define NORMAL
#define MOD 1000000007
#define MAX_SIZE 50011
typedef long long ll;
using namespace std;

struct task {
	   int st, id, pi;
	   ll ti;
	   bool operator < (task other) const {
	   		return pi < other.pi;
	   }
};

task tsk[MAX_SIZE];
int id, n;
ll T;
vector<int> candidate;
ll finish[MAX_SIZE];

static bool cmp(const task &t1, const task &t2) {
	   return t1.st < t2.st;
}

bool valid(int mid) {
	 int i;
	 tsk[id].pi = mid;
	 priority_queue<task> q;
	 ll t = 0;
	 for (i = 1; i <= n; i++) {
	 	 while (t < 1ll * tsk[i].st && !q.empty()) {
		 	   task p = q.top();
			   q.pop();
			   if (p.ti <= tsk[i].st - t) {
   	  		       t += p.ti;
   	  		       finish[p.id] = t;
  		       } else {
  		       	   p.ti -= tsk[i].st - t;
			       t = tsk[i].st;
				   q.push(p);	 
			   }
         }
         if (q.empty()) {
         	 t = max(t, 1ll * tsk[i].st);
         }
	 	 q.push(tsk[i]);
	 }	 
	 
	 while (!q.empty()) {
	 	   task p = q.top();
	 	   q.pop();
	 	   t += p.ti;
	 	   finish[p.id] = t;
	 }
	 
	 return finish[tsk[id].id] <= T;
}

int main(){
	#ifndef NORMAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
	scanf("%d", &n);
	int i;
	for (i = 1; i <= n; ++i) {
		scanf("%d%lld%d", &tsk[i].st, &tsk[i].ti, &tsk[i].pi);
		tsk[i].id = i;
	}
	scanf("%lld", &T);
	sort(tsk + 1, tsk + 1 + n);
	
	for (i = 2; i <= n; i++) {
		if (i == 2 && tsk[i].pi != 1) candidate.push_back(1);
	    if (i > 2 && tsk[i].pi - tsk[i-1].pi > 1) {
		   candidate.push_back(tsk[i-1].pi + 1);
		}
	}
	if (tsk[n].pi != 1000000000) {
	   candidate.push_back(tsk[n].pi + 1);
	}
	sort(tsk + 1, tsk + 1 + n, cmp);
	for (i = 1; i <= n; i++) {
		if (tsk[i].pi == -1) {
		   id = i;
		   break;
		}
	}
	
	int sz = (int) candidate.size() - 1;
	int low = 0, high = sz;
	int ans = 1000000000;
	while (low <= high) {
		  int mid = (low + high) >> 1;
		  if (valid(candidate[mid])) {
		  	 ans = candidate[mid];
		  	 high = mid - 1;
		  } else {
		  	 low = mid + 1;
		  }
	}
	
	printf("%d\n", ans);
	valid(ans);
	for (i = 1; i <= n; ++i) printf("%lld ", finish[i]);
	printf("\n");
	return 0;
}

