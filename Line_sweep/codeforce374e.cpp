#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 2011
using namespace std;

struct point {
    int x, y;
};
// if the line is horizontal, it would be (x1, y), (x2, y)
// if it is vertical it would be (y, x1), (y, x2)
struct line {
    int x1, x2, y;
    bool operator < (line other) const {
        if (x2 != other.x2) return x2 > other.x2;
        if (x1 != other.x1) return x1 > other.x1;
        return y > other.y;
    }
};


point blue[MAX_SIZE], red[MAX_SIZE];
line hor[MAX_SIZE], ver[MAX_SIZE];
int n, m;

static bool cmp_1(const line &l1, const line &l2) {
    if (l1.y != l2.y) return l1.y < l2.y;
    if (l1.x1 != l2.x1) return l1.x1 < l2.x1;
    return l1.x2 < l2.x2;
}

static bool cmp_2(const line &l1, const line &l2) {
    return l1.x1 < l2.x1;
}

vector<line> removedup(line li[], int sz) {
    int i;
    vector<line> ret;
    for (i = 1; i <= sz; ++i) {
        if (i == 1) {
            ret.push_back(li[i]);
        } else {
            if (li[i].y != ret.back().y) {
                ret.push_back(li[i]);
            } else {
                if (ret.back().x2 < li[i].x1) {
                    ret.push_back(li[i]);
                } else {
                    int r = max(ret.back().x2, li[i].x2);
                    ret[ret.size() - 1].x2 = r;
                }
            }
        }
    }
    return ret;
}
bool valid(int T) {
    // the interval for blue segments would be
    // (x, y-2t), (x, y+2t)
    // red segments would be (x-2t, y), (x+2t, y)
    int i, j, sz1, sz2, k;
    for (i = 1; i <= n; ++i) {
        ver[i].x1 = blue[i].y - 2 * T;
        ver[i].x2 = blue[i].y + 2 * T;
        ver[i].y = blue[i].x;
    }

    for (i = 1; i <= m; ++i) {
        hor[i].x1 = red[i].x - 2 * T;
        hor[i].x2 = red[i].x + 2 * T;
        hor[i].y = red[i].y;
    }

    sort(ver + 1, ver + 1 + n, cmp_1);
    sort(hor + 1, hor + 1 + m, cmp_1);

    vector<line> hr = removedup(hor, m);
    vector<line> vc = removedup(ver, n);
    sz1 = hr.size(), sz2 = vc.size();
    sort(vc.begin(), vc.end(), cmp_2);

    for (i = 0; i < sz1; ++i) {
        priority_queue<line> s1;
        multiset<int> xcoord;
        k = 0;
        while (k < sz2 && vc[k].x1 <= hr[i].y ) {
            if (vc[k].x2 > hr[i].y) {
                s1.push(vc[k]);
                xcoord.insert(vc[k].y);
            }
            k++;
        }

        for (j = i + 1; j < sz1; ++j) {
            while (!s1.empty()) {
                auto iter = s1.top();
                if (iter.x2 < hr[j].y) {
                    xcoord.erase(xcoord.find(iter.y));
                    s1.pop();
                } else {
                    break;
                }
            }

            int l = max(hr[i].x1, hr[j].x1), r = min(hr[i].x2, hr[j].x2);
            if (l < r && !xcoord.empty()) {
                auto it1 = xcoord.lower_bound(l);
                auto it2 = xcoord.upper_bound(r);
                if (it2 != xcoord.begin() && it1 != xcoord.end()) {
                    it2 = prev(it2);
                    if (*it1 != *it2 && *it1 >= l && *it1 <= r && *it2 >= l && *it2 <= r) return true;
                }
            }
        }
    }
    return false;
}

int main() {
    int i;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        blue[i].x = x + y, blue[i].y = x - y;
    }

    for (i = 1; i <= m; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        red[i].x = x + y, red[i].y = x - y;
    }

    int ans = -1, low = 1, high = 500100;
    while (low <= high) {
        int mid = (low + high) >> 1;
        if (valid(mid)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    if (ans != -1) {
        printf("%d\n", ans);
    } else {
        printf("Poor Sereja!\n");
    }
    return 0;
}
