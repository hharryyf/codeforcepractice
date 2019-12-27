#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 262192
typedef long long ll;
using namespace std;

vector<int> a[MAX_SIZE];

struct persistentTree {
    struct node {
        int l, r, val;
	    node *left, *right;   
	    node(int l, int r) {
	        this->l = l;
	        this->r = r;
	        this->val = 0;
	        this->left = this->right = NULL;
	    }
    };
	
	node *root[MAX_SIZE];
	
	persistentTree() {
	    int i;
	    for (i = 0 ; i < MAX_SIZE; i++) root[i] = NULL;
	}
	
	node *build(int l, int r) {
	    if (l > r) return NULL;
	    node *t = new node(l, r);
	    if (l == r) {
	        return t;
	    }
	    
	    int mid = l + (r - l) / 2;
	    t->left = build(l, mid);
	    t->right = build(mid + 1, r);
	    return t;
	}
	
	void init(int n) {
	    root[0] = build(1, n);
	}
	
	node *upd(node *t, int pos, int val) {
	    if (t == NULL) return NULL;
	    node *nd = new node(t->l, t->r);
	    nd->left = t->left;
	    nd->right = t->right;
	    int mid = t->l + (t->r - t->l) / 2;
	    if (nd->l == nd->r && nd->l == pos) {
	        nd->val = val;
	        return nd;
	    }
	    
	    if (pos <= mid) {
	        nd->left = upd(t->left, pos, val);
	    } else {
	        nd->right = upd(t->right, pos, val);
	    }
	    
	    nd->val = nd->left->val + nd->right->val;
	    return nd;
	}
	
	// set pos to val in version i
	void update(int version, int pos, int val) {
	    if (version <= 0) return;
	    root[version] = upd(root[version - 1], pos, val);
	}
	
	int query(node *t, int start, int end) {
	    if (t == NULL || start > end) return 0;
	    if (t->l > end || start > t->r) return 0;
	    if (start <= t->l && t->r <= end) return t->val;
	    return query(t->left, start, end) + query(t->right, start, end);
	}
	
	int getsum(int version, int l, int r) {
	    return query(root[version], l, r); 
	}
};

int n, k;
persistentTree tree = persistentTree();
int rt[MAX_SIZE];

int main() {
    scanf("%d%d", &n, &k);
    int i, v;
    int vs = 1;
    tree.init(n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &v);
        a[v].push_back(i);
        if (a[v].size() > k) {
            tree.update(vs++, a[v][a[v].size() - k - 1], 0);
        }
        tree.update(vs++, i, 1);
        rt[i] = vs - 1;
    }
    
    int q;
    int lst = 0;
    scanf("%d", &q);
    while (q > 0) {
        int l, r;
        scanf("%d%d", &l, &r);
        l = (l + lst) % n + 1;
        r = (r + lst) % n + 1;
        if (l > r) swap(l, r);
        lst = tree.getsum(rt[r], l, r);
        printf("%d\n", lst);
        q--;
    }
	return 0;
}

