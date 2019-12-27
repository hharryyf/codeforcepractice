#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 1048597
#define MAX_V 300011
typedef long long ll;
using namespace std;

/*
    This problem definitly very tricky, the first data structure
    problem I failed to solve after Buses and People.
    
    The main difficulty of the problem however, is not the data structure part,
    but the observation part. Firstly, we could see that for a given group
    there's a [L, R] acceptance bound which satisfy
    L = max(li) and R = min(ri), for all i within the group.
    Similarly, we have L <= vi <= R, which is max(li) <= vi <= min(ri)
    which is li <= L <= vi and vi <= R <= ri
    Hence, the problem could be reduced to the routine problem, find the point (L, R) 
    in the plane that has the maximum number of rectangle (li, vi, vi, ri) covered on it.
    A range tree and line sweep would easily work.
*/



vector<pair<int, int>> adding[MAX_V];
vector<pair<int, int>> removing[MAX_V];
struct segt {
    int value, lz;
};

segt tree[MAX_SIZE];

void pushdown(int l, int r, int index) {
    if (l > r) return;
    if (tree[index].lz) {
        if (l != r) {
            tree[index * 2].value += tree[index].lz;
            tree[index * 2].lz += tree[index].lz;
            tree[index * 2 + 1].value += tree[index].lz;
            tree[index * 2 + 1].lz += tree[index].lz;
        }
        tree[index].lz = 0;
    }
}
// return the (value, index) of the maximum value in the entire tree
pair<int, int> query(int l, int r, int index) {
    if (l > r) return make_pair(-1, -1);
    pushdown(l, r, index);
    if (l == r) return make_pair(tree[index].value, l);
    int mid = l + (r - l) / 2;
    if (tree[index * 2].value >= tree[index * 2 + 1].value) {
        return query(l, mid, index * 2);
    }
    return query(mid + 1, r, index * 2 + 1);
}

void update(int start, int end, int l, int r, int index, int val) {
    if (start > end || l > r) return;
    pushdown(l, r, index);
    if (start > r || l > end) return;
    if (start <= l && r <= end) {
        tree[index].value += val;
        tree[index].lz += val;
        return;
    }
    
    int mid = l + (r - l) / 2;
    if (end <= mid) {
        update(start, end, l, mid, index * 2, val);
    } else if (start >= mid + 1) {
        update(start, end, mid + 1, r, index * 2 + 1, val);
    } else {
        update(start, end, l, mid, index * 2, val);
        update(start, end, mid + 1, r, index * 2 + 1, val);
    }
    tree[index].value = max(tree[index * 2].value, tree[index * 2 + 1].value);
}

int L[MAX_V], R[MAX_V], V[MAX_V];

int main() {
	int n, i;
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
	    scanf("%d%d%d", &L[i], &V[i], &R[i]);
	    adding[V[i]].emplace_back(L[i], V[i]);
	    removing[R[i]].emplace_back(L[i], V[i]);
	}
	
	int maxx = 0, maxy = 0, maxp = 0;
	
	for (i = 1; i < MAX_V; i++) {
	    for (auto p : adding[i]) {
	        update(p.first, p.second, 1, MAX_V - 2, 1, 1);
	    }
	    
	    pair<int, int> q = query(1, MAX_V - 2, 1);
	    if (q.first >= maxp) {
	        maxp = q.first;
	        maxx = q.second;
	        maxy = i;
	    }
	    
	    for (auto p : removing[i]) {
	        update(p.first, p.second, 1, MAX_V - 2, 1, -1);
	    }
	}
	
	printf("%d\n", maxp);
	for (i = 1; i <= n; i++) {
	    if (L[i] <= maxx && maxx <= V[i] && V[i] <= maxy && maxy <= R[i]) {
	        printf("%d ", i);
	    }
	}
	printf("\n");
	return 0;
}

