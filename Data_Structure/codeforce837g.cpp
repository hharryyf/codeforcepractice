#include <bits/stdc++.h>
#define MAX_SIZE 300111
typedef long long ll;
using namespace std;

class persistentTree {
public:
    void build(int n) {
        this->n = n;
        root[0] = crt(0, n - 1);
    }
    
    void update(int version, int start, int end, ll dk, ll db) {
        root[version] = upd(root[version - 1], start, end, 0, n - 1, dk, db);
    }
    
    pair<ll, ll> query(int version, int x) {
		return getsum(root[version], x, 0, n-1);
    }
    
private:
    int n;
    struct node {
        int left, right;
        ll k, b;
    };
    node tree[MAX_SIZE * 140];
    int cnt = 0;
    int root[MAX_SIZE];

    void pushdown(int rt, int l, int r) {
    	int mid = l + (r - l) / 2;
    	if (rt != 0) {
    		if (tree[rt].k != 0 || tree[rt].b != 0) {
    			if (tree[rt].left && tree[rt].right) {
    				int nl = ++cnt;
    				int nr = ++cnt;
    				tree[nl].k = tree[tree[rt].left].k + tree[rt].k;
    				tree[nl].b = tree[tree[rt].left].b + tree[rt].b;
    				tree[nr].k = tree[tree[rt].right].k + tree[rt].k;
    				tree[nr].b = tree[tree[rt].right].b + tree[rt].b;
    				tree[nl].left = tree[tree[rt].left].left;
    				tree[nl].right = tree[tree[rt].left].right;
    				tree[nr].left = tree[tree[rt].right].left;
    				tree[nr].right = tree[tree[rt].right].right;
    				tree[rt].left = nl;
    				tree[rt].right = nr;
    				tree[rt].k = tree[rt].b = 0;
				}
    		}	
    	}
    }
    
    int crt(int l, int r) {
        if (l > r) return 0;
        int curr = ++cnt;
        tree[curr].k = tree[curr].b = 0;
        if (l == r) {
            return curr;
        }
        
        int mid = l + (r - l) / 2;
        tree[curr].left = crt(l, mid);
        tree[curr].right = crt(mid + 1, r);
        return curr;
    }
    
    int upd(int rt, int start, int end, int l, int r, ll dk, ll db) {
        if (l > r || rt == 0) return rt;
        int curr = ++cnt;
        pushdown(rt, l, r);
        tree[curr] = tree[rt];
        if (start > r || l > end) return curr;
        if (start <= l && r <= end) {
            tree[curr].k += dk;
		    tree[curr].b += db;
		    return curr;
        }
        
        int mid = l + (r - l) / 2;
	    if (end <= mid) { 
		    tree[curr].left = upd(tree[rt].left, start, end, l, mid, dk, db);
	    } else if (start >= mid + 1) {
		    tree[curr].right = upd(tree[rt].right, start, end, mid + 1, r, dk, db);
	    } else {
	        tree[curr].left = upd(tree[rt].left, start, end, l, mid, dk, db);
	        tree[curr].right = upd(tree[rt].right, start, end, mid + 1, r, dk, db);
	    }
	    
	    return curr;
    }
    
    pair<ll, ll> getsum(int rt, int pos, int l, int r) {
        if (rt == 0 || l > r || pos < l || pos > r) return make_pair(0, 0);
        pushdown(rt, l, r);
        if (l == r && pos == l) {
            return make_pair(tree[rt].k, tree[rt].b);
        }
        
        int mid = l + (r - l) / 2;
        if (pos <= mid) {
            return getsum(tree[rt].left, pos, l, mid);
        }
        return getsum(tree[rt].right, pos, mid + 1, r);
    }
};

persistentTree tree;
vector<int> disc;
int tmp[MAX_SIZE];

ll lst = 0;
ll mod = 1000000000;

int arr[75011][6];

int main() {
    int n, q, i;
    scanf("%d", &n);
    int curr = 0;
    tmp[curr++] = 0;
    tmp[curr++] = mod + 1;
    for (i = 0; i < n; i++) {
        int x1, x2, y1, a, b, y2;
        scanf("%d%d%d%d%d%d", &x1, &x2, &y1, &a, &b, &y2);
        tmp[curr++] = x1, tmp[curr++] = x1 + 1, tmp[curr++] = x2, tmp[curr++] = x2 + 1;
        arr[i][0] = x1, arr[i][1] = x2, arr[i][2] = y1, arr[i][3] = a, arr[i][4] = b, arr[i][5] = y2;
    }
    
    sort(tmp, tmp + curr);
    
    for (i = 0 ; i < curr; i++) {
        if (i == 0 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
    }
    
    int m = disc.size();
    tree.build(m);
    int vs = 1;
    for (i = 0 ; i < n; i++) {
        int R1 = lower_bound(disc.begin(), disc.end(), arr[i][0]) - disc.begin();
        int L2 = lower_bound(disc.begin(), disc.end(), arr[i][0] + 1) - disc.begin();
        int R2 = lower_bound(disc.begin(), disc.end(), arr[i][1]) - disc.begin();
        int R3 = lower_bound(disc.begin(), disc.end(), arr[i][1] + 1) - disc.begin();
        //cout << 0 << " " << R1 << " " << L2 << " " << R2 << " " << R3 << endl;
        tree.update(vs++, 0, R1, 0, arr[i][2]);
        tree.update(vs++, L2, R2, arr[i][3], arr[i][4]);
        tree.update(vs++, R3, m-1, 0, arr[i][5]);
    }
    
    scanf("%d", &q);
    while (q > 0) {
        int l, r;
        ll x;
        scanf("%d%d%lld", &l, &r, &x);
        x = (x + lst) % mod;
        int idx = upper_bound(disc.begin(), disc.end(), x) - 1 - disc.begin();
        auto p1 = tree.query(3 * r, idx);
        auto p2 = tree.query(3 * (l-1), idx);
        
        lst = (p1.first - p2.first) * x + (p1.second - p2.second);
        printf("%lld\n", lst);
        q--;
    }
    return 0;
}
