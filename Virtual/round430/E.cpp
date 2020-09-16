#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 300111
using namespace std;

int N;
int depth[MAX_SIZE];
int parent[MAX_SIZE][19];

int LCA(int x, int y) {
    int i;
    if (depth[x] < depth[y]) swap(x, y);
    for (i = 18; i >= 0; --i) {
        if (depth[x] - (1 << i) >= depth[y]) {
            x = parent[x][i];
        }
    }

    if (x == y) return x;

    for (i = 18; i >= 0; --i) {
        if (parent[x][i] != parent[y][i]) {
            x = parent[x][i], y = parent[y][i];
        }
    }

    return parent[x][0];
}
// add a new point x into the tree, which parent is p
void update(int x, int p) {
    int i;
    parent[x][0] = p;
    for (i = 1; i < 19; ++i) parent[x][i] = parent[parent[x][i-1]][i-1];
    depth[x] = depth[p] + 1;
}

int dist(int x, int y) {
    return depth[x] + depth[y] - 2 * depth[LCA(x, y)];
}
// the left part of the diameter set, the right part of the diameter set
set<int> st1, st2;

int main() {
    int n, i, D = 0;
    scanf("%d", &n);
    st1.insert(1);
    for (i = 2; i <= n + 1; ++i) {
        int v;
        scanf("%d", &v);
        update(i, v);
       
        // check what happen if we insert v into the current set
        int d1 = st1.empty() ? 0 : dist(*st1.begin(), i), d2 = st2.empty() ? 0 : dist(*st2.begin(), i);
        if (max(d1, d2) > D) {
            if (max(d1, d2) == d1) {
                    for (auto u : st2) {
                        if (dist(u, i) == d1) {
                            st1.insert(u);
                        }
                    }
                    st2.clear();
                    st2.insert(i);
            } else {
                    for (auto u : st1) {
                        if (dist(u, i) == d2) {
                            st2.insert(u);
                        }
                    }
                    st1.clear();
                    st1.insert(i);
            }
            D = max(d1, d2);
        } else if (max(d1, d2) == D) {
                if (max(d1, d2) == d1) {
                    st2.insert(i);
                } else {
                    st1.insert(i);
                }
        }

        printf("%d\n", (int) st1.size() + st2.size());
    }
    return 0;
}

/*
16
1
2
3
1
1
6
2
6
1
5
3
5
7
5
13
16
17
18
11
12
2
17
14
18
22
17
17
27
1
5
30
4
10
22
30
34
31
4
5
23
12
9
30
35
18
43
23
28
36
37
48
3
23
3
16
13
1
25
27
51
48
45
37
2
25
21
18
63
62
26
19
12
60
22
73
38
66
1
66
45
52
33
68
67
64
25
26
84
83
66
71
7
23
19
42
84
27
26
23
85
4
94
7
78
24
31
81
60
92
51
2
65
34
112
35
6
115
75
3
104
41
19
35
124
120
113
2
59
90
53
85
90
*/