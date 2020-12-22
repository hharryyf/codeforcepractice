#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 2011
using namespace std;
int x[MAX_SIZE], y[MAX_SIZE];
map<pair<pair<int, int>, ll>, int> mp;
int N;

int main() {
    int i, j;
    long long ans = 0;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%d%d", &x[i], &y[i]);
        for (j = 1; j < i; ++j) {
            int dx = x[i] - x[j], dy = y[i] - y[j];
            ll dist = 1ll * dx * dx + 1ll * dy * dy;
            int g = __gcd(abs(dx), abs(dy));
            dx /= g, dy /= g;
            if (dx < 0) dx *= -1, dy *= -1;
            if (dy == 0) dx = 1;
            if (dx == 0) dy = 1;
            // ans = ans + mp[make_pair(make_pair(dx, dy), dist)];
            mp[make_pair(make_pair(dx, dy), dist)]++;
        }
    }

    for (auto iter : mp) {
        // cout << iter.first.first.first << " " << iter.first.first.second << " " << iter.first.second << endl;
        ans = ans + 1ll * (iter.second - 1) * iter.second / 2;
    }
    printf("%I64d\n", ans / 2);
    return 0;
}