#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 2000011
using namespace std;

int day[MAX_SIZE >> 1][2];
int f[MAX_SIZE];
int sz[MAX_SIZE];
int tmp[MAX_SIZE];
vector<int> g[MAX_SIZE];
vector<int> disc;

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int a = find(x), b = find(y);
    if (a == b) {
        sz[a]++;
    } else {
        f[a] = b;
        sz[b] += sz[a] + 1;
    }
}

int main() {
    int n, i;
    scanf("%d", &n);
    
    for (i = 0 ; i < MAX_SIZE; ++i) f[i] = i, sz[i] = 0;

    for (i = 0 ; i < n; ++i) {
        scanf("%d%d", &day[i][0], &day[i][1]);
        tmp[i * 2] = day[i][0];
        tmp[i * 2 + 1] = day[i][1];
    }

    sort(tmp, tmp + 2 * n);

    for (i = 0 ; i < 2 * n; ++i) {
        if (i == 0 || tmp[i] != tmp[i-1]) {
            disc.push_back(tmp[i]);
        }
    }

    for (i = 0 ; i < n; ++i) {
        int id1 = lower_bound(disc.begin(), disc.end(), day[i][0]) - disc.begin();
        int id2 = lower_bound(disc.begin(), disc.end(), day[i][1]) - disc.begin();
        unionset(id1, id2);
    }

    int si = disc.size();
    for (i = 0 ; i < si; ++i) {
        g[find(i)].push_back(i);
    }

    int ans = 0;
    for (i = 0 ; i < si; ++i) {
        if (find(i) == i) {
            if (sz[i] == (int) g[i].size() - 1) {
                ans = max(ans, disc[g[i][g[i].size() - 2]]);
            } else if (sz[i] == (int) g[i].size()){
                ans = max(ans, disc[g[i].back()]);
            } else {
                printf("-1\n");
                return 0;
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}