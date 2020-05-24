#include <bits/stdc++.h>
#define MAX_SIZE 1048597
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
#define MID ((l+r)>>1)
using namespace std;


struct segt {
    int lz, value;
};

segt tree[MAX_SIZE];
int p[MAX_SIZE];
int q[MAX_SIZE];
int n;

void pushdown(int l, int r, int index) {
    if (l > r) return;
    if (tree[index].lz != 0) {
        if (l != r) {
            tree[LEFT].lz += tree[index].lz;
            tree[RIGHT].lz += tree[index].lz;
            tree[LEFT].value += tree[index].lz;
            tree[RIGHT].value += tree[index].lz;
        }   
        tree[index].lz = 0;
    }
}

void update(int start, int end, int l, int r, int index, int val) {
    if (start > end || l > r || start > end || l > end) return;
    pushdown(l, r, index);
    if (start <= l && r <= end) {
        tree[index].lz += val;
        tree[index].value += val;
        return;
    }

    if (end <= MID) {
        update(start, end, l, MID, LEFT, val);
    } else if (start >= MID + 1) {
        update(start, end, MID + 1, r, RIGHT, val);
    } else {
        update(start, end, l, MID, LEFT, val);
        update(start, end, MID + 1, r, RIGHT, val);
    } 
    tree[index].value = max(tree[LEFT].value, tree[RIGHT].value);
}

/*
    key observation, the answer is non-increasing.
    Why? Because if v is the answer to the ith query, all v+1 to n
    can be removed by operations q[1:i]. A newly added removing operation
    cannot make the removed element active again.

    Hence, instead of thinking what elements are left in the set, we can check
    all v from n to 1. The trickest part comes, instead of thinking when the largest
    element is removed, we think when all elements greater than or equal to the largest
    element is removed.
*/
int main() {
    int i;
    scanf("%d", &n);
    vector<int> candidate;
    for (i = 1; i <= n; ++i) {
        int v;
        scanf("%d", &v);
        p[v] = i;
        candidate.push_back(i);
    }

    for (i = 1; i <= n; ++i) {
        scanf("%d", &q[i]);
    }
    // increase the protection by 1
    update(1, p[n], 1, n, 1, 1);
    for (i = 1; i <= n; ++i) {
        printf("%d ", candidate.back());
        update(1, q[i], 1, n, 1, -1);
        while (!candidate.empty()) {
            if (tree[1].value <= 0) {
                candidate.pop_back();
                if (!candidate.empty()) {
                    update(1, p[candidate.back()], 1, n, 1, 1);
                }
            } else {
                break;
            }
        }
    }    

    printf("\n");
    return 0;
}