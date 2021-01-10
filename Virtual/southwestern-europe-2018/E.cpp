#include <bits/stdc++.h>
#define MAX_SIZE 10111
using namespace std;

double up = 0, down = 0;

double getup(int num) {
    if (num == 100) return 100.0;
    return 1.0 * num + 0.49;
}

double getdown(int num) {
    if (num == 0) {
        return 0.0;
    }
    return 1.0 * num - 0.50;
}

int N;
char s[MAX_SIZE][22];
int v[MAX_SIZE];
double d[MAX_SIZE], u[MAX_SIZE];

int sgn(double x) {
    if (fabs(x) <= 1e-8) return 0;
    if (x > 0) return 1;
    return -1;
}

int main() {
    int i;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%s%d", s[i] + 1, &v[i]);
        down += getdown(v[i]);
        up += getup(v[i]);
    }

    for (i = 1; i <= N; ++i) {
        int ok = 0;
        down -= getdown(v[i]);
        up -= getup(v[i]);
        for (double j = getdown(v[i]); sgn(getup(v[i]) - j) >= 0; j += 0.01) {
            if (sgn(j + down - 100.00) <= 0 && sgn(j + up - 100.00) >= 0) {
                d[i] = j;
                ok++;
                break;
            }
        }

        for (double j = getup(v[i]); sgn(j - getdown(v[i])) >= 0; j -= 0.01) {
            if (sgn(j + down - 100.00) <= 0 && sgn(j + up - 100.00) >= 0) {
                u[i] = j;
                ok++;
                break;
            }
        }

        // cout << up << " " << down << endl;
        down += getdown(v[i]);
        up += getup(v[i]);
        if (ok != 2) {
            printf("IMPOSSIBLE\n");
            return 0;
        }
    }

    for (i = 1; i <= N; ++i) {
        printf("%s %.2lf %.2lf\n", s[i] + 1, d[i], u[i]);
    }
    return 0;
}