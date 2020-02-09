#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 200111
typedef long long ll;
using namespace std;

int f[MAX_SIZE], subsz[MAX_SIZE];
int lptype[MAX_SIZE];

int find(int x) {
    if (x == f[x]) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    if (x == y) {
        lptype[find(x)] = 2;
        return;
    }
    int a = find(x), b = find(y);
    if (a == b) {
        lptype[a] = 1;
        return;
    }
    
    subsz[a] += subsz[b];
    f[b] = a;
    lptype[a] += lptype[b];
}

int main() {
    int i, n;
    scanf("%d", &n);
    for (i = 1; i < MAX_SIZE; i++) f[i] = i, subsz[i] = 1;
    for (i = 1; i <= n; i++) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        unionset(v1, v2);
    }
    
    ll ans = 1;
    for (i = 1; i <= 2 * n; i++) {
        if (find(i) == i) {
            if (lptype[i] == 1) ans = (ans * 2) % MOD;
            else if (lptype[i] == 0) ans = (ans * subsz[i]) % MOD;
        }
    }
    cout << ans << endl;
    return 0;
}
