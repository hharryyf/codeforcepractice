#include <bits/stdc++.h>
#define MAX_SIZE 524292
typedef long long ll;
using namespace std;

struct segt {
    ll minl, rsum;   
};

ll a, b, c, d, st;
ll len;
ll candidate[MAX_SIZE << 2];
vector<ll> t, rt;
segt tree[MAX_SIZE << 2];
int n, m = 0;
ll prefix[MAX_SIZE], psum[MAX_SIZE];

segt pullup(segt t1, segt t2) {
    segt tt;
    tt.rsum = t1.rsum + t2.rsum;
    tt.minl = min(t1.minl, t1.rsum + t2.minl);
    return tt;
}

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        if (rt[l] == 0) {
            tree[index].minl = tree[index].rsum = -d;
        } else {
            tree[index].minl = tree[index].rsum = c;
        }
        return;
    }
    
    int mid = l + (r - l) / 2;
    build(l, mid, index * 2);
    build(mid + 1, r, index * 2 + 1);
    tree[index] = pullup(tree[index * 2], tree[index * 2 + 1]);
}

segt query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return segt{0,0};
    if (start <= l && r <= end) return tree[index];
    int mid = l + (r - l) / 2;
    if (end <= mid) return query(start, end, l, mid, index * 2);
    if (start >= mid + 1) return query(start, end, mid + 1, r, index * 2 + 1);
    return pullup(query(start, end, l, mid, index * 2), 
                  query(start, end, mid + 1, r, index * 2 + 1));
}

pair<ll, ll> getprefix(ll curr) {
    if (curr <= t[0]) {
        return make_pair(0,0);
    }
    
    int index = lower_bound(t.begin(), t.end(), curr) - t.begin() - 1;
    return make_pair(prefix[index], psum[index]);
}

bool valid(int tm) {
    auto p = getprefix(tm);
    int l = lower_bound(t.begin(), t.end(), tm) - t.begin();
    int r = lower_bound(t.begin(), t.end(), tm + len) - t.begin() - 1;
    ll ret = query(l, r, 0, n - 1, 1).minl;
    return (st + p.second + ret >= 0) && (st + p.first >= 0);
}

int main() {
    int i;
    scanf("%d%lld%lld%lld%lld%lld%lld", &n, &a, &b, &c, &d, &st, &len);
    for (i = 0 ; i < n; i++) {
        int v1, v2;
        scanf("%lld%lld", &v1, &v2);
        t.push_back(v1), rt.push_back(v2);
        if (v2 == 0) {
            if (i == 0) {
                prefix[i] = psum[i] = -b;
            } else {
                psum[i] = psum[i-1] - b;
                prefix[i] = min(prefix[i-1], psum[i]);
            }
        } else {
            if (i == 0) {
                prefix[i] = psum[i] = a;
            } else {
                psum[i] = psum[i-1] + a;
                prefix[i] = min(prefix[i-1], psum[i]);
            }
        }
        
        candidate[m++] = v1;
        candidate[m++] = v1 + 1;
        if (v1 - len + 1 >= 0) {
            candidate[m++] = v1 - len + 1;
        }
        if (v1 - len >= 0) {
            candidate[m++] = v1 - len;
        }
    }
    
    candidate[m++] = 0;
    
    sort(candidate, candidate + m);
    build(0, n - 1, 1);
    
    for (i = 0 ; i < m; i++) {
        if (valid(candidate[i])) {
            printf("%lld\n", candidate[i]);
            return 0;
        }
    }
    
    printf("-1\n");
    return 0;
}
