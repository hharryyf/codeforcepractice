#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

double L;



void solve(double len) {
    len = len - floor(len / (L * 4.0)) * 4.0 * L;
    double rem = len - floor(len / L) * L;
    double tol = floor(len / L);
    if (fabs(tol) <= 1e-7) {
        printf("%.10lf %.10lf\n", rem, 0.0);
    } else if (fabs(tol - 1.0) <= 1e-7) {   
        printf("%.10lf %.10lf\n", L, rem);
    } else if (fabs(tol - 2.0) <= 1e-7) {
        printf("%.10lf %.10lf\n", L - rem, L);
    } else {
        printf("%.10lf %.10lf\n", 0.0, L - rem);
    }
}

int main() {
    int i, n;
    double d;
    scanf("%lf%lf", &L, &d);
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        solve(d * i);
    }    
    return 0;
}