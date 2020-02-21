#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 100111
using namespace std;
typedef long long ll;

struct qrs {
    int x, r, iq;
};

qrs add[MAX_SIZE], del[MAX_SIZE];
vector<int> disc;
int tmp[MAX_SIZE];

static bool cmp_1(const qrs &a, const qrs &b) {
    return (a.x + a.r) < (b.x + b.r);
}

static bool cmp_2(const qrs &a, const qrs &b) {
    return a.x < b.x;
}

struct dynamictree {
    struct node {
        int val;
        int l, r;
        struct node *left, *right;
    
        node(int l, int r, int val) {
            this->left = this->right = NULL;
            this->l = l, this->r = r, this->val = val;
        }
    };
    
    node *tree[MAX_SIZE];
    
    node *inc(node *rt, int pos, int l, int r, int val) {
        if (l > r || pos < l || pos > r) return rt;
        if (rt == NULL) {
            rt = new node(l, r, 0);
        }
        
        if (l == r && pos == r) {
            rt->val += val;
            return rt;
        }
        
        int mid = l + (r - l) / 2;
        if (pos <= mid) {
            rt->left = inc(rt->left, pos, l, mid, val);
        } else {
            rt->right = inc(rt->right, pos, mid + 1, r, val);
        }
        int v1 = rt->left == NULL ? 0 : rt->left->val;
        int v2 = rt->right == NULL ? 0 : rt->right->val;
        rt->val = v1 + v2;
        return rt;
    }
    
    int getans(node *rt, int l, int r) {
        if (rt == NULL) return 0;
        if (l <= rt->l && rt->r <= r) return rt->val;
        int mid = rt->l + (rt->r - rt->l) / 2;
        if (r <= mid) {
            return getans(rt->left, l, r);
        } else if (l >= mid + 1) {
            return getans(rt->right, l, r);
        } else {
            return getans(rt->left, l, r) + getans(rt->right, l, r);
        }
    }
    
    // increment pos by val in tree[version]
    void update(int pos, int val, int version) {
        tree[version] = inc(tree[version], pos, 0, 1000000000, val);
    }
    
    int query(int l, int r, int version) {
        return getans(tree[version], l, r);
    }
};

dynamictree tree;

int getindex(int x) {
	return lower_bound(disc.begin(), disc.end(), x) - disc.begin();
}

int main() {
    int n, k, i, j, l;
    scanf("%d%d", &n, &k);
    for (i = 0 ; i < n; i++) {
		scanf("%d%d%d", &add[i].x, &add[i].r, &add[i].iq);
		tmp[i] = add[i].iq;
		del[i] = add[i];
	}
	
	sort(tmp, tmp + n);
	sort(add, add + n, cmp_2);
	sort(del, del + n, cmp_1);
	for (i = 0 ; i < n; i++) {
		if (i == 0 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
	}
	ll cnt = 0;
	for (i = 0, j = 0; i < n; i++) {
		while (j < n && (del[j].r + del[j].x) < add[i].x) {
  			  tree.update(del[j].x, -1, getindex(del[j].iq));
  			  j++;
		}
		
		int v1 = lower_bound(disc.begin(), disc.end(), add[i].iq - k) - disc.begin();
		int v2 = upper_bound(disc.begin(), disc.end(), add[i].iq + k) - disc.begin() - 1;
		for (l = v1; l <= v2; l++) {
			cnt += tree.query(max(add[i].x - add[i].r, 0), add[i].x, l);
		}
		
		tree.update(add[i].x, 1, getindex(add[i].iq));
	}
	
	cout << cnt << endl;
    return 0;
}
