#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define MAX_SIZE 1000111
using namespace std;

char s[MAX_SIZE];
int nxt[MAX_SIZE];
int ans[MAX_SIZE];
int m;

void calnext() {
    nxt[0] = -1;
    int j = 0, k = -1;
    while (j <= m - 1) {
        if (k == -1 || s[j] == s[k]) {
            j++, k++;
            nxt[j] = k;
        } else {
            k = nxt[k];
        }     
    }
}

void print() {
    int cnt = 0;
    ans[cnt++] = m;
    int curr = m;
    while (curr != 0 && nxt[curr] != 0) {
        ans[cnt++] = nxt[curr];
        curr = nxt[curr];
    }
    
    int i = cnt - 1;
    while (i >= 0) {
        printf("%d ", ans[i]);
        i--;
    }
    printf("\n");
}

int main() {
    while (scanf("%s", s) != EOF) {
        m = strlen(s);
        calnext();
        print();
    }
    return 0;
}
