#include <bits/stdc++.h>
#define MAX_SIZE 10000011
using namespace std;

struct node {
    int u = 0, v = 0;
    void insert(int w) {
        if (u == 0) {
            this->u = w;
            return;
        } 

        if (v == 0) {
            this->v = w;
            if (u > v) swap(u, v);
            return;
        }

        if (w < v) v = w;
        if (u > v) swap(u, v); 
    }
};

int rev[MAX_SIZE];
int visited[MAX_SIZE];
node p[MAX_SIZE];
int N;

int main() {
    int i, mx = 0, j;
    int L = 0, R = 0;
    long long ans = 1e14;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        int v;
        scanf("%d", &v);
        if (rev[v] != 0 && ans > 1ll * v) {
            L = rev[v], R = i;
            ans = v;
        }
        rev[v] = i;
        visited[v] = 1;
        mx = max(mx, v);
    }

    for (i = 1; i <= mx; ++i) {
        for (j = i; j <= mx; j += i) {
            if (visited[j]) {
                p[i].insert(j);
            }
        }
    }
    
    for (i = 1; i <= mx; ++i) {
        if (p[i].u != 0 && p[i].v != 0 && ans > 1ll * p[i].u * p[i].v / i) {
            ans = 1ll * p[i].u * p[i].v / i;
            L = rev[p[i].u], R = rev[p[i].v];
        }
    }

    if (L > R) swap(L, R);
    printf("%d %d\n", L, R);
    return 0;
}