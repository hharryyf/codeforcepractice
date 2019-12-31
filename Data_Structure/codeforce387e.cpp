#pragma GCC optimize(2)
#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 1000011
using namespace std;

int a[MAX_SIZE];
int visited[MAX_SIZE];
int table[20][MAX_SIZE];
int logs[MAX_SIZE];
int n, k;
ll tree[MAX_SIZE];
int mp[MAX_SIZE];
vector<int> qrs;

int shift(int x) {
    return x & (-x);
}

ll getans(int index) {
    ll ret = 0;
    while (index > 0) {
        ret += tree[index];
        index = index - shift(index);
    }
    return ret;
}

void update(int index, int val) {
    while (index <= n) {
        tree[index] += val;
        index = index + shift(index);
    }
}

ll query(int start, int end) {
    if (start > end) return 0;
    return getans(end) - getans(start - 1);
}

void change(int index, int val) {
    ll v = query(index, index);
    update(index, val - v);
}

void precompute() {
    int i;
    for (i = 2; i < MAX_SIZE; i++) {
        logs[i] = logs[i/2] + 1;
    }
}

int RMQ(int l, int r) {
    if (l > r) return 4 * MAX_SIZE;
    int len = r - l + 1;
    return min(table[logs[len]][l], table[logs[len]][r - (1 << logs[len]) + 1]);
}

void build() {
    int i, j;
    for (i = 1; i <= n; i++) {
        if (!visited[i]) {
            table[0][i] = 4 * MAX_SIZE;
        } else {
            table[0][i] = a[i];
        }
    }
    
    for (i = 1; i <= 19; i++) {
        int prel = (1 << (i - 1));
        for (j = 1; j <= n; j++) {
            if (j + prel <= n) {
                table[i][j] = min(table[i-1][j], table[i-1][j+prel]);
            } else {
                table[i][j] = table[i-1][j];
            }
        }
    }
}
// get the smallest idx > index such that the value
// is less than a[index]
int getright(int index) {
    int ret = n + 1;
    int l = index + 1, r = n;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (RMQ(index + 1, mid) < a[index]) {
            ret = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ret;
}

int getleft(int index) {
    int ret = 0;
    int l = 1, r = index - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (RMQ(mid, index - 1) < a[index]) {
            ret = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return ret;
}

int main() {
    ll ans = 0;
    precompute();
    scanf("%d%d", &n, &k);
    int i;
    for (i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        mp[a[i]] = i;
        change(i, 1);
    }
    
    for (i = 1; i <= k; i++) {
        int v;
        scanf("%d", &v);
        visited[mp[v]] = 1;
    }
    
    for (i = 1; i <= n; i++) {
        if (!visited[i]) {
        	qrs.push_back(a[i]);
        }
    }
    
    sort(qrs.begin(), qrs.end());
    
    build();
    
    vector<int> :: iterator iter = qrs.begin();
    while (iter != qrs.end()) {
        int R = getright(mp[*iter]), L =  getleft(mp[*iter]);
        ans += query(L + 1, R - 1);
        change(mp[*iter], 0);
        iter++;
    }
    printf("%lld\n", ans);
    return 0;
}
