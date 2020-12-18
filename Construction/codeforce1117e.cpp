#include <bits/stdc++.h>
#define MAX_SIZE 10011
using namespace std;

char st[MAX_SIZE], pt[3][MAX_SIZE];
char ret[3][MAX_SIZE];
char ans[MAX_SIZE];
int N;

int main() {
    int i;
    scanf("%s", st);
    N = strlen(st);
    for (i = 0; i < N; ++i) {
        pt[0][i] = i / 676 + 'a';
        pt[1][i] = (i / 26) % 26 + 'a';
        pt[2][i] = i % 26 + 'a';
    }

    for (i = 0 ; i < 3; ++i) {
        printf("? %s\n", pt[i]);
        fflush(stdout);
        scanf("%s", ret[i]);
    }
    printf("! ");
    for (i = 0 ; i < N; ++i) {
        int val = 676 * (ret[0][i] - 'a') + 26 * (ret[1][i] - 'a') + (ret[2][i] - 'a');
        ans[val] = st[i];       
        // printf("%c", st[val]);
    }
    printf("%s\n", ans);
    fflush(stdout);
    return 0;
}