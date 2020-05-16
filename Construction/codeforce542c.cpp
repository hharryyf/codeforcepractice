#include <bits/stdc++.h>
#define MAX_SIZE 211
typedef long long ll;
using namespace std;

int f[MAX_SIZE];
int cycle[MAX_SIZE];
int link[MAX_SIZE];
int visited[MAX_SIZE];

ll LCA(ll a, ll b) {
    ll c = __gcd(a, b);
    return a / c * b;
}

int main() {
    int n, i, j, k = 1;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) scanf("%d", &f[i]);
    for (i = 1; i <= n; ++i) {
        k = 1;
        memset(visited, 0, sizeof(visited));
        visited[i] = k++;
        j = f[i];
        while (visited[j] == 0) {
            visited[j] = k++;
            j = f[j];
        }

        // here visited[j] is not zero, next visited would be k
        cycle[i] = k - visited[j];
        link[i] = visited[j] - 1;
    }

    ll ans = 1;
    int maxlink = *max_element(link + 1, link + n + 1);
    for (i = 1; i <= n; ++i) {
        ans = LCA(ans, cycle[i]);
        // cout << "cycle= " << cycle[i] << " link= " << link[i] << endl;
    }
    if (maxlink == 0) {
        cout << ans << endl;
    } else {
        cout << ans * ((maxlink - 1) / ans + 1) << endl;
    }
    return 0;
}