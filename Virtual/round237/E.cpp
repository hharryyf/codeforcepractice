#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 1000111
using namespace std;
typedef long long ll;

char st[MAX_SIZE << 1];
int visited[MAX_SIZE << 1];
int block = MAX_SIZE << 1;
int curr = 0;
int n;
int idx(int x) {
    return x + MAX_SIZE;
}

void walk(int x) {
    if (curr + x == block) return;
    curr += x;
    visited[idx(curr)] += 1;
}

bool check(int mid=0) {
    int i;
    memset(visited, 0, sizeof(visited));
    curr = 0;
    block = mid;
    visited[0]++;
    if (mid == 0) {
        block = MAX_SIZE * 2;
    }

    for (i = 1; i <= n; ++i) {
        if (st[i] == 'R') {
            walk(1);
        } else {
            walk(-1);
        }
    }
    
    if (visited[idx(curr)] == 1 && curr != 0) return true;
    return false;
}

int main() {
    scanf("%s", st + 1);
    n = strlen(st + 1);
    if (check()) {
        printf("1\n");
        return 0;
    }

    int low = -1 - n, high = -1;
    int L = 1, R = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (check(mid)) {
            high = mid - 1;
            L = mid;
        } else {
            low = mid + 1;
        }
    }

    low = 1, high = n;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (check(mid)) {
            low = mid + 1;
            R = mid;
        } else {
            high = mid - 1;
        }
    }
    
    int ans = 0;
    if (L <= -1) {
        ans += -L;
    } 

    if (R >= 1) {
        ans += R;
    }

    printf("%d\n", ans);
    return 0;
}