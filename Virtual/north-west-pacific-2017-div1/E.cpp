#include <bits/stdc++.h>
using namespace std;

double vp, v, X;
int n;

int sgn(int x) {
    if (fabs(x) <= 1e-8) return 0;
    if (x > 0) return 1;
    return -1;
}

int main() {
    int i;
    cin >> n >> X >> v;
    double T =  X * 2.0 / v;
    for (i = 1; i <= n; ++i) {
        double li, ri, vi;
        cin >> li >> ri >> vi;
        vp += (ri - li) / X * vi;
    }

    if (sgn(fabs(vp) - fabs(v)) >= 0) {
        printf("Too hard\n");
        return 0;
    }
    double vl = sqrt(v * v - vp * vp);
    double ans = X / vl;
    if (sgn(ans - T) >= 0) {
        printf("Too hard\n");
        return 0;
    }

    printf("%.3lf\n", ans);
    return 0;
}