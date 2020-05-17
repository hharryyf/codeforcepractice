#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

int b[MAX_SIZE], c[MAX_SIZE];
vector<int> disc;
int tmp[MAX_SIZE], f[MAX_SIZE];
int n;

int find(int x) {
    // cout << x << endl;
    if (x == f[x]) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int aa = find(x), bb = find(y);
    f[aa] = bb;
}

void preprocess() {
    int i;
    for (i = 0 ; i < MAX_SIZE; ++i) f[i] = i;
}

multiset<int> g[MAX_SIZE];
vector<pair<int, int>> ret;

void euler(int v) {
    // cout << "enter" << endl;
    while (!g[v].empty()) {
        int nv = *g[v].begin();
        g[nv].erase(g[nv].find(v));
        g[v].erase(g[v].find(nv));
        euler(nv);
        ret.emplace_back(v, nv);
    }
}

int main() {
    int i, n, j = 0;
    scanf("%d", &n);
    preprocess();
    for (i = 0; i < n-1; ++i) {
        scanf("%d", &b[i]);
        tmp[j++] = b[i];
    }

    for (i = 0 ; i < n-1; ++i) {
        scanf("%d", &c[i]);
        tmp[j++] = c[i];
    }

    for (i = 0 ; i < n-1; ++i) {
        if (b[i] > c[i]) {
            printf("-1\n");
            return 0;
        }
    }

    sort(tmp, tmp + j);

    for (i = 0 ; i < j; ++i) {
        if (i == 0 || tmp[i] != tmp[i-1]) {
            disc.push_back(tmp[i]);
        }
    }

    for (i = 0 ; i < n-1; ++i) {
        int idx1 = lower_bound(disc.begin(), disc.end(), b[i]) - disc.begin();
        int idx2 = lower_bound(disc.begin(), disc.end(), c[i]) - disc.begin();
        // add code here to add edges
        g[idx1].insert(idx2);
        g[idx2].insert(idx1);
        unionset(idx1, idx2);
    }

    int sz = disc.size();

    int x = find(0);

    for (i = 1; i < sz; ++i) {
        if (find(i) != x) {
            printf("-1\n");
            return 0;
        }
    }

    int start = 0;
    x = 0;
    for (i = 0 ; i < sz; ++i) {
        if ((int) g[i].size() % 2 == 1) {
            ++x;
            start = i;
        }
    }

    if (x > 2) {
        printf("-1\n");
        return 0;
    }
    // cout << "start= " << disc[start] << endl;
    euler(start);
    reverse(ret.begin(), ret.end());
    for (i = 0 ; i < (int) ret.size(); ++i) {
        if (i == 0) {
            printf("%d ", disc[ret[i].first]);
        }
        printf("%d ", disc[ret[i].second]);
    }
    printf("\n");
    return 0;
}