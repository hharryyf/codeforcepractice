#include <bits/stdc++.h>
#define MAX_SIZE 524292
using namespace std;

struct segt {
	int lz;
	int value;
};

segt row[MAX_SIZE], col[MAX_SIZE];

int tmp1[MAX_SIZE], tmp2[MAX_SIZE];
vector<int> disc1, disc2;
int n, q;
int op[MAX_SIZE >> 1][3];

void build(segt tree[], int l, int r, int index) {
    if (l > r) return;
    tree[index].value = 1;
    if (l == r) return;
    int mid = l + (r - l) / 2;
    build(tree, l, mid, index * 2);
    build(tree, mid + 1, r, index * 2 + 1);
}

void pushdown(segt tree[], int l, int r, int index) {
    if (l < r) {
        if (tree[index].lz != 0) {
            tree[index * 2].lz = max(tree[index].lz, tree[index * 2].lz);
            tree[index * 2 + 1].lz = max(tree[index].lz, tree[index * 2 + 1].lz);
            tree[index * 2].value = max(tree[index].lz, tree[index * 2].value);
            tree[index * 2 + 1].value = max(tree[index].lz, tree[index * 2 + 1].value);
        }
        tree[index].lz = 0;
    }
}

int query(segt tree[], int pt, int l, int r, int index) {
    if (l > r) return 0;
    pushdown(tree, l, r, index);
    if (pt == l && r == l) return tree[index].value;
    int mid = l + (r - l) / 2;
    if (pt <= mid) return query(tree, pt, l, mid, index * 2);
    return query(tree, pt, mid + 1, r, index * 2 + 1);
}

void update(segt tree[], int start, int end, int l, int r, int index, int val) {
    if (start > end || l > r) return;
    pushdown(tree, l, r, index);
    if (start > r || l > end) return;
    if (start <= l && r <= end) {
        tree[index].value = max(tree[index].value, val);
        tree[index].lz = val;
        return;
    }
    
    int mid = l + (r - l) / 2;
    update(tree, start, end, l, mid, index * 2, val);
    update(tree, start, end, mid + 1, r, index * 2 + 1, val);
    tree[index].value = max(tree[index * 2].value, tree[index * 2 + 1].value);
}

char st[4];

int main() {
	scanf("%d%d", &n, &q);
	int i;
	for (i = 0 ; i < q; i++) {
	    int v1, v2;
	    scanf("%d%d%s", &v1, &v2, st);
	    if (st[0] == 'U') {
	        op[i][2] = 1;
	    } else {
	        op[i][2] = 2;
	    }
	    tmp1[i] = op[i][0] = v1;
	    tmp2[i] = op[i][1] = v2;
	}
	
	sort(tmp1, tmp1 + q);
	sort(tmp2, tmp2 + q);
	for (i = 0 ; i < q; i++) {
	    if (i == 0 || tmp1[i] != tmp1[i-1]) {
	        disc1.push_back(tmp1[i]);
	    }
	    
	    if (i == 0 || tmp2[i] != tmp2[i-1]) {
	        disc2.push_back(tmp2[i]);
	    }
	}
	int sz1 = disc1.size(), sz2 = disc2.size();
	build(col, 0, sz1 - 1, 1);
	build(row, 0, sz2 - 1, 1);
	
	for (i = 0 ; i < q; i++) {
	    if (op[i][2] == 1) {
	        // eat in the col
	        int index = lower_bound(disc1.begin(), disc1.end(), op[i][0]) - disc1.begin();
	        int ans = 1 + op[i][1] - query(col, index, 0, sz1 - 1, 1);
	        printf("%d\n", ans);
	        int r = lower_bound(disc2.begin(), disc2.end(), op[i][1]) - disc2.begin();
	        int l = lower_bound(disc2.begin(), disc2.end(), op[i][1] - ans + 1) - disc2.begin();
	        update(col, index, index, 0, sz1 - 1, 1, op[i][1] + 1);
	        update(row, l, r, 0, sz2 - 1, 1, op[i][0] + 1);
	        
	    } else {
	        // eat in the row
	        int index = lower_bound(disc2.begin(), disc2.end(), op[i][1]) - disc2.begin();
	        int ans = 1 + op[i][0] - query(row, index, 0, sz2 - 1, 1);
	        printf("%d\n", ans);
	        int r = lower_bound(disc1.begin(), disc1.end(), op[i][0]) - disc1.begin();
	        int l = lower_bound(disc1.begin(), disc1.end(), op[i][0] - ans + 1) - disc1.begin();
	        update(row, index, index, 0, sz2 - 1, 1, op[i][0] + 1);
	        update(col, l, r, 0, sz1 - 1, 1, op[i][1] + 1);
	    }
	}
	
	return 0;
}
