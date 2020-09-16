#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 10000111
using namespace std;

int child[MAX_SIZE][2];
int cnt = 0;

void insert(vector<int> a) {
    int i = 0, n = a.size(), curr = 0;
    while (i < n) {
        if (child[curr][a[i]] != 0) {
            curr = child[curr][a[i]];
        } else {
            child[curr][a[i]] = ++cnt;
            curr = child[curr][a[i]];
        }
        ++i;
    }
}

int query(vector<int> a) {
    int curr = 0, i = 0, n = a.size();
    int ret = 0;
    while (i < n) {
        if (child[curr][a[i]] != 0) {
            curr = child[curr][a[i]];
            ret *= 2;
        } else {
            curr = child[curr][a[i] ^ 1];
            ret = ret * 2 + 1;
        }
        ++i;
    }

    return ret;
}

vector<int> gen(int x) {
    vector<int> ret = vector<int>(19, 0);
    int i = 18;
    while (x > 0) {
        ret[i] = x % 2;
        x /= 2;
        i--;
    }

    return ret;
}
int visited[524312];

int main() {
    int n, m, x = 0;
    scanf("%d%d", &n, &m);
    int i, v;
    for (i = 0 ; i < n; ++i) {
        scanf("%d", &v);
        visited[v] = 1;
    }

    for (i = 0; i < 524288; ++i) {
        if (!visited[i]) {
            insert(gen(i));
        }
    }

 // cout << full[0] << " " << sz[0] << endl;
    for (i = 0 ; i < m; ++i) {
        scanf("%d", &v);
        x ^= v;
        printf("%d\n", query(gen(x)));
    }

    return 0;
}