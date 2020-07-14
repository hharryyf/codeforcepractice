#include <bits/stdc++.h>
#define MAX_SIZE 524292
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
using namespace std;

struct event {
    int l, r, y, c, tp;
    bool operator < (event other) const {
        if (y != other.y) return y < other.y;
        return tp < other.tp;
    }
};

struct rectangle {
    int x1, x2, y1, y2;
};

rectangle rec[MAX_SIZE];
vector<event> evt;
set<int> st[MAX_SIZE];
int unmark[MAX_SIZE];
int mn[MAX_SIZE];
int mark[MAX_SIZE];
vector<int> disc;
vector<int> ycoord;
int tmp[MAX_SIZE];
int n;

void build(int l, int r, int index) {
    if (l > r) return;
    st[index].insert(0);
    unmark[index] = 0;
    mn[index] = 0;
    if (l == r) return;
    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
}

void pullup(int l, int r, int index) {
    if (l == r) {
        unmark[index] = mn[index] = *st[index].rbegin();
    } else {
        int val = *st[index].rbegin();
        mn[index] = max(val, min(mn[LEFT], mn[RIGHT]));
        unmark[index] = max(val, max(unmark[LEFT], unmark[RIGHT]));
    }

    if (unmark[index] != -1 && mark[unmark[index]]) unmark[index] = -1;
    if (unmark[index] != -1 && unmark[index] < mn[index]) unmark[index] = -1;
}

void update(int start, int end, int l, int r, int index, int val, int tp) {
    if (start > end || l > r || start > r || l > end) return;
    if (start <= l && r <= end) {
        if (tp == 1) {
            st[index].insert(val);
        } else if (tp == -1) {
            st[index].erase(val);
        }
        pullup(l, r, index);
        return;
    }

    if (end <= MID) {
        update(start, end, l, MID, LEFT, val, tp);
    } else if (start >= MID + 1) {
        update(start, end, MID + 1, r, RIGHT, val, tp);
    } else {
        update(start, end, l, MID, LEFT, val, tp);
        update(start, end, MID + 1, r, RIGHT, val, tp);
    }

    pullup(l, r, index);
}

int main() {
    int i, j;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d%d%d%d", &rec[i].x1, &rec[i].y1, &rec[i].x2, &rec[i].y2);
        tmp[i * 2 - 1] = rec[i].x1;
        tmp[i * 2] = rec[i].x2;
    }

    sort(tmp + 1, tmp + 1 + 2 * n);

    for (i = 1; i <= 2 * n; ++i) {
        if (i == 1 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
    }

    for (i = 1; i <= n; ++i) {
        tmp[i * 2 - 1] = rec[i].y1;
        tmp[i * 2] = rec[i].y2;
    }

    sort(tmp + 1, tmp + 1 + 2 * n);
    
    for (i = 1; i <= 2 * n; ++i) {
        if (i == 1 || tmp[i] != tmp[i-1]) ycoord.push_back(tmp[i]);
    }

    for (i = 1; i <= n; ++i) {
        event e;
        e.l = lower_bound(disc.begin(), disc.end(), rec[i].x1) - disc.begin();
        e.r = lower_bound(disc.begin(), disc.end(), rec[i].x2) - disc.begin() - 1;
        e.c = i;
        e.y = rec[i].y1;
        e.tp = 1;
        evt.push_back(e);
        e.y = rec[i].y2;
        e.tp = -1;
        evt.push_back(e);
    }

    build(0, (int) disc.size() - 2, 1);
    sort(evt.begin(), evt.end());
    int sz1 = ycoord.size(), sz2 = evt.size();
    for (i = 0, j = 0; i < sz1; ++i) {  
        while (j < sz2 && evt[j].y <= ycoord[i]) {
            update(evt[j].l, evt[j].r, 0, (int) disc.size() - 2, 1, evt[j].c, evt[j].tp);
            ++j;
        }

        while (unmark[1] > 0) {
            mark[unmark[1]] = 1;
            int L = lower_bound(disc.begin(), disc.end(), rec[unmark[1]].x1) - disc.begin();
            int R = lower_bound(disc.begin(), disc.end(), rec[unmark[1]].x2) - disc.begin() - 1;
            // cout << "delete " << unmark[1] << endl;
            update(L, R, 0, (int) disc.size() - 2, 1, unmark[1], 2);
        }
    }

    mark[0] = 1;
    int ans = 0;
    for (i = 0 ; i <= n; ++i) {
        ans += mark[i];
    }

    printf("%d\n", ans);
    return 0;
}