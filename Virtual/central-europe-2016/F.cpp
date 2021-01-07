#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

int nxt1[MAX_SIZE], nxt2[MAX_SIZE];
int indeg1[MAX_SIZE], indeg2[MAX_SIZE];
int f[MAX_SIZE], sz[MAX_SIZE];
set<pair<int, int>> st;
int N;

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

int main() {
    int i;
    long long ans = 0;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &nxt1[i]);
        if (nxt1[i] != 0) {
            indeg1[nxt1[i]]++;
        }
    }

    for (i = 1; i <= N; ++i) {
        scanf("%d", &nxt2[i]);
        if (nxt2[i] != 0) {
            indeg2[nxt2[i]]++;
            st.insert(make_pair(i, nxt2[i]));
        }
        f[i] = i;
        sz[i] = 1;
    }

    for (i = 1; i <= N; ++i) {
        int j = i, flag = false;
        if (indeg1[i] != 0) continue;
        while (nxt1[j] != 0) {
            if (flag) {
                int tmp = nxt1[j];
                nxt1[j] = 0;
                j = tmp;
                ans++;
            } else {
                if (st.find(make_pair(j, nxt1[j])) == st.end()) {
                    flag = true;
                    int tmp = nxt1[j];
                    nxt1[j] = 0;
                    j = tmp;
                    ans++;
                } else {
                    int v1 = find(j), v2 = find(nxt1[j]);
                    f[v1] = v2;
                    sz[v2] += sz[v1];
                    j = nxt1[j];
                }
            }
        }
    }

    for (i = 1; i <= N; ++i) {
        if (indeg2[i] != 0) continue;
        int j = i;
        while (nxt2[j] != 0) {
            int x = find(nxt2[j]), y = find(j); 
            if (x != y) {
                ans = ans + 2 * sz[x] - 1;
                f[x] = y;
                sz[y] += sz[x]; 
            }

            j = nxt2[j];
        }
    }

    cout << ans << endl;
    return 0;
}