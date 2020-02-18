#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
#define MAX_SIZE 111
using namespace std;

int dp[MAX_SIZE][MAX_SIZE];
int a[MAX_SIZE];
int f(int start, int end) {
    if (end - start <= 1) return 0;
    if (dp[start][end] != -1) return dp[start][end];
    int i;
    int ret = a[start + 1] * a[start] * a[end] + f(start, start + 1) + f(start + 1, end);
    for (i = start + 2; i <= end - 1; i++) {
        ret = min(a[i] * a[start] * a[end] + f(start, i) + f(i, end), ret);
    }
    
    return dp[start][end] = ret;
}

int main() {
    int i, j;
    for (i = 0 ; i < MAX_SIZE; i++) {
        for (j = 0 ; j < MAX_SIZE; j++) {
            dp[i][j] = -1;
        }
    }
    
    int n;
    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    printf("%d\n", f(1, n));
    return 0;
}
