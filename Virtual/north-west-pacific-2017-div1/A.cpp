#include <bits/stdc++.h>
#define MAX_SIZE 111
using namespace std;

char st[MAX_SIZE];

int main() {
    int n, i;
    scanf("%s", st);
    n = strlen(st);
    for (i = 1; i < n; ++i) {
        if (st[i] == st[i-1]) {
            printf("Or not.\n");
            return 0;
        }
    }

    printf("Odd.\n");
    return 0;
}