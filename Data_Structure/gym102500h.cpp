#include <bits/stdc++.h>
#define MAX_SIZE 262192
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
typedef long long ll;
using namespace std;
const ll inf = 1e16;
ll tree[MAX_SIZE];
ll h[MAX_SIZE];
int N;

void update(int pt, int l, int r, int index, ll val) {
    if (pt < l || pt > r || l > r) return;
    if (l == r) {
        tree[index] = val;
        return;
    }

    if (pt <= MID) {
        update(pt, l, MID, LEFT, val);
    } else {
        update(pt, MID + 1, r, RIGHT, val);
    }
    tree[index] = min(tree[LEFT], tree[RIGHT]);
}

int query(int start, int end, int l, int r, int index, ll val) {
    if (start > end || l > r || start > r || l > end) return MAX_SIZE;
    if (tree[index] > val) return MAX_SIZE;
    if (l == r) return l;
    if (start <= l && r <= end) {
        if (tree[LEFT] <= val) return query(start, end, l, MID, LEFT, val);
        return query(start, end, MID + 1, r, RIGHT, val);
    }

    if (end <= MID) {
        return query(start, end, l, MID, LEFT, val);
    }

    if (start >= MID + 1) {
        return query(start, end, MID + 1, r, RIGHT, val);
    }

    return min(query(start, end, l, MID, LEFT, val), 
               query(start, end, MID + 1, r, RIGHT, val));
}

void init() {
    int i;
    for (i = 0 ; i < MAX_SIZE; ++i) tree[i] = inf;
}

void solve(int g) {
    init();
    int i;
    double ans = -1.0;
    for (i = 0; i <= N; ++i) {
        if (i == 0) {
            update(i, 0, N, 1, h[0] - 1ll * g * i);
            continue;
        } 

        int idx = query(0, i - 1, 0, N, 1, h[i] - 1ll * g * i);
        update(i, 0, N, 1, h[i] - 1ll * g * i);
        if (idx == MAX_SIZE) continue;
        double delta = 0.0;
        /*
            h[i] - h[idx] + delta * (h[idx - 1] - h[idx]) = g * (i - idx - delta)
            h[i] - h[idx] - g * i + g * idx = delta * (h[idx - 1] - h[idx] + g)
        */
        if (idx != 0) {
            delta = max(delta, 1.0 * (h[i] - h[idx] - 1.0 * g * i + 1.0 * g * idx) / (h[idx - 1] - h[idx] + g));
        }

        /*
            ((h[i+1] - h[i]) * delta + h[i] - h[idx]) / (i + delta - idx) >= g
            h[i+1] * delta - h[i] * delta + h[i] - h[idx] >= g * i + g * delta - g * idx
            (h[i+1] - h[i] - g) * delta >= h[idx] - h[i] + g * i - g * idx
            
        */
        if (i < N && h[i+1] - h[i] - g <= 0) {
            // cout << h[i+1] - h[i] - g << endl;
            // cout << "fuck" << endl;
            delta = max(delta, 1.0 * (1.0 * g * i - 1.0 * g * idx + h[idx] - h[i]) / (h[i+1] - h[i] - g));
        }

        delta = min(delta, 1.0);
        ans = max(ans, delta + i - idx);
    }

    if (ans <= 0.0) {
        printf("-1\n");
    } else {
        printf("%.9lf\n", ans);
    }
}

int main() {
    int i, K;
    scanf("%d%d", &N, &K);
    for (i = 0; i <= N; ++i) scanf("%I64d", &h[i]);
    while (K-- > 0) {
        double g;
        scanf("%lf", &g);
        solve(round(g * 10));
    }

    return 0;
}