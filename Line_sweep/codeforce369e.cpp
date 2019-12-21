#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 1000025
typedef long long ll;
using namespace std;

struct interval {
   int l, r;
};

struct qrs {
    int l, r, id;
};	

struct BIT {
	   int n = MAX_SIZE - 1;
	   ll tree[MAX_SIZE];
	   
	   int shift(int x) {
	   	   return x & (-x);
	   }
	   
	   void update(int index, ll val) {
	   		if (index == 0) return;
	   		while (index <= this->n) {
			    tree[index] += val;
				index += shift(index);   
	        }
	   }
	   
	   ll getans(int index) {
       	    if (index == 0) return 0;
 	   	    ll ret = 0;
            while (index > 0) {
				ret += tree[index];
				index = index - shift(index);
		    }
		    return ret;
	   }
	   
	   ll query(int start, int end) {
	   	    if (start > end) return 0;
	   	    return getans(end) - getans(start - 1);
	   }
};

vector<qrs> qs;
int n;
interval arr[MAX_SIZE];
ll ans[MAX_SIZE];

static bool cmp_1(const interval &a, const interval &b) {
    return a.r < b.r;
}

static bool cmp_2(const qrs &a, const qrs &b) {
    return a.r < b.r;
}

BIT tree;

void addinterval(int l, int r, int id) {
	 if (l > r) return;
	 qs.push_back(qrs{l, r, id});
}

int main() {
	int m, i, j;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n; i++) {
		scanf("%d%d", &arr[i].l, &arr[i].r);
	} 
	
	sort(arr + 1, arr + 1 + n, cmp_1);
	
	for (i = 1; i <= m; i++) {
		int k;
		vector<int> pt;
		scanf("%d", &k);
		for (j = 0 ; j < k; j++) {
			int p;
			scanf("%d", &p);
			pt.push_back(p);
		}
		
		for (j = 0; j < k; j++) {
			if (j == 0) {
			   addinterval(0, pt[j] - 1, i);
			} else {
			   addinterval(pt[j-1] + 1, pt[j] - 1, i);
			}
		}
		
		addinterval(pt.back() + 1, 1000001, i);
	}
	
	sort(qs.begin(), qs.end(), cmp_2);
	
	for (i = 0, j = 1; i < (int) qs.size(); i++) {
		while (j <= n && arr[j].r <= qs[i].r) {
			  tree.update(arr[j].l, 1);
			  j++;
		}
		
		ans[qs[i].id] += tree.query(qs[i].l, qs[i].r);
	}
	
	for (i = 1; i <= m; i++) {
		printf("%lld\n", n - ans[i]);
	}
	return 0;
}

