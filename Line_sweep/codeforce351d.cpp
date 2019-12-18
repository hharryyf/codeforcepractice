#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 262192
typedef long long ll;
using namespace std;

struct BIT {
    int n = MAX_SIZE - 1;
    int tree[MAX_SIZE];
    
    void setsize(int n) {
		 this->n = n;
	}
	
	void set(int index, int val) {
		 if (index <= 0) return;
		 int curr = this->query(index, index);
		 this->add(index, val - curr);
	}
    
	void add(int index, int val) {
		 if (index <= 0) return;
		 while (index <= n) {
              tree[index] += val;
              index = index + shift(index);
		 }
	}
	
	int shift(int x) {
		return x & (-x);
	}
	
	int getsum(int index) {
		int ret = 0;
		while (index > 0) {
            ret += tree[index];
            index = index - shift(index);
		}
		
		return ret;
	}
	
	int query(int start, int end) {
		if (start > end) return 0;
		return getsum(end) - getsum(start - 1);
	}
};

struct qrs {
	int l, r, id;   
};

qrs qs[MAX_SIZE];
BIT tree1, tree2;
int ans[MAX_SIZE];
int arr[MAX_SIZE];
// the last ocurrence of a number 0 as default
int lst[MAX_SIZE];

// pos[i] records the all of the index of the number i
vector<int> pos[MAX_SIZE];
// fail[i] records the last failure position of number i
int fail[MAX_SIZE];

static bool cmp(const qrs &a, const qrs &b) {
    return a.r < b.r;
}

int main() {
	int i, m, q, j;
	scanf("%d", &m);
	tree1.setsize(m);
	tree2.setsize(m);
	for (i = 1; i <= m; i++) {
		scanf("%d", &arr[i]);
		
	}
	
	scanf("%d", &q);
	
	for (i = 1; i <= q; i++) {
		scanf("%d%d", &qs[i].l, &qs[i].r);
		qs[i].id = i;
	}
	
	sort(qs + 1, qs + 1 + q, cmp);
	
	for (i = 1, j = 1; i <= q; i++) {
		while (j <= m && j <= qs[i].r) {
  			  tree1.set(lst[arr[j]], 0);
	 		  lst[arr[j]] = j;
  		      tree1.set(j, 1);
  		      if ((int) pos[arr[j]].size() == 1) {
 		  	  	 tree2.set(pos[arr[j]].back(), 0);	    
			  } else if ((int) pos[arr[j]].size() > 1) {
			  	 int cnt = (int) pos[arr[j]].size(); 
		         tree2.set(pos[arr[j]][cnt - 1], 0);
				 if (j - pos[arr[j]][cnt - 1] != pos[arr[j]][cnt - 1] - pos[arr[j]][cnt - 2]) {
				 	tree2.set(fail[arr[j]], 0);
				 	tree2.set(pos[arr[j]][cnt - 2], -1);
				 	fail[arr[j]] = pos[arr[j]][cnt - 2];
				 }	 
			  }
			  
			  tree2.set(j, 1);
			  pos[arr[j]].push_back(j);
			  j++;
		}
		// if there exists a number that can be wipped out during the first round, the answer
		// is equivalent to the set size of the given range
		// otherwise, we need to add 1 to the answer
		ans[qs[i].id] = tree1.query(qs[i].l, qs[i].r) + (tree2.query(qs[i].l, qs[i].r) > 0 ? 0 : 1);
	}	
	
	for (i = 1; i <= q; i++) {
		printf("%d\n", ans[i]);
	}
	return 0;
}

