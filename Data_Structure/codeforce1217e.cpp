#include <bits/stdc++.h>
#define INF 3000000000ll
#define MAX_SIZE 524292
typedef long long ll;
using namespace std;

pair<ll, ll> tree[MAX_SIZE][10];
int mul[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
pair<ll, ll> pullup(pair<ll, ll> p1, pair<ll, ll> p2) {
	pair<ll, ll> p;
	if (p1.first < p2.first) {
	   p.first = p1.first;
	   p.second = min(p1.second, p2.first);
	} else {
	   p.first = p2.first;
	   p.second = min(p2.second, p1.first);
	}	 
    
    return p;
}

void build(int l, int r, int index) {
	 if (l > r) return;
	 int i, v;
	 if (l == r) {
	 	scanf("%d", &v);
	 	for (i = 0 ; i < 10; i++) {
			tree[index][i] = {INF, INF};
			if ((v / mul[i]) % 10 != 0) {
			   tree[index][i].first = v;
			} 
	    }
	 	return;
	 }
	 int mid = l + (r - l) / 2;
	 build(l, mid, index * 2);
	 build(mid + 1, r, index * 2 + 1);
	 for (i = 0 ; i < 10; i++) tree[index][i] = pullup(tree[index * 2][i], tree[index * 2 + 1][i]);
}

void update(int pos, int l, int r, int index, ll val, int dim) {
	 if (pos < l || pos > r || l > r) return;
	 if (pos == l && l == r) {
	 	tree[index][dim] = {val, INF};
	 	return;
	 }
	 
	 int mid = l + (r - l) / 2;
	 if (pos <= mid) {
	 	update(pos, l, mid, index * 2, val, dim);
	 } else {
	    update(pos, mid + 1, r, index * 2 + 1, val, dim);
	 }
	 tree[index][dim] = pullup(tree[index * 2][dim], tree[index * 2 + 1][dim]);
}

pair<ll, ll> query(int start, int end, int l, int r, int index, int dim) {
     if (start > end || l > r || start > r || l > end) return make_pair(INF, INF);
	 if (start <= l && r <= end) return tree[index][dim];
	 int mid = l + (r - l) / 2;
	 if (end <= mid) return query(start, end, l, mid, index * 2, dim);
	 if (start >= mid + 1) return query(start, end, mid + 1, r, index * 2 + 1, dim);
	 return pullup(query(start, end, l, mid, index * 2, dim), 
	               query(start, end, mid + 1, r, index * 2 + 1, dim));
}

int main() {
	int n, q, i;
	scanf("%d%d", &n, &q);
	build(1, n, 1);
	while (q > 0) {
		int tp, l, r;
		ll ans = INF;
		scanf("%d%d%d", &tp, &l, &r);
		if (tp == 2) {
			for (i = 0 ; i < 10; i++) {
				auto p = query(l, r, 1, n, 1, i);
				if (p.first < INF && p.second < INF) {
				   ans = min(p.first + p.second, ans);
				}
			}  
	        
	        printf("%lld\n", (ans < INF ? ans : -1));
		} else {
		    for (i = 0 ; i < 10; i++) {
				if ((r / mul[i]) % 10 != 0) {
				   update(l, 1, n, 1, r, i);   
				} else {
				   update(l, 1, n, 1, INF, i);
				}
			}
		}
        q--;
	}
	return 0;
}

