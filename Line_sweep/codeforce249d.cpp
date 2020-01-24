#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 262192
typedef double DB;
using namespace std;

int tree[MAX_SIZE];

void update(int pt, int l, int r, int index, int val) {
    if (pt < l || pt > r) return;
    if (l == r && pt == l) {
        tree[index] = max(tree[index], val);
        return;
    }
    
    int mid = l + (r - l) / 2;
    if (pt <= mid) {
        update(pt, l, mid, index * 2, val);
    } else {
        update(pt, mid + 1, r, index * 2 + 1, val);
    }
    tree[index] = max(tree[index * 2], tree[index * 2 + 1]);
}

int query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return -MAX_SIZE;
    if (start <= l && r <= end) return tree[index];
    int mid = l + (r - l) / 2;
    if (end <= mid) {
        return query(start, end, l, mid, index * 2);
    } else if (start >= mid + 1) {
        return query(start, end, mid + 1, r, index * 2 + 1);
    }
    return max(query(start, end, l, mid, index * 2), 
               query(start, end, mid + 1, r, index * 2 + 1));
}

int n;
DB a, b, c, d;
struct pt {
    DB x, y;
    DB ab, cd;
};

pt p[MAX_SIZE << 1];
vector<DB> disc;
DB tmp[MAX_SIZE << 1];
static bool cmp_1(const pt &p1, const pt &p2) {
    if (p1.x != p2.x) return p1.x < p2.x;
    return p1.y < p2.y;
}

static bool cmp_2(const pt &p1, const pt &p2) {
    DB v1 = p1.y - a / b * p1.x ;
    DB v2 = p2.y - a / b * p2.x ;
    if (v1 != v2) return v1 < v2;
    return p1.x < p2.x;
}

DB getab(DB x, DB y) {
    return y - a / b * x;
}
// only can be called in solve_2
DB getcd(DB x, DB y) {
    return y - c / d * x;
}

void solve_1() {
    int ans = 0, i, j;
    for (i = 1; i <= n; i++) tmp[i] = p[i].ab;
    sort(tmp + 1, tmp + n + 1);
    for (i = 1; i <= n; i++) {
        if (i == 1 || tmp[i] != tmp[i-1]) {
            disc.push_back(tmp[i]);
        }
    }
    
    int m = disc.size();
    sort(p + 1, p + 1 + n, cmp_1);
    
    for (i = 1, j = 1; i <= n;) {
        vector<pair<int, int>> ret;
        while (j <= n && p[i].x == p[j].x) {
            int index = lower_bound(disc.begin(), disc.end(), p[j].ab) - disc.begin() - 1;
            ret.emplace_back(1 + query(0, index, 0, m - 1, 1), j);
            j++;
        }
        
        for (auto re : ret) {
            ans = max(ans, re.first);
            int index = lower_bound(disc.begin(), disc.end(), p[re.second].ab) - disc.begin();
            if (p[re.second].y > p[re.second].x / b * a) {
			   ans = max(ans, 1);
			   update(index, 0, m - 1, 1, 1);
			}
            update(index, 0, m - 1, 1, re.first);
        }
        
        i = j;
    }
    printf("%d\n", ans);
}

void solve_2() {
    int ans = 0, i, j;
    for (i = 1; i <= n; i++) tmp[i] = p[i].cd;
    sort(tmp + 1, tmp + n + 1);
    for (i = 1; i <= n; i++) {
        if (i == 1 || tmp[i] != tmp[i-1]) {
            disc.push_back(tmp[i]);
        }
    }
    
    int m = disc.size();
    sort(p + 1, p + 1 + n, cmp_2);
    
    for (i = 1, j = 1; i <= n;) {
        vector<pair<int, int>> ret;
        while (j <= n && p[j].ab == p[i].ab) {
            int r = lower_bound(disc.begin(), disc.end(), p[j].ab) - disc.begin() - 1;
            int l = upper_bound(disc.begin(), disc.end(), p[j].cd) - disc.begin();
            ret.emplace_back(1 + query(l, r, 0, m - 1, 1), j);
            j++;
        }
        
        for (auto re : ret) {
            ans = max(ans, re.first);
            int index = lower_bound(disc.begin(), disc.end(), p[re.second].cd) - disc.begin();
            if ((p[re.second].y > p[re.second].x / b * a) && (p[re.second].y < p[re.second].x  / d * c)) {
			   ans = max(ans, 1);
			   update(index, 0, m - 1, 1, 1);
			}
            update(index, 0, m - 1, 1, re.first);
        }
        
        i = j;
    }
    printf("%d\n", ans);
}

int main() {
    int i;
    scanf("%d", &n);
    scanf("%lf/%lf %lf/%lf", &a, &b, &c, &d);
    for (i = 1; i <= n; i++) {
        scanf("%lf%lf", &p[i].x, &p[i].y);
        p[i].ab = getab(p[i].x, p[i].y);
        if (d != 0) {
            p[i].cd = getcd(p[i].x, p[i].y);
        }
    }
    
    for (i = 1; i < MAX_SIZE; i++) tree[i] = -MAX_SIZE;
    
    if (d == 0) {
        solve_1();
    } else {
        solve_2();
    }
    return 0;
}
