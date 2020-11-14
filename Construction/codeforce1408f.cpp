#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> ret;
int logs[15011];
int visited[15011];

void solve(int len, int offset) {
    int i, j;
    for (i = 0; i < len; ++i) {
        for (j = 1; j <= (1 << len); ++j) {
            visited[j] = 0;
        }

        for (j = 1; j <= (1 << len); ++j) {
            if (j + (1 << i) <= (1 << len) && !visited[j] && !visited[j + (1 << i)]) {
                visited[j] = visited[j + (1 << i)] = 1;
                ret.emplace_back(j + offset, j + (1 << i) + offset);
            }
        }
    }
}

int main() {
    int n, i;
    for (i = 2; i < 15001; ++i) logs[i] = logs[i/2] + 1;
    scanf("%d", &n);

    solve(logs[n], 0);
    if (n != (1 << logs[n])) {
        solve(logs[n], n - (1 << logs[n]));
    }
    printf("%d\n", (int) ret.size());
    for (auto p : ret) {
        printf("%d %d\n", p.first, p.second);
    }
    return 0;
}