#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 300111
using namespace std;

vector<int> occ[MAX_SIZE];
class persistentTree {
public:    
    void setsize(int n) {
        this->n = n;
    }
    
    void update(int version, int pos, int val) {
        root[version] = inc(root[version - 1], pos, 1, n, val);
    }
    
    void build() {
        tree[0].left = tree[0].right = tree[0].value = 0;
        root[0] = crt(1, n);
    }
    
    int getkth(int L, int R, int k) {
        return query(root[L - 1], root[R], 1, n, k);
    }
    
private:
    struct segt {
        int left, right, value;  
    };
    
    segt tree[MAX_SIZE * 35];
    int cnt = 0;
    int root[MAX_SIZE];
    int n;
    
    int crt(int l, int r) {
        if (l > r) return 0;
        int curr = ++cnt;
        tree[curr].left = tree[curr].right = tree[curr].value = 0;
        if (l == r) {
            return curr;
        }
        int mid = l + (r - l)  / 2;
        tree[curr].left = crt(l, mid);
        tree[curr].right = crt(mid + 1, r);
        return curr;
    }
    
    int inc(int rt, int pos, int l, int r, int val) {
        if (l > r || pos < l || pos > r) return rt;
        int curr = ++cnt;
        tree[curr] = tree[rt];
        int mid = l + (r - l) / 2;
        if (l == r && pos == l) {
            tree[curr].value += val;
            return curr;
        }
        
        if (pos <= mid) {
            tree[curr].left = inc(tree[rt].left, pos, l, mid, val);
        } else {
            tree[curr].right = inc(tree[rt].right, pos, mid + 1, r, val);
        }
        tree[curr].value = tree[tree[curr].left].value + tree[tree[curr].right].value;
        return curr;
    }
    
    int query(int rt1, int rt2, int l, int r, int k) {
        if (l == r) return l;
        int mid = l + (r - l) / 2;
        int tol = tree[tree[rt2].left].value - tree[tree[rt1].left].value;
        if (tol >= k) {
            return query(tree[rt1].left, tree[rt2].left, l, mid, k);   
        }
        return query(tree[rt1].right, tree[rt2].right, mid + 1, r, k - tol);
    }
};

persistentTree tree;
int a[MAX_SIZE];

int main() {
    int i, n, q;
    scanf("%d%d", &n, &q);
    tree.setsize(n);
    tree.build();
    for (i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        tree.update(i, a[i], 1);
        occ[a[i]].push_back(i);
    }
    
    while (q > 0) {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        int len = (r - l + 1) / k;
        bool valid = false;
        if (len == 0) {
		   printf("%d\n", tree.getkth(l, r, 1));
		   valid = true;
		} else {
	        for (i = 1; i * len <= (r - l + 1); i++) {
	            int num = tree.getkth(l, r, i * len);
	            int L = lower_bound(occ[num].begin(), occ[num].end(), l) - occ[num].begin();
	            int R = upper_bound(occ[num].begin(), occ[num].end(), r) - occ[num].begin() - 1;
	            if (R - L + 1 > len) {
	                printf("%d\n", num);
	                valid = true;
	                break;
	            }
	        }
		}
        
        if (!valid) {
            printf("-1\n");
        }
        
        q--;
    }
    return 0;
}
