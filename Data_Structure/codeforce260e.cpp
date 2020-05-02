#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 262192
#define MID ((l+r)>>1)
using namespace std;

struct segt {
    int left, right, value;
};

int cnt = 0;
vector<int> dx, dy;
vector<int> disc;
int root[MAX_SIZE];
pair<int, int> pt[MAX_SIZE];
segt tree[MAX_SIZE * 30];
int a[10];
int n;

int build(int l, int r) {
    if (l > r) return 0;
    int curr = ++cnt;
    if (l == r) return curr;
    tree[curr].left = build(l, MID);
    tree[curr].right = build(MID + 1, r);
    return curr;
}

int update(int rt, int pos, int l, int r) {
    if (pos < l || pos > r || l > r || rt == 0) return rt;
    int curr = ++cnt;
    tree[curr] = tree[rt];
    if (pos == l && l == r) {
        tree[curr].value++;
        return curr;
    }

    if (pos <= MID) {
        tree[curr].left = update(tree[rt].left, pos, l, MID);
    } else {
        tree[curr].right = update(tree[rt].right, pos, MID + 1, r);
    }
    tree[curr].value = tree[tree[curr].left].value + tree[tree[curr].right].value;
    return curr;
}

int query(int rt, int start, int end, int l, int r) {
    if (rt == 0 || start > end || l > r || start > r || l > end) return 0;
    if (start <= l && r <= end) return tree[rt].value;
    if (end <= MID) {
        return query(tree[rt].left, start, end, l, MID);
    } else if (start >= MID + 1) {
        return query(tree[rt].right, start, end, MID + 1, r);
    }

    return query(tree[rt].left, start, end, l, MID) + query(tree[rt].right, start, end, MID + 1, r);
}

int visited[10];
bool valid = false;
int ans[10];
double ret[4];

void check() {
    // check whether
    // a[ans[7]], a[ans[8]], a[ans[9]]
    // a[ans[4]], a[ans[5]], a[ans[6]]
    // a[ans[1]], a[ans[2]], a[ans[3]]
    // forms a valid cut
    int l1 = dx[a[ans[1]] + a[ans[4]] + a[ans[7]] - 1];
    int idx1 = upper_bound(dx.begin(), dx.end(), l1) - dx.begin();
    if (idx1 != a[ans[1]] + a[ans[4]] + a[ans[7]]) return;
    int l2 = dx[a[ans[1]] + a[ans[4]] + a[ans[7]] + a[ans[2]] + a[ans[5]] + a[ans[8]] - 1];
    int idx2 = upper_bound(dx.begin(), dx.end(), l2) - dx.begin();
    if (idx2 != a[ans[1]] + a[ans[4]] + a[ans[7]] + a[ans[2]] + a[ans[5]] + a[ans[8]]) return;
    int l3 = dy[a[ans[1]] + a[ans[2]] + a[ans[3]] - 1];
    int idx3 =  upper_bound(dy.begin(), dy.end(), l3) - dy.begin();
    if (idx3 != a[ans[1]] + a[ans[2]] + a[ans[3]]) return;
    int l4 = dy[a[ans[1]] + a[ans[2]] + a[ans[3]] + a[ans[4]] + a[ans[5]] + a[ans[6]] - 1];
    int idx4 = upper_bound(dy.begin(), dy.end(), l4) - dy.begin();
    if (idx4 != a[ans[1]] + a[ans[2]] + a[ans[3]] + a[ans[4]] + a[ans[5]] + a[ans[6]]) return;
    int L = upper_bound(disc.begin(), disc.end(), l3) - disc.begin();
    int R = upper_bound(disc.begin(), disc.end(), l4) - disc.begin();
    int q1 = query(root[idx1], 1, L, 1, n);
    int q2 = query(root[idx2], 1, L, 1, n) - q1;
    int q3 = query(root[idx1], 1, R, 1, n) - q1;
    int q4 = query(root[idx2], 1, R, 1, n) - q1 - q2 - q3;
    if (q1 != a[ans[1]] || q2 != a[ans[2]] || q3 != a[ans[4]] || q4 != a[ans[5]]) return;
    ret[0] = 0.1 + l1;
    ret[1] = 0.1 + l2;
    ret[2] = 0.1 + l3;
    ret[3] = 0.1 + l4;
    //for (int i = 1; i <= 9; ++i) cout << a[ans[i]] << " ";
    //cout << endl;
    valid = true;
}

void dfs(int idx) {
    int i;
    if (valid) return;
    if (idx > 9) {
        check();
        return;
    }
    for (i = 1; i <= 9; ++i) {
        if (!visited[i]) {
            ans[idx] = i;
            visited[i] = 1;
            dfs(idx + 1);
            visited[i] = 0;
        }
    }
}

int main() {
    int i;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d%d", &pt[i].first, &pt[i].second);
        dx.push_back(pt[i].first);
        dy.push_back(pt[i].second);
    }

    for (i = 1; i <= 9; ++i) scanf("%d", &a[i]);
    sort(pt + 1, pt + 1 + n);
    sort(dx.begin(), dx.end());
    sort(dy.begin(), dy.end());

    for (i = 0 ; i < (int) dy.size(); ++i) {
        if (i == 0 || dy[i] != dy[i-1]) disc.push_back(dy[i]);
    }

    root[0] = build(1, n);
    for (i = 1; i <= n; ++i) {
        int pos = lower_bound(disc.begin(), disc.end(), pt[i].second) - disc.begin() + 1;
        // increment pos at version i by 1
        root[i] = update(root[i-1], pos, 1, n);
    }

    dfs(1);

    if (!valid) {
        printf("-1\n");
        return 0;
    }
    printf("%.10lf %.10lf\n", ret[0], ret[1]);
    printf("%.10lf %.10lf\n", ret[2], ret[3]);
    return 0;
}