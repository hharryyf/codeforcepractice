#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 300011
typedef long long ll;
using namespace std;

struct circle {
    int x, y, r;
};


circle cir[1511];

struct line {
    // y = a/b * x + c/b
    // if b = 0, we would record as (x, 0, 1)
    // if a = 0, we would record as (0, y, -1)
    // if k < 0, we would record a as negative
    int a, b, c;
    bool operator < (line other) const {
        if (a != other.a) return a < other.a;
        if (b != other.b) return b < other.b;
        return c < other.c;
    }
};

ll ans;
map<line, vector<int>> Left;
map<line, vector<int>> Right;
// insert a line into the left and right set
void insert(int x1, int y1, int x2, int y2) {
    if (x1 > x2 || (x1 == x2 && y1 > y2)) {
        swap(x1, x2);
        swap(y1, y2);
    }

    int A = y2 - y1, B = x2 - x1, d;
    if (B == 0) {
        // insert as (line{x1, 0, 0})
        Left[line{x1, 0, 1}].push_back(y1);
        Right[line{x2, 0, 1}].push_back(y2);
        return;
    }

    if (A == 0) {
        Left[line{0, y1, -1}].push_back(x1);
        Right[line{0, y1, -1}].push_back(x2);
        return;
    }


    if (A < 0) {
        d = __gcd(-A, B);
    } else {
        d = __gcd(A, B);
    }

    int C = B * y1 - A * x1;
    A /= d, B /= d, C /= d;
    // cout << A << " " << B << ", " << C << endl;
    Left[line{A, B, C}].push_back(x1);
    Right[line{A, B, C}].push_back(x2);
}   

void preprocess() {
    for (auto &e : Left) {
        sort(e.second.begin(), e.second.end());
    }

    for (auto &e : Right) {
        sort(e.second.begin(), e.second.end());
    }
}

// return the number of lines that are prependicular to 
// the segment x1, y1, x2, y2 and there is an intersection point
int query(int x1, int y1, int x2, int y2) {
    if (x1 > x2 || (x1 == x2 && y1 > y2)) {
        swap(x1, x2);
        swap(y1, y2);
    }

    int midx = x1 + (x2 - x1) / 2, midy = y1 + (y2 - y1) / 2;
    // the query line is vertical
    if (x1 == x2) {
        // we get a horizontal line with y = midy
        auto iter = Left.find(line{0, midy, -1});
        if (iter == Left.end()) return 0;
        int sz1 = upper_bound(iter->second.begin(), iter->second.end(), x1) - iter->second.begin();
        iter = Right.find(line{0, midy, -1});
        int sz2 = lower_bound(iter->second.begin(), iter->second.end(), x1) - iter->second.begin();
        return sz1 - sz2;
    }

    if (y1 == y2) {
        auto iter = Left.find(line{midx, 0, 1});
        if (iter == Left.end()) return 0;
        int sz1 = upper_bound(iter->second.begin(), iter->second.end(), y1) - iter->second.begin();
        iter = Right.find(line{midx, 0, 1});
        int sz2 = lower_bound(iter->second.begin(), iter->second.end(), y1) - iter->second.begin();
        return sz1 - sz2;
    }

    int A = x2 - x1, B = y1 - y2, C = midy * B - midx * A;
    if (B < 0) {
        B *= -1, A *= -1, C *= -1;
    }

    int d;
    if (A < 0) {
        d = __gcd(-A, B);
    } else {
        d = __gcd(A, B);
    }

    A /= d, B /= d, C /= d;
    // cout << A << " " << B << " " << C << endl;
    auto iter = Left.find(line{A, B, C});
    if (iter == Left.end()) return 0;
    int sz1 = upper_bound(iter->second.begin(), iter->second.end(), midx) - iter->second.begin();
    //cout << "query " << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
    /*
    for (auto v : iter->second) {
        cout << v << " ";
    }
    cout << endl;*/
    iter = Right.find(line{A, B, C});
    int sz2 = lower_bound(iter->second.begin(), iter->second.end(), midx) - iter->second.begin();
    /*for (auto v : iter->second) {
        cout << v << " ";
    }
    cout << endl;
    cout << sz1 << " and " << sz2 << endl;*/
    return sz1 - sz2;
}

int main() {
    int i, m, n, j;
    scanf("%d%d", &m, &n);
    for (i = 1; i <= m; ++i) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        x1 *= 2, y1 *= 2, x2 *= 2, y2 *= 2;
        insert(x1, y1, x2, y2);
    }

    for (i = 1; i <= n; ++i) {
        scanf("%d%d%d", &cir[i].x, &cir[i].y, &cir[i].r);
        cir[i].x *= 2, cir[i].y *= 2, cir[i].r *= 2;
    }

    preprocess();

    for (i = 1; i <= n; ++i) {
        for (j = i + 1; j <= n; ++j) {
            if (cir[i].r != cir[j].r) continue;
            // the order is very important to avoid overflow!
            if ((cir[i].x - cir[j].x) * (cir[i].x - cir[j].x) <= 4 * cir[i].r * cir[i].r - (cir[i].y - cir[j].y) * (cir[i].y - cir[j].y)) continue;
            ans += query(cir[i].x, cir[i].y, cir[j].x, cir[j].y);
        }
    }
    
    printf("%I64d\n", ans);
    return 0;
}