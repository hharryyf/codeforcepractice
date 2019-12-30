#include <bits/stdc++.h>
#pragma GCC optimize(2)
#define MOD 1000000007
#define MAX_SIZE 524292
typedef long long ll;
using namespace std;

/*
  This problem was the 10th 2400+ data structure problem solved during the holiday.
  This problem use exactly the same trick as codeforce817f MEX query, we
  need to manage 2 tags at the same time.
  Firstly, we can observe that we just need to answer for all numbers from -1e5 to 1e5
  at the end of the operation is it sign flipped or not
  we use 1 to represent non-flip, -1 -> flip
  Then, the problem simply reduce to the following, for each update, we set [-1e5, -v] to -1
  invert the bit of [-v + 1, v-1], set [v, 1e5] to 1.
  Of course, edge cases such as v > 0, v < 0 should be considered.
  
  Then the lazy propagation part would be quite straight forward. if we meet a set tag, we cancel the
  invert tag of the child and change the set tag of the child. if we meet an invert tag, we invert the 
  child's invert tag.
*/

const int L = 0, R = 200000, shift = 100000;

struct segt {
	   int value, lz, ivt;
};

segt tree[MAX_SIZE];

void build(int l, int r, int index) {
	 if (l > r) return;
	 tree[index].value = tree[index].ivt = 1;
 	 tree[index].lz = 0;
	 if (l == r) {
		 return;
	 }
	 
	 int mid = l + (r - l) / 2;
	 build(l, mid, index * 2);
	 build(mid + 1, r, index * 2 + 1);
}

void pushdown(int l, int r, int index) {
	 if (l > r) return;
	 if (tree[index].lz != 0) {
	 	if (l != r) {
	       tree[index * 2].lz = tree[index * 2 + 1].lz = tree[index].lz;
	       tree[index * 2].value = tree[index * 2 + 1].value = tree[index].lz;
	       tree[index * 2 + 1].ivt = tree[index * 2].ivt = 1;
		}
	 }
	 
	 if (tree[index].ivt != 1) {
	 	if (l != r) {
	       tree[index * 2].ivt *= -1;
		   tree[index * 2 + 1].ivt *= -1;
		   tree[index * 2].value *= -1;
		   tree[index * 2 + 1].value *= -1;
		}
	 }
	 
	 tree[index].lz = 0;
	 tree[index].ivt = 1;
}

void update(int start, int end, int l, int r, int index, int val) {
	 if (start > end || l > r) return;
	 pushdown(l, r, index);
	 if (start > r || l > end) return;
	 if (start <= l && r <= end) {
	 	tree[index].value = val;
	 	tree[index].lz = val;
	 	tree[index].ivt = 1;
	 	return;
	 }
	 
	 int mid = l + (r - l) / 2;
	 update(start, end, l, mid, index * 2, val);
	 update(start, end, mid + 1, r, index * 2 + 1, val);
	 tree[index].value = max(tree[index * 2].value, tree[index * 2 + 1].value);
}

void invert(int start, int end, int l, int r, int index) {
	 if (start > end || l > r) return;
	 pushdown(l, r, index);
	 if (start > r || l > end) return;
	 if (start <= l && r <= end) {
	 	tree[index].value *= -1;
	 	tree[index].ivt *= -1;
	 	return;
	 }
	 
	 int mid = l + (r - l) / 2;
	 invert(start, end, l, mid, index * 2);
	 invert(start, end, mid + 1, r, index * 2 + 1);
	 tree[index].value = max(tree[index * 2].value, tree[index * 2 + 1].value);
}

int query(int pt, int l, int r, int index) {
	int mid = l + (r - l) / 2;
	if (pt < l || pt > r || l > r) return 1;
	pushdown(l, r, index);
	if (l == r && r == pt) {
	   return tree[index].value;
	}
	
	if (pt <= mid) return query(pt, l, mid, index * 2);
	return query(pt, mid + 1, r, index * 2 + 1);
}

char st[4];
int arr[MAX_SIZE >> 1];

int main() {
	int i, n, m;
	scanf("%d%d", &n, &m);
	build(L, R, 1);
	for (i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
	}
	
	for (i = 1; i <= m; i++) {
		int v;
		scanf("%s%d", st, &v);
		if (st[0] == '<') {
		   if (v > 0) {
		   	  update(L, -v + shift, L, R, 1, -1);
		   	  invert(-v + shift + 1, v + shift - 1, L, R, 1);
		   	  update(v + shift, R, L, R, 1, 1);
		   	  //cout << "update " << L - shift << " " << -v << " to -1 " << endl;
		   	  //cout << "invert " << -v + 1 << " " << v - 1 << endl;
			  //cout << "update " << v << " " << R - shift << " to 1 " << endl;	  
		   } else {
		   	  update(L, v + shift - 1, L, R, 1, -1);
			  update(-v + shift + 1, R, L, R, 1, 1);	
			  //cout << "update " << L - shift << " " << v << " to -1 " << endl; 
			  //cout << "update " << -v + 1 << " " << R - shift << " to 1 " << endl;   
		   }
		} else {
		   if (v < 0) {
		   	  update(L, v + shift, L, R, 1, 1);
		   	  invert(v + shift + 1, -v + shift - 1, L, R, 1);
		   	  update(-v + shift, R, L, R, 1, -1);
		   	  //cout << "update " << L - shift << " " << v - 1 << " to 1 " << endl;
		   	  //cout << "invert " << v + 1 << " " << v - 1 << endl;
			  //cout << "update " << v << " " << R - shift << " to 1 " << endl;
		   } else {
		   	  update(L, -v + shift - 1, L, R, 1, 1);
		   	  update(v + shift + 1, R, L, R, 1, -1);
		   }
		}
	}
	
	for (i = 1; i <= n; i++) {
		printf("%d ", arr[i] * query(arr[i] + shift, L, R, 1));
	}
	printf("\n");
	return 0;
}

