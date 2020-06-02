#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;
typedef long long ll;

int a[MAX_SIZE];
int visited[MAX_SIZE];
int n;
vector<int> p2;

void solve_1() {
    int i;
    if (n % 2 == 1) {
        printf("NO\n");
        return;
    }

    printf("YES\n");

    p2.push_back(1);
    while (p2.back() * 2 + 1 <= 262144) {
        p2.push_back(p2.back() * 2 + 1);
    }

    reverse(p2.begin(), p2.end());
    for (i = n; i >= 1; --i) {
        if (a[i] != 0) continue;
        for (auto p : p2) {
            if (p - i <= n && p - i >= 1 && !visited[p - i]) {
                visited[p - i] = 1;
                visited[i] = 1;
                a[i] = p - i;
                a[p - i] = i;
            }
        }
    }

    for (i = 1; i <= n; ++i) {
        printf("%d ", a[i]);
        if ((a[i] & i) != 0 || a[i] == i) printf("wrong answer\n");
    }
    printf("\n");
}

void solve_2() {
    if (n < 6) {
        printf("NO\n");
        return;
    }
    int p = 1, i;
    
    while (p * 2 <= n) {
        p = p * 2;
    }

    if (p == n) {
        printf("NO\n");
        return;
    }

    printf("YES\n");
    if (n == 6) {
        printf("3 6 2 5 1 4\n");
    } else {
        if (n % 2 == 1) {
            a[1] = 7, a[2] = 6, a[3] = 2, a[4] = 5, a[5] = 4, a[6] = 3, a[7] = 1;
            for (i = 8; i <= n; i += 2) {
                a[i] = i+1, a[i+1] = i;
            }
        } else {
            for (i = 1; i <= n; ++i) {
                a[i] = i;
            }

            for (i = 1; i <= n; ++i) {
                if (i % 2 == 0 && ((i & n) != 0)) {
                    p = i;
                    break;
                }
            }

            // a[1], a[n], a[p], a[p+1]

            for (i = 2; i <= n - 1; i += 2) {
                a[i] = i+1, a[i+1] = i;
            }

            a[1] = p+1, a[n] = p, a[p] = n, a[p+1] = 1;
        }

        for (i = 1; i <= n; ++i) {
            printf("%d ", a[i]);
            if ((a[i] & i) == 0 || i == a[i]) printf("wrong answer\n");
        }
        printf("\n");
    }
}

int main() {
    scanf("%d", &n);
    solve_1();
    solve_2();    
    return 0;
}