#include <bits/stdc++.h>
#define MAX_SIZE 2011
using namespace std;

int N, M;
int a[MAX_SIZE], b[MAX_SIZE];
map<int, int> cnt;

int main() {
    int i, j;
    scanf("%d%d", &N, &M);
    for (i = 1; i <= N; ++i) scanf("%d", &a[i]);
    for (i = 1; i <= M; ++i) scanf("%d", &b[i]);
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= M; ++j) {
            if (a[i] <= b[j]) cnt[b[j] - a[i]]++;
        }
    }

    int curr = 0, tol = 0;
    for (auto iter : cnt) {
        if (iter.second > tol) {
            tol = iter.second;
            curr = iter.first;
        }
    }

    printf("%d\n", curr);
    return 0;
}