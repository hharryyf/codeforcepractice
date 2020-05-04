#include <bits/stdc++.h>

using namespace std;

char s[53][53];

int main() {
    int a, b, c, d, i, j;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    a--, b--, c--, d--;
    for (i = 1; i <= 25; ++i) {
        for (j = 1; j <= 25; ++j) {
            s[i][j] = 'A';
        }
    }

    for (i = 1; i <= 25; ++i) {
        for (j = 26; j <= 50; ++j) {
            s[i][j] = 'B';
        }
    }

    for (i = 26; i <= 50; ++i) {
        for (j = 1; j <= 25; ++j) {
            s[i][j] = 'C';
        }
    }

    for (i = 26; i <= 50; ++i) {
        for (j = 26; j <= 50; ++j) {
            s[i][j] = 'D';
        }
    }

    for (i = 1; i <= 25 && b > 0; ++i) {
        for (j = 1; j <= 25 && b > 0; ++j) {
            if (i % 2 == 0 && j % 2 == 0) {
                s[i][j] = 'B';
                --b;
            }
        }
    }

    for (i = 1; i <= 25 && c > 0; ++i) {
        for (j = 26; j <= 50 && c > 0; ++j) {
            if (i % 2 == 0 && j % 2 == 1) {
                s[i][j] = 'C';
                --c;
            }
        }
    }

    for (i = 26; i <= 50 && d > 0; ++i) {
        for (j = 1; j <= 25 && d > 0; ++j) {
            if (i % 2 == 1 && j % 2 == 0) {
                s[i][j] = 'D';
                --d;
            }
        }
    }

    for (i = 26; i <= 50 && a > 0; ++i) {
        for (j = 26; j <= 50 && a > 0; ++j) {
            if (i % 2 == 1 && j % 2 == 1) {
                s[i][j] = 'A';
                --a;
            }
        }
    }
    cout << 50 << " " << 50 << endl;
    for (i = 1; i <= 50; ++i) {
        for (j = 1; j<= 50; ++j) {
            putchar(s[i][j]);
        }
        putchar('\n');
    }

    return 0;
}