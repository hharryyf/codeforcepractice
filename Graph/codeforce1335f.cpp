#include <bits/stdc++.h>
#define MAX_SIZE 1000011
using namespace std;
// key and most most important observation, the graph is a functional
// graph !!!!
char st[MAX_SIZE];

int child[MAX_SIZE][25];
int color[MAX_SIZE];
int n, m;
pair<int, int> endcoord[MAX_SIZE];

int idx(int x, int y) {
    return x * m + y;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T > 0) {
        int i, j;
        scanf("%d%d", &n, &m);
        for (i = 0 ; i < n * m; ++i) {
            for (j = 0 ; j < 25; ++j) {
                child[i][j] = 0;
            }
        }

        for (i = 0 ; i < n; ++i) {
            scanf("%s", st);
            for (j = 0 ; j < m; ++j) {
                color[idx(i, j)] = st[j] - '0';
            }
        }

        for (i = 0 ; i < n; ++i) {
            scanf("%s", st);
            for (j = 0 ; j < m; ++j) {
                if (st[j] == 'U') {
                    child[idx(i, j)][0] = idx(i-1, j);
                } else if (st[j] == 'D') {
                    child[idx(i, j)][0] = idx(i+1, j);
                } else if (st[j] == 'L') {
                    child[idx(i, j)][0] = idx(i, j - 1);
                } else {
                    child[idx(i, j)][0] = idx(i, j + 1);
                }
            }
        }

        for (j = 1 ; j < 25; ++j) {
            for (i = 0 ; i < n * m; ++i) {
                child[i][j] = child[child[i][j-1]][j-1];
            }
        }

        set<int> all, black;
        // since after 1 << 24 moves all points are locked inside the cycle
        // component of each functional graph, no further collisions are possible
        for (i = 0 ; i < n * m; ++i) {
            all.insert(child[i][24]);
            if (color[i] == 0) {
                black.insert(child[i][24]);
            }
        } 

        printf("%d %d\n", (int) all.size(), (int) black.size());
        --T;
    }
    return 0;
}