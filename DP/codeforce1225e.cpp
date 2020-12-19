#include <bits/stdc++.h>
#define MAX_SIZE 2011
typedef long long ll;
using namespace std;
const ll mod = 1e9 + 7;
int N, M;
ll dp[MAX_SIZE][MAX_SIZE][2], R[MAX_SIZE][MAX_SIZE], D[MAX_SIZE][MAX_SIZE];
int row[MAX_SIZE][MAX_SIZE], col[MAX_SIZE][MAX_SIZE];
ll v[2];
char st[MAX_SIZE][MAX_SIZE];

ll add(ll u, ll v) {
    ll ret = u + v;
    ret %= mod;
    if (ret < 0) ret += mod;
    return ret;
}

int main() {
    int i, j;
    scanf("%d%d", &N, &M);
    D[1][1] = R[1][1] = dp[1][1][0] = dp[1][1][1] = 1;
    for (i = 1; i <= N; ++i) scanf("%s", st[i] + 1);
    if (N == 1 && M == 1) {
        printf("1\n");
        return 0;  
    }

    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= M; ++j) {
            row[i][j] = row[i][j-1] + (st[i][j] == 'R');
            col[i][j] = col[i-1][j] + (st[i][j] == 'R');
        }
    }

    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= M; ++j) {
            if (i == 1 && j == 1) continue;
            // dp[i][j][0] = sum(dp[i][y][1], x = y..j-1), here y = min y such that row[i][M] - row[i][y-1] <= M - j
            // dp[i][j][1] = sum(dp[x][j][0], x = y..i-1), here y = min y such that col[N][j] - col[y-1][j] <= N - i
            int low = 1, high = j, y = j;
            while (low <= high) {
                int mid = (low + high) / 2;
                if (row[i][M] - row[i][mid] <= M - j) {
                    y = mid;
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }
            // cout << "walk rightward " << y << endl;
            dp[i][j][0] = add(D[i][j-1], -D[i][y-1]);
            low = 1, high = i, y = i;
            while (low <= high) {
                int mid = (low + high) / 2;
                if (col[N][j] - col[mid][j] <= N - i) {
                    y = mid;
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }
            
            dp[i][j][1] = add(R[i-1][j], -R[y-1][j]);
            D[i][j] = add(D[i][j-1], dp[i][j][1]);
            R[i][j] = add(R[i-1][j], dp[i][j][0]); 
            // cout << "walk downward " << y << endl;
            // cout << "(" << dp[i][j][0] << ", " << dp[i][j][1] << ") ";
        }
    }

    printf("%I64d\n", add(dp[N][M][0], dp[N][M][1]));
    return 0;
}