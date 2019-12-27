#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 10012
#define INF 1000000000
typedef long long ll;
using namespace std;
// the algorithm would work as follows
// sort according to x in ascending order
// for each radio station, we want to make sure when we query
// all the points that can reach this radio
// station has been added

// sort according to x-r for the add event
// sort according to x for the query event
// for each radio station, add in all the radio station that has xi-ri <= x
// query [x, x+r] for all [max(f-k, 1), min(f+k, 10000)]
// remember that ans - 1 for each query
// but I didn't know dynamic range tree could work in this case, this means
// I'm still a bit too young, sometimes naive
struct DynamicTree {
	struct node {
	    int l, r;
		int val;
		node *left, *right;
		node(int l, int r, int val) {
		    this->l = l;
		    this->r = r;
		    this->val = val;
		   	this->left = this->right = NULL;
		}
	};
	
	node *root[MAX_SIZE];
	DynamicTree() {
        int i;
        for (i = 0 ; i < MAX_SIZE; i++) {
            root[i] = new node(1, INF, 0);
        }
	}
	
	node *update(node *t, int pt, int val) {
	    int mid = t->l + (t->r - t->l) / 2;
	    if (t->l == t->r && t->l == pt) {
	        t->val += val;
	        return t;
	    }
	    
	    if (t->left == NULL) {
	        t->left = new node(t->l, mid, 0);
	    }
	    
	    if (t->right == NULL) {
	        t->right = new node(mid + 1, t->r, 0);
	    }
	    
	    if (pt <= mid) {
	        t->left = update(t->left, pt, val);
	    } else {
	        t->right = update(t->right, pt, val);
	    }
	    
	    t->val = t->left->val + t->right->val;
	    
	    return t;
	}
	
	int query(node *t, int l, int r) {
	    if (t == NULL) return 0;
	    if (t->l > r || l > r || t->l > t->r || l > t->r) return 0;
	    if (l <= t->l && t->r <= r) return t->val;
	    return query(t->left, l, r) + query(t->right, l, r);
	}
	
	void insert(int version, int index, int val) {
	    root[version] = update(root[version], index, val);  
	}
	
	int getans(int version, int l, int r) {
	    return query(root[version], l, r);
	}
};

DynamicTree tree = DynamicTree();

struct pt {
    int x, r, f;  
};

pt qrs[MAX_SIZE * 10];

pt ist[MAX_SIZE * 10];

static bool cmp_1(const pt &a, const pt &b) {
    return a.x < b.x;
}

static bool cmp_2(const pt &a, const pt &b) {
    return (a.x - a.r) < (b.x - b.r);
}


int main() {
	ll ans = 0;
	int n, k, i, j, pp;
	scanf("%d%d", &n, &k);
	for (i = 0 ; i < n; i++) {
	    scanf("%d%d%d", &qrs[i].x, &qrs[i].r, &qrs[i].f);
	    ist[i].x = qrs[i].x;
	    ist[i].r = qrs[i].r;
	    ist[i].f = qrs[i].f;
	}
	
	sort(qrs, qrs + n, cmp_1);
	sort(ist, ist + n, cmp_2);
	
	for (i = 0, j = 0 ; i < n; i++) {
	    while (j < n && ist[j].x - ist[j].r <= qrs[i].x) {
	        tree.insert(ist[j].f, ist[j].x, 1);
	        j++;
	    }
	    
	    for (pp = max(1, qrs[i].f - k); pp <= min(10000, qrs[i].f + k); pp++) {
	        ans += tree.getans(pp, qrs[i].x, qrs[i].x + qrs[i].r);
	    }
	    ans--;
	}
	
	printf("%lld\n", ans);
	return 0;
}

