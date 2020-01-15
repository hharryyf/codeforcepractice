#include <bits/stdc++.h>
#define MAX_SIZE 100111
typedef long long ll;
using namespace std;

struct points {
    ll x, y;
    bool operator < (points other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

ll yminl[MAX_SIZE], ymaxl[MAX_SIZE], yminh[MAX_SIZE], ymaxh[MAX_SIZE]; 

points pt[MAX_SIZE];

int n;

bool valid(ll r) {
    int i, j;
    for (i = 0, j = 0; i < n; i++) {
        while (j < n && pt[j].x <= pt[i].x + r) {
            j++;
        }
        
        if (i == 0 && j == n) return true;
        if (i != 0 && j != n) {
            ll mx = max(ymaxl[i-1], ymaxh[j]);
            ll mn = min(yminl[i-1], yminh[j]);
            if (mx - mn <= r) return true;
        }
        
        if (i != 0 && j == n && ymaxl[i-1] - yminl[i-1] <= r) return true;
        if (i == 0 && j != n && ymaxh[j] - yminh[j] <= r) return true;
        
    }
    return false;
}

int main() {
    scanf("%d", &n);
    int i;
    for (i = 0 ; i < n; i++) {
        ll x, y;
        scanf("%lld%lld", &x, &y);
        pt[i].x = x + y, pt[i].y = y - x;
    }
    
    sort(pt, pt + n);
    
    for (i = 0 ; i < n; i++) {
        if (i == 0) {
            yminl[i] = ymaxl[i] = pt[i].y;
        } else {
            yminl[i] = min(yminl[i-1], pt[i].y);
            ymaxl[i] = max(ymaxl[i-1], pt[i].y);
        }
    }
    
    for (i = n - 1; i >= 0; i--) {
        if (i == n - 1) {
            yminh[i] = ymaxh[i] = pt[i].y;
        } else {
            yminh[i] = min(yminh[i+1], pt[i].y);
            ymaxh[i] = max(ymaxh[i+1], pt[i].y);
        }
    }
    
    ll low = 0, high = 4000000000ll;
    ll ans = high;
    while (low <= high) {
        ll mid = low + (high - low) / 2;
        if (valid(mid)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    printf("%.15lf\n", (ans * 1.0) / 2.0);
    return 0;
}
