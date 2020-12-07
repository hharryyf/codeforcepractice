#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 1011
using namespace std;
int a[MAX_SIZE][MAX_SIZE];
int dist[MAX_SIZE * MAX_SIZE][41];
vector<int> chunk[41];
const int inf = 1000000;
int N, M, K;

int idx(int x, int y) {
    return (x - 1) * M + y;
}

int main() {
    int i, j, k;
    scanf("%d%d%d", &N, &M, &K);
    int tol = N * M;
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= M; ++j) {
            scanf("%d", &a[i][j]);
            chunk[a[i][j]].push_back(idx(i, j));
            for (k = 1; k <= K; ++k) {
                dist[idx(i, j)][k] = inf;
            }
        }
    }    

    for (i = 1; i <= K; ++i) {
        for (j = 1; j <= K; ++j) {
            dist[tol + 2 * j - 1][i] = inf;
            dist[tol + 2 * j][i] = inf;
        }
    }

    for (k = 1; k <= K; ++k) {
        deque<int> q;
        for (auto v : chunk[k]) {
            dist[v][k] = 0;
            q.push_back(v);
        }
        
        dist[tol + 2 * k - 1][k] = 0;
        dist[tol + 2 * k][k] = 0;
        q.push_back(tol + 2 * k - 1);
        q.push_back(tol + 2 * k);
        while (!q.empty()) {
            int v = q.front();
            q.pop_front();
            if (v > tol) {
                int dif = v - tol;
                if (dif % 2 == 1) {
                    if (dist[v][k] + 1 < dist[v + 1][k]) {
                        dist[v + 1][k] = dist[v][k] + 1;
                        q.push_back(v + 1);
                    }
                } else {
                    //cout << "current= " << k << endl;
                    //cout << "relax color " << dif / 2 << endl;
                    for (auto nv : chunk[dif / 2]) {
                        //cout << dist[v][v] << " > " << dist[nv][k] << endl;
                        if (dist[v][k] < dist[nv][k]) {
                            dist[nv][k] = dist[v][k];
                            q.push_front(nv);
                          //  if (dif == 14 && k == 1) {
                          //      cout << nv << " --> ";
                          //  }
                        }
                    }
                }
            } else {
                int x = (v - 1) / M + 1, y = (v - 1) % M + 1;
                if (x + 1 <= N && dist[idx(x+1, y)][k] > dist[idx(x, y)][k] + 1) {
                    dist[idx(x+1, y)][k] = dist[idx(x, y)][k] + 1;
                    q.push_back(idx(x+1, y));
                }

                if (x - 1 >= 1 && dist[idx(x-1, y)][k] > dist[idx(x, y)][k] + 1) {
                    dist[idx(x-1, y)][k] = dist[idx(x, y)][k] + 1;
                    q.push_back(idx(x-1, y));
                }

                if (y + 1 <= M && dist[idx(x, y + 1)][k] > dist[idx(x, y)][k] + 1) {
                    dist[idx(x, y+1)][k] = dist[idx(x, y)][k] + 1;
                    q.push_back(idx(x, y+1));
                }

                if (y - 1 >= 1 && dist[idx(x, y - 1)][k] > dist[idx(x, y)][k] + 1) {
                    dist[idx(x, y-1)][k] = dist[idx(x, y)][k] + 1;
                    q.push_back(idx(x, y-1));
                }

                if (dist[tol + 2 * a[x][y] - 1][k] > dist[idx(x, y)][k]) {
                    //cout << "x= " << x << " y= " << y << endl;
                    dist[tol + 2 * a[x][y] - 1][k] = dist[idx(x, y)][k];
                    //cout << "in queue color " << a[x][y] << endl;
                    q.push_front(tol + 2 * a[x][y] - 1);
                }
            }
        }
    }
    //cout << "#" << endl;
    //cout << dist[idx(N, M) + 1][1] << " " << dist[idx(N, M) + 2][1] << endl;
    //for (i = 1; i <= N; ++i) {
    //    for (j = 1; j <= M; ++j) {
    //        cout << dist[idx(i, j)][1] << " ";
    //    }
    //    cout << endl;
    //}

    int q;
    scanf("%d", &q);
    while (q-- > 0) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        int idx1 = idx(x1, y1), idx2 = idx(x2, y2);
        int ans = abs(x1 - x2) + abs(y1 - y2);
        for (i = 1; i <= K; ++i) {
            // cout << i << ": " << dist[idx1][i] + dist[idx2][i] + 1 << endl;
            ans = min(ans, dist[idx1][i] + dist[idx2][i] + 1);
        }

        printf("%d\n", ans);
    }
    return 0;
}