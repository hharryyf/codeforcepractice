#include <bits/stdc++.h>
using namespace std;
#define MAX_SIZE 1011

vector<int> eveneven;
vector<int> oddodd;
vector<int> evenodd;
vector<int> oddeven;
int x[MAX_SIZE], y[MAX_SIZE];

int main() {
    int n, i;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d%d", &x[i], &y[i]);
        if (i > 1) {
            x[i] = x[i] - x[1], y[i] = y[i] - y[1];
        }
    }
    x[1] = y[1] = 0;
    bool flag = true;
    while (flag) {
        for (i = 1; i <= n; ++i) {
            if (abs(x[i]) % 2 == 1 || abs(y[i]) % 2 == 1) {
                flag = false;
                break;
            }
        }

        if (!flag) break;
        for (i = 1; i <= n; ++i) {
            x[i] /= 2, y[i] /= 2;
        }
    }

    for (i = 1; i <= n; ++i) {
        if (abs(x[i]) % 2 == 1 && abs(y[i]) % 2 == 1) {
            oddodd.push_back(i);
        } else if (abs(x[i]) % 2 == 0 && abs(y[i]) % 2 == 1) {
            evenodd.push_back(i);
        } else if (abs(x[i]) % 2 == 1 && abs(y[i]) % 2 == 0) {
            oddeven.push_back(i);
        } else {
            eveneven.push_back(i);
        }
    }

    if (!oddeven.empty() || !evenodd.empty()) {
        printf("%d\n", (int) oddeven.size() + (int) evenodd.size());
        for (auto id : oddeven) {
            printf("%d ", id);
        }

        for (auto id : evenodd) {
            printf("%d ", id);
        }
        printf("\n");
    } else {
        printf("%d\n", (int) eveneven.size());
        for (auto id : eveneven) {
            printf("%d ", id);
        }
        printf("\n");
    }
    return 0;
}