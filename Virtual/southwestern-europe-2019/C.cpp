#include <bits/stdc++.h>
#define MAX_SIZE 1000111
using namespace std;

int visited[MAX_SIZE];
char st[123];
int N;

int main() {
    int i;
    scanf("%d", &N);    
    for (i = 0 ; i < N; ++i) {
        scanf("%s", st);
        if (st[0] == '-') continue;
        if (strlen(st) > 7) continue;
        int v = atoi(st);
        if (v < MAX_SIZE) visited[v] = 1;
    }

    for (i = 0 ; i < MAX_SIZE; ++i) {
        if (!visited[i]) {
            printf("%d\n", i);
            return 0;
        }
    }
    return 9;
}