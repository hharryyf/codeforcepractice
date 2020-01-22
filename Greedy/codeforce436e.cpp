#include <bits/stdc++.h>
#define MAX_SIZE 300011
typedef long long ll;
using namespace std;

vector<ll> disc;
struct BIT {
    ll tree[MAX_SIZE << 1][2];
    int n;
    
    int shift(int x) {
        return x & (-x);
    }
    
    void update(int index, ll cnt, ll w) {
        if (index <= 0) return;
        while (index <= n) {
            tree[index][0] += cnt;
            tree[index][1] += w;
            index += shift(index);
        }
    }
    
    pair<ll, ll> getans(int index) {
        ll v1 = 0, v2 = 0;
        while (index > 0) {
            v1 += tree[index][0], v2 += tree[index][1];
            index -= shift(index);
        }
        return make_pair(v1, v2);
    }
    
    int getindex(ll w) {
        int low = 0, high = n;
        int idx = n;
        while (low <= high) {
            int mid = low + ((high - low) >> 1);
            if (getans(mid).first >= w) {
                idx = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return idx;
    }
};

BIT tree;

struct level {
    ll a, b;
    int id;
    bool operator < (level other) const {
        return b < other.b;
    }
};

level arr[MAX_SIZE];
ll inc[MAX_SIZE];
ll tmp[MAX_SIZE << 1];
bool se1[MAX_SIZE], se2[MAX_SIZE];
bool visited[MAX_SIZE];

int main() {
    int i, n, j = 1;
    ll w;
    ll curr = 0, ans = 0, prefix = 0;
    scanf("%d%lld", &n, &w);
    for (i = 1; i <= n; i++) {
        scanf("%lld%lld", &arr[i].a, &arr[i].b);
        arr[i].id = i;
        tmp[j++] = arr[i].a;        
        tmp[j++]  = arr[i].b - arr[i].a;
        ans += arr[i].b;
    }
    
    sort(tmp + 1, tmp + 2 * n + 1);
    sort(arr + 1, arr + n + 1);
    
    disc.push_back(0);
    for (i = 1; i <= 2 * n; i++) {
        if (i == 1 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);                
    }
    
    tree.n = (int) disc.size();
    
    for (i = 1; i <= n; i++) {
        int index = lower_bound(disc.begin(), disc.end(), arr[i].a) - disc.begin();
        tree.update(index, 1, arr[i].a);
        inc[i] = arr[i].b - arr[i].a;
    }
    
    int findex = n;
    for (i = 0; i <= n; i++) {
        // w - i smallest number from inc[1:i] and arr[i+1:n].a
        int index = lower_bound(disc.begin(), disc.end(), inc[i]) - disc.begin();
        tree.update(index, 1, inc[i]);
        index = lower_bound(disc.begin(), disc.end(), arr[i].a) - disc.begin();
        tree.update(index, -1, -arr[i].a);
        prefix += arr[i].a;
        // answer is valid iff w - i <= n
        if (w - i <= n) {
            index = tree.getindex(w - i);
            auto p = tree.getans(index);
            curr = p.second - (p.first - (w - i)) * disc[index]; 
            if (curr + prefix < ans) {
                ans = curr + prefix;
                findex = i;
            }
        }
    }
    
    
    printf("%lld\n", ans);
    
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
    
    curr = 0;
    for (i = 1; i <= findex; i++) {
        curr++;
        q.push(make_pair(inc[i], arr[i].id));
        se1[arr[i].id] = true;
        visited[arr[i].id] = true;
    }
    
    for (i = findex + 1; i <= n; i++) {
        q.push(make_pair(arr[i].a, arr[i].id));
    }
    
    while (curr < w && !q.empty()) {
        int index = q.top().second;
        q.pop();
        if (visited[index]) {
            se1[index] = false;
            se2[index] = true;
        } else {
            se1[index] = true;
        }
        curr++;
    }
    
    for (i = 1; i <= n; i++) {
        if (se1[i]) {
            printf("1");
        } else if (se2[i]) {
            printf("2");
        } else {
            printf("0");
        }
    }
    
    printf("\n");
    return 0;
}
