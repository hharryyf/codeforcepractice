#include <bits/stdc++.h>

using namespace std;
// deg1 vertices
vector<int> deg1;
// all the non-deg 1 vertex and there degree
vector<int> deg;
int a[512];
vector<int> g[512];

int main() {
    int n, i, j, cnt = 0;
    int d = 0;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        int v;
        scanf("%d", &v);
        if (v == 1) {
            deg1.push_back(i);
        } else {
            deg.push_back(i);
        }
        a[i] = v;
    }

    if (deg.empty()) {
        printf("NO\n");
        return 0;
    }

    for (i = 0 ; i < (int) deg.size() - 1; ++i) {
        g[deg[i]].push_back(deg[i+1]);
        ++cnt;
        a[deg[i]]--, a[deg[i+1]]--;
    }

    if (deg1.size() == 0) {
        d = (int) deg.size() - 1;
    } else if (deg1.size() == 1) {
        d = (int) deg.size();
        g[deg1.back()].push_back(deg.back());
        a[deg1.back()]--, a[deg.back()]--;
        deg1.pop_back();
        ++cnt;
    } else {
        d = (int) deg.size() + 1;
        g[deg.back()].push_back(deg1.back());
        a[deg1.back()]--, a[deg.back()]--;
        deg1.pop_back();
        g[deg.front()].push_back(deg1.back());
        a[deg1.back()]--, a[deg.front()]--;
        deg1.pop_back();
        ++cnt, ++cnt;
    }

    for (i = 0, j = 0; i < (int) deg.size(); ++i) {
        while (j < (int) deg1.size() && a[deg[i]] > 0) {
            g[deg1[j]].push_back(deg[i]);
            a[deg[i]]--, a[deg1[j]]--;
            ++cnt;
            ++j;
        }
    }

    if (j != (int) deg1.size()) {
        printf("NO\n");
        return 0;
    }

    printf("YES %d\n%d\n", d, cnt);
    for (i = 1; i <= n; ++i) {
        for (auto v : g[i]) {
            printf("%d %d\n", i, v);
        }
    } 
    return 0;
}