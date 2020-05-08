#include <bits/stdc++.h>

using namespace std;
int a[1011][1011];
int n;

void check() {
    int i, j;
    for (i = 0 ; i < n; ++i) {
        int row = 0, col = 0;
        for (j = 0 ; j < n; ++j) {
            row ^= a[i][j];
            col ^= a[j][i];
        }
        if (row != 0 || col != 0) {
            printf("wrong answer!\n");
            return;
        }
    }
    printf("correct!\n");
}

int main() {
    scanf("%d", &n);
    int k = n / 4;
    int i, j;
    for (i = 0 ; i < n; ++i) {
        for (j = 0 ; j < n; ++j) {
            a[i][j] = (i % 4) * 4 + (j % 4);
            a[i][j] += (k * (i / 4) + j / 4) * 16;
        }
    }

    // check();
    for (i = 0 ; i < n; ++i) {
        for (j = 0 ; j < n; ++j) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
    return 0;
}