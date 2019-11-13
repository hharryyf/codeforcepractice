#include <bits/stdc++.h>
#define INF 0
#define MAX_SIZE 262192
typedef int ll;
using namespace std;

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
	pushdown(t);
	
	ret->left = t->left, ret->right = t->right;
	ret->rsum = t->rsum;
	ret->lz = t->lz;
	
	if (start > t->r || t->l > end) return ret;
	
	if (start <= t->l && t->r <= end) {
		ret->rsum = val * (t->r - t->l + 1);
		ret->lz = val;
		return ret;
	}
	
	int mid = t->l + (t->r - t->l) / 2;
	if (end <= mid) { 
		ret->left = update(start, end, t->left, val);
	} else if (start >= mid + 1) {
		ret->right = update(start, end, t->right, val);
	} else {
		ret->left = update(start, end, t->left, val);
		ret->right = update(start, end, t->right, val);
	}
	
	ll c1 = ret->left == NULL ? 0 : ret->left->rsum;
	ll c2 = ret->right == NULL ? 0 : ret->right->rsum;
	ret->rsum = c1 + c2;
	return ret;
}

ll queryversion(int start, int end, int vs) {
	return query(start, end, version[vs]);
}

int n, q;

char str[4];

void debug(segt *t, int dpt) {
	if (t != NULL) {
		
		debug(t->right, dpt + 1);
		for (int i = 0 ; i < dpt; i++) {
			cout << "\t";
		}
		cout << "[" << t->l << " " << t->r << "]" << " " << t->rsum << " " << t->lz << "id: " << t << endl;
		debug(t->left, dpt + 1);
	}
}
/* note that query is [l,r)*/
int main() {
	int vs = 0;
	scanf("%d", &n);
	version[vs++] = build(0, n);
	scanf("%d", &q);
	ll lst = 0;
	while (q > 0) {
		scanf("%s", str);
		if (str[0] == 'U') {
			int l, r;
			ll val;
			scanf("%d%d%d", &l, &r, &val);
		    // l = l ^ lst;
		    // r = r ^ lst;
		    // val = val ^ lst;
			version[vs] = update(l, r-1, version[vs-1], val);
			vs++;
		} else {
			int v, l, r;
			scanf("%d%d%d", &v, &l, &r);
			// v = v ^ lst;
			// l = l ^ lst;
			// r = r ^ lst;
			lst = queryversion(l, r-1, v);
			printf("%d\n", lst);
		}
		q--;
	}
	
	exit(0);
	return 0;
}
