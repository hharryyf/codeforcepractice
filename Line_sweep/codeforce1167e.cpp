#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 1048597
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
using namespace std;

int tree[MAX_SIZE << 1];
int L[MAX_SIZE], R[MAX_SIZE];
vector<int> add[MAX_SIZE];
int del = MAX_SIZE;
int N, X;
void update(int pt, int l, int r, int index) {
    if (pt < l || pt > r || l > r) return;
    if (l == r) {
        tree[index] = 1;
        return;
    }

    if (pt <= MID) {
        update(pt, l, MID, LEFT);
    } else {
        update(pt, MID + 1, r, RIGHT);
    }

    tree[index] = max(tree[LEFT], tree[RIGHT]);
}

int queryR(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return 0;
    if (tree[index] == 0) return 0;
    if (l == r) return l;
    if (start <= l && r <= end) {
        if (tree[RIGHT] == 1) return queryR(start, end, MID + 1, r, RIGHT);
        return queryR(start, end, l, MID, LEFT);
    }

    if (end <= MID) {
        return queryR(start, end, l, MID, LEFT);
    } else if (start >= MID + 1) {
        return queryR(start, end, MID + 1, r, RIGHT);
    } else {
        return max(queryR(start, end, l, MID, LEFT), queryR(start, end, MID + 1, r, RIGHT));
    }
}

int queryL(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return MAX_SIZE;
    if (tree[index] == 0) return MAX_SIZE;
    if (l == r) return l;
    if (start <= l && r <= end) {
        if (tree[LEFT] == 1) return queryL(start, end, l, MID, LEFT);
        return queryL(start, end, MID + 1, r, RIGHT);
    }

    if (end <= MID) {
        return queryL(start, end, l, MID, LEFT);
    } else if (start >= MID + 1) {
        return queryL(start, end, MID + 1, r, RIGHT);
    } else {
        return min(queryL(start, end, l, MID, LEFT), queryL(start, end, MID + 1, r, RIGHT));
    }
}

int main() {
    int i, mx = 0;
    set<int> st;
    scanf("%d%d", &N, &X);
    for (i = 1; i <= X; ++i) {
        L[i] = MAX_SIZE, R[i] = 0;
    }

    for (i = 1; i <= N; ++i) {
        int v;
        scanf("%d", &v);
        L[v] = min(queryL(v + 1, X, 1, X, 1), L[v]);
        R[v] = max(queryR(v + 1, X, 1, X, 1), R[v]);
        update(v, 1, X, 1);
    }

    for (i = 1; i <= X; ++i) {
        //cout << L[i] << " " << R[i] << endl;
        if (L[i] <= R[i]) {
            add[i].push_back(L[i]);
            add[i].push_back(R[i]);
            del = min(del, R[i]);
            del = min(del, L[i]);
            mx = max(mx, i);
        }
    }

    long long ans = 0;
    for (i = 1; i <= X; ++i) {
        if (mx != 0) {
            ans = ans + X - mx + 1;
            //cout << i << " -- " << *st.rbegin() << endl;
        } else {
            ans += X - i + 1;
            //cout << i << " " << i << endl;
        }

        if (!add[i].empty()) {
            for (auto v : add[i]) {
                mx = max(mx, v);
            }
        }

        if (del == i) break;
    }

    printf("%I64d\n", ans);
    return 0;
}