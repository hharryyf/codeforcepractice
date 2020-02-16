#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define MAX_SIZE 111
using namespace std;

int dp[MAX_SIZE][MAX_SIZE];
char s[MAX_SIZE];
void init() {
    int i, j;
    for (i = 0 ; i < MAX_SIZE; i++) {
        for (j = 0 ; j < MAX_SIZE; j++) {
            dp[i][j] = -1;
        }
    }
}

bool match(char ch1, char ch2) {
    if (ch1 == '(' && ch2 == ')') return true;
    if (ch1 == '[' && ch2 == ']') return true;
    return false;
}

int f(int start, int end) {
    if (start >= end) return 0;
    if (dp[start][end] != -1) return dp[start][end];
    int ret = f(start + 1, end - 1) + 2 * match(s[start], s[end]);
    int i;
    for (i = start; i < end; i++) {
        ret = max(ret, f(start, i) + f(i + 1, end));
    }
    return dp[start][end] = ret;
}

int main() {
    while (scanf("%s", s) != EOF) {
        if (strcmp(s, "end") == 0) break;
        init();
        printf("%d\n", f(0, strlen(s) - 1));
    }
    return 0;
}
