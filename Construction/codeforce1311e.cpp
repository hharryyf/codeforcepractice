#include <bits/stdc++.h>
#define MAX_SIZE 5011
using namespace std;

int dep[MAX_SIZE], p[MAX_SIZE], L[MAX_SIZE], R[MAX_SIZE];
int N, D;

void init() {
    int i;
    for (i = 1; i <= N; ++i) {
        p[i] = L[i] = R[i] = -1;
    }

    for (i = 1; i < N; ++i) {
        p[i+1] = i, L[i] = i+1, dep[i] = i - 1;
    }
    dep[N] = N - 1;
}

int getv() {
    int ret = -1;
    for (int i = 2; i <= N; ++i) {
        if (L[i] == -1 && R[i] == -1) {
            if (ret == -1 || dep[ret] < dep[i]) ret = i;
        }
    }

    return ret;
}

int getnew(int limit, int up) {
    int ret = -1;
    for (int i = 1; i <= N; ++i) {
        if (dep[i] >= limit && dep[i] <= up && (L[i] == -1 || R[i] == -1)) {
            if (ret == -1 || dep[ret] > dep[i]) {
                ret = i;
            }
        } 
    }

    return ret;
}

void del(int v) {
    if (p[v] != -1) {
        if (L[p[v]] == v) {
            L[p[v]] = -1;
        } else {
            R[p[v]] = -1;
        }
        p[v] = -1;
    }
}

void addchild(int v, int u) {
    if (L[v] == -1) {
        L[v] = u;
        p[u] = v;
    } else if (R[v] == -1) {
        R[v] = u;
        p[u] = v;
    }
    dep[u] = dep[v] + 1;
}

int gettol() {
    int ret = 0;
    for (int i = 1; i <= N; ++i) ret += dep[i];
    return ret;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d%d", &N, &D);
        init();
        int curr = gettol();
        while (curr > D) {
           //  cout << "depth= " << curr << endl;
            int v = getv();
            if (v == -1) break;
            int d = dep[v];
            int low = d - (curr - D) - 1, high = d - 2;
            int u = getnew(low, high);
            if (u == -1) break;
            del(v);
            addchild(u, v);
            curr = gettol();
        }

        if (curr != D) {
            printf("NO\n");
        } else {
            printf("YES\n");
            for (int i = 2; i <= N; ++i) {
                printf("%d ", p[i]);
            }
            printf("\n");
        }
    }
    return 0;
}