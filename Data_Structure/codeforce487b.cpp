#include <bits/stdc++.h>
#define MOD 1000000007
#define INF 10000000
#define MAX_SIZE 262192
typedef long long ll;
using namespace std;

int a[MAX_SIZE];
int table[MAX_SIZE >> 1][18][2];
int tree[MAX_SIZE];
int n, s, L;
int logs[MAX_SIZE];

void construct() {
	 int i, j;
	 tree[1] = INF;
	 for (i = 2; i < MAX_SIZE; i++) {
	 	 tree[i] = INF;
	 	 logs[i] = logs[i/2] + 1;
	 }
	 
	 for (i = 1 ; i <= n; i++) {
	 	 table[i][0][0] = table[i][0][1] = a[i];
	 }	 
	 
	 for (i = 1; i <= 17; i++) {
	 	 int prev2 = 1 << (i-1);
         for (j = 1; j <= n; j++) {
		  	 int intEnd = j + prev2;
		  	 if (intEnd <= n) {
	         	table[j][i][0] = min(table[j][i-1][0], table[intEnd][i-1][0]);
	         	table[j][i][1] = max(table[j][i-1][1], table[intEnd][i-1][1]);
			 } else {
			    table[j][i][0] = table[j][i-1][0];
			    table[j][i][1] = table[j][i-1][1];
			 }
         }
	 }
}
// query the rangemax - range min
int rmq(int l, int r) {
	int len = logs[r - l + 1];
	int rmax = max(table[l][len][1], table[r + 1 - (1 << len)][len][1]);
	int rmin = min(table[l][len][0], table[r + 1 - (1 << len)][len][0]);
	return rmax - rmin;
}

void update(int pos, int l, int r, int index, int val) {
	 if (pos < l || pos > r || l > r) return;
	 if (l == r && r == pos) {
	 	tree[index] = val;
	 	return;
	 }
	 
	 int mid = l + (r - l) / 2;
	 if (pos <= mid) {
	 	update(pos, l, mid, index * 2, val);
	 } else {
	    update(pos, mid + 1, r, index * 2 + 1, val);
	 }
	 tree[index] = min(tree[index * 2], tree[index * 2 + 1]);
}

int query(int start, int end, int l, int r, int index) {
	if (start > end || l > r || start > r || l > end) return INF;
	if (start <= l && r <= end) return tree[index];
	int mid = l + (r - l) / 2;
	if (end <= mid) return query(start, end, l, mid, index * 2);
	if (start >= mid + 1) return query(start, end, mid + 1, r, index * 2 + 1);
	return min(query(start, end, l, mid, index * 2), query(start, end, mid + 1, r, index * 2 + 1));
}

int main() {
	scanf("%d%d%d", &n, &s, &L);
	int i;
	for (i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	
	construct();
	
	for (i = 1; i <= n; i++) {
		   // get the leftmost position that safisfy the condition
        int low = 1, high = i;
        int idx = i + 1;
        while (low <= high) {
  		    int mid = (low + high) >> 1;
  		    int delta = rmq(mid, i);
  		    if (delta <= s) {
	            idx = mid;
	            high = mid - 1;	
            } else {
	            low = mid + 1;
            }
        }	   
		   
        if (i - idx + 1 < L) {
	   	    update(i, 1, n, 1, INF);
        } else {
		    if (idx == 1) {
			   update(i, 1, n, 1, 1);
			   // cout << i << endl;
			} else {
			   int pre = query(idx - 1, i - L, 1, n, 1);
			   update(i, 1, n, 1, pre + 1);
			}
		}
	}
	
	int ans = query(n, n, 1, n, 1);
	if (ans < INF) {
	   printf("%d\n", ans);
	} else {
	   printf("-1\n");
	}
	return 0;
}

