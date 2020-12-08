#include <bits/stdc++.h>
using namespace std;

const int inf = 1e8;

int d[10011];
int dist[10011][2011];
int N, M, G, R;

int main() {
    int i, j;
    scanf("%d%d", &N, &M);
    for (i = 0; i < M; ++i) scanf("%d", &d[i]);
    sort(d, d + M);
    scanf("%d%d", &G, &R);
    for (i = 0 ; i <= M; ++i) {
        for (j = 0 ; j <= (G + R); ++j) {
            dist[i][j] = inf;
        }
    }    

    deque<pair<int, int>> q;
    q.push_front(make_pair(0, 0));
    dist[0][0] = 0;
    while (!q.empty()) {
        auto p = q.front();
        q.pop_front();
        if (p.second < G) {
            if (p.first > 0) {
                int dd = d[p.first] - d[p.first - 1];
                if (dd <= (G - p.second) && dist[p.first - 1][dd + p.second] > dist[p.first][p.second]) {
                    dist[p.first - 1][dd + p.second] = dist[p.first][p.second];
                    q.push_front(make_pair(p.first - 1, dd + p.second));
                }
            }

            if (p.first < M - 1) {
                int dd = d[p.first + 1] - d[p.first];
                if (dd <= (G - p.second) && dist[p.first + 1][dd + p.second] > dist[p.first][p.second]) {
                    dist[p.first + 1][dd + p.second] = dist[p.first][p.second];
                    q.push_front(make_pair(p.first + 1, dd + p.second));
                }
            }
        } else {
            int nxt = (p.second + 1) % (G + R);
            if (nxt != 0 && dist[p.first][nxt] > dist[p.first][p.second]) {
                dist[p.first][nxt] = dist[p.first][p.second];
                q.push_front(make_pair(p.first, nxt));
            } else if (nxt == 0 && dist[p.first][nxt] > dist[p.first][p.second] + 1) {
                dist[p.first][nxt] = dist[p.first][p.second] + 1;
                q.push_back(make_pair(p.first, nxt));
            }
        }
    }
    long long ans = 1e15;

    for (i = 0 ; i < (G + R); ++i) {
        if (dist[M - 1][i] < inf) {
            ans = min(ans, 1ll * dist[M - 1][i] * (G + R) + i);
        }
    }

    if (ans < 1e15) {
        printf("%I64d\n", ans);
    } else {
        printf("-1\n");
    }
    return 0;
}