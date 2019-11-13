#include <bits/stdc++.h>
#define INF 1000000007
#define MAX_SIZE 524292
typedef int ll;
using namespace std;

int arr[MAX_SIZE];
int pre[MAX_SIZE];

struct segt {
	struct segt *left, *right;
	int l, r;
	ll lz, rsum;	
	segt(int l, int r) {
		this->l = l;
		this->r = r;
		this->lz = -INF;
		this->rsum = 0;
		this->left = this->right = NULL;
	}	
};

segt *version[MAX_SIZE];

segt *build(int l, int r) {
	if (l > r) return NULL;
	segt *t = new segt(l, r);
	if (l == r) {
		return t;
	}
	
	int mid = l + (r - l) / 2;
	t->left = build(l, mid);
	t->right = build(mid + 1, r);
	return t;
}

void pushdown(segt * &t) {
	if (t != NULL) {
		if (t->lz != -INF) {
			if (t->left != NULL && t->right != NULL) {
				int mid = t->l + (t->r - t->l) / 2;
				int len1 = mid - t->l + 1, len2 = t->r - mid;
				segt *t1 = new segt(t->l, mid);
				segt *t2 = new segt(mid + 1, t->r);
				t1->rsum = t->lz * len1;
				t1->lz = t->lz;
				t2->rsum = t->lz * len2;
				t2->lz = t->lz;
				t1->left = t->left->left;
				t1->right = t->left->right;
				t2->left = t->right->left;
				t2->right = t->right->right;
				t->left = t1;
				t->right = t2;
			}
			t->lz = -INF;
		}	
	}
}

ll query(int start, int end, segt *t) {
	if (start > end || t == NULL) return 0ll;
	pushdown(t);
	if (start > t->r || t->l > end) return 0ll;
	if (start <= t->l && t->r <= end) {
		return t->rsum;
	}
	int mid = t->l + (t->r - t->l) / 2;
	if (end <= mid) {
		return query(start, end, t->left);
	}
	
	if (start >= mid + 1) {
		return query(start, end, t->right);
	}
	
	return query(start, end, t->left) + query(start, end, t->right);
}

segt *update(int start, int end, segt *t, ll val) {
	if (start > end || t == NULL) return NULL;
	segt *ret = new segt(t->l, t->r);
	ret->left = t->left, ret->right = t->right;
	ret->rsum = t->rsum;
	ret->lz = t->lz;
	pushdown(ret);
	
	if (start > t->r || t->l > end) return ret;
	
	if (start <= t->l && t->r <= end) {
		ret->rsum = val * (t->r - t->l + 1);
		ret->lz = val;
		return ret;
	}
	
	ret->left = update(start, end, ret->left, val);
	ret->right = update(start, end, ret->right, val);
	ret->rsum = ret->left->rsum + ret->right->rsum;
	return ret;
}

ll queryversion(int start, int end, int vs) {
	return query(start, end, version[vs]);
}

int n, q;

int main() {
	int vs = 0;
	int lst = 0;
	scanf("%d", &n);
	scanf("%d", &q);
	version[vs++] = build(0, n);
	unordered_map<int, int> h;
	for (int i = 1 ; i <= n; i++) {
		scanf("%d", &arr[i]);
		if (h.find(arr[i]) == h.end()) {
			pre[i] = 0;
		} else {
			pre[i] = h[arr[i]];
		}
		
		h[arr[i]] = i;
		version[vs] = update(pre[pre[i]], pre[pre[i]], version[vs-1], 0);
		vs++;
		version[vs] = update(pre[i], pre[i], version[vs-1], -1);
		vs++;
		version[vs] = update(i, i, version[vs-1], 1);
		vs++;
	}	
	
	
	
	
	while (q > 0) {
		int l, r;
		scanf("%d%d", &l, &r);
		// l = l ^ lst, r = r ^ lst;
		lst = queryversion(l, r, 3 * r);
		printf("%d\n", lst);
		q--;
	}
	
	return 0;
}
