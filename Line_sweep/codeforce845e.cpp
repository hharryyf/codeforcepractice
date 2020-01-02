#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
#define MAX_SIZE 511

class intervalset {
public:
    intervalset(int r=0) {
        this->R = r;
        s.insert(make_pair(0,0));
        s.insert(make_pair(r + 1, r + 1));
    }
    
    pair<int, int> covered() {
        int r = this->L - 1;
        int l = this->R + 1;
        int saferight = 0;
        for (auto p : s) {
            //cout << p.first << " " << p.second << endl;
            if (p.first > saferight + 1) {
                l = min(saferight + 1, l);
                r = max(r, p.first - 1);
            }
            saferight = max(saferight, p.second);
        }
        //cout << "return " << l << " " << r << endl;
        return make_pair(l, r);
    }
    
    void insert(int l, int r) {
        s.insert(make_pair(l, r));
    }
    
    void del(int l, int r) {
        s.erase(s.find(make_pair(l, r)));
    }
    
private:
    int L = 1;
    int R;
    multiset<pair<int, int>> s;
};

int x[MAX_SIZE], y[MAX_SIZE];
int n, m, k;
intervalset ivt;

unordered_map<int, vector<pair<int, int>>> enter;
unordered_map<int, vector<pair<int, int>>> leave;
vector<int> ycoord;
vector<int> disc;


void addpoint(int pt) {
    if (pt > m) ycoord.push_back(m);
    else if (pt < 1) ycoord.push_back(1);
    else ycoord.push_back(pt);
}

bool valid(int t) {
    ivt = intervalset(n);
    int left = n + 1, right = 0, low = m + 1, high = 0;
    enter.clear(), leave.clear(), ycoord.clear(), disc.clear();
    int i;
    ycoord.push_back(1);
    ycoord.push_back(m);
    for (i = 1; i <= k; i++) {
        enter[max(1, y[i] - t)].emplace_back(max(x[i] - t, 1), min(x[i] + t, n));
        leave[min(m, y[i] + t)].emplace_back(max(x[i] - t, 1), min(x[i] + t, n));
        addpoint(y[i] - t - 1);
        addpoint(y[i] - t);
        addpoint(y[i] - t + 1);
        addpoint(y[i] + t - 1);
        addpoint(y[i] + t);
        addpoint(y[i] + t + 1);
    }
    
    sort(ycoord.begin(), ycoord.end());
    
    for (i = 0 ; i < (int) ycoord.size(); i++) {
        if (i == 0 || ycoord[i] != ycoord[i-1]) disc.push_back(ycoord[i]);
    }
    
    for (i = 0; i < (int) disc.size(); i++) {
        for (auto p : enter[disc[i]]) {
            ivt.insert(p.first, p.second);
        }
        
        auto pp = ivt.covered();
        if (pp.first != n + 1) {
            low = min(low, disc[i]);
            high = max(high, disc[i]);
            left = min(left, pp.first);
            right = max(right, pp.second);
        }
        for (auto p : leave[disc[i]]) {
            ivt.del(p.first, p.second);
        }
    }
    
    return max(right - left, high - low) <= 2 * t;
}

int main() {
    int i;
    scanf("%d%d%d", &n, &m, &k);
    for (i = 1; i <= k; i++) {
        scanf("%d%d", &x[i], &y[i]);
    }
    int l = 0, r = max(n, m);
    int ans = max(n, m);
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (valid(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    printf("%d\n", ans);
    return 0;
}
