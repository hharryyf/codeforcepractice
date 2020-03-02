#include <bits/stdc++.h>
#define MOD 1000000007
#define BLOCK 452
//#define DEBUG
typedef long long ll;
using namespace std;

int n;
vector<int> b[BLOCK];
int a[BLOCK * BLOCK];
int bid[BLOCK * BLOCK];
ll cnt = 0;
int block_size;
// add v to b[id]
void add(int v, int id) {
	 b[id].push_back(v);
	 int i = (int) b[id].size() - 1;
	 while (i > 0 && b[id][i] < b[id][i-1]) {
	 	   swap(b[id][i], b[id][i-1]);
	 	   i--;
	 } 	 
}
// remove v from b[id]
void del(int v, int id) {
	 int i = lower_bound(b[id].begin(), b[id].end(), v) - b[id].begin();
	 int sz = (int) b[id].size() - 1;
	 while (i < sz) {
  	 	   swap(b[id][i], b[id][i+1]);
  	 	   i++;
	 }
	 b[id].pop_back();
}
// return how many numbers are less than v in range [l, r]
int query(int l, int r, int v) {
	if (l > r) return 0;
	int ret = 0;
	int i;
	for (i = l; i <= r && i < (bid[l] + 1) * block_size; ++i) ret += (a[i] < v);		
	if (bid[l] != bid[r]) {
	   for (i = bid[r] * block_size; i <= r; ++i) ret += (a[i] < v);
	   for (i = bid[l] + 1; i <= bid[r] - 1; ++i) ret += lower_bound(b[i].begin(), b[i].end(), v) - b[i].begin();
	}
	
	return ret;
}

void show() {
	 int i;
	 cout << "----start----" << endl;
	 for (i = 0 ; i <= block_size; i++) {
	 	 for (auto v : b[i]) cout << v << " ";
	 	 cout << endl;
	 }
	 cout << "----end----" << endl;
}

int main() {
	int i, q, j;
	scanf("%d%d", &n, &q);
	block_size = sqrt(n);
	for (i = 0 ; i <= block_size + 1; i++) {
		for (j = i * block_size; j < (i+1) * block_size && j < n; j++) {
			bid[j] = i;
			add(j, bid[j]);
			a[j] = j;
		}
	}
	
	while (q > 0) {
		  int l, r;
		  scanf("%d%d", &l, &r);
		  l--, r--;
		  if (l > r) swap(l, r);
		  if (l == r) {
		  	 printf("%lld\n", cnt);
		  	 q--;
		  	 continue;
		  }
		  
		  cnt += 1ll * (query(l+1, r-1, a[r]) - query(l+1, r-1, a[l])) * 2;
		  if (a[l] < a[r]) {
		      cnt++;
		  } else {
		  	  cnt--;
		  }
		  printf("%lld\n", cnt);
		  if (bid[l] != bid[r]) {
		  	 del(a[l], bid[l]);
		  	 del(a[r], bid[r]);
		  	 add(a[l], bid[r]);
		  	 add(a[r], bid[l]);
		  }
		  swap(a[l], a[r]);
		  
		  #ifdef DEBUG
		  show();
		  #endif
		  
		  q--;
	}
	return 0;
}

