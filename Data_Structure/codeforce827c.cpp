#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;
int N;
struct BIT {
    int tree[MAX_SIZE];
    int shift(int x) {
        return x & (-x);
    }

    void update(int index, int val) {
        if (index <= 0) return;
        while (index <= N) {
            tree[index] += val;
            index += shift(index);
        }  
    }

    int query(int index) {
        int ret = 0;
        while (index > 0) {
            ret = ret + tree[index];
            index -= shift(index);
        }
        return ret;
    }
};

BIT tree[11][10][4];
int getpos(char ch) {
    if (ch == 'A') return 0;
    if (ch == 'C') return 1;
    if (ch == 'G') return 2;
    return 3;
}

char st[MAX_SIZE];
char c[12];

int main() {
    int q, i, j, k;
    scanf("%s", st + 1);
    N = strlen(st + 1);
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= 10; ++j) {
            k = i % j;
            tree[j][k][getpos(st[i])].update(i, 1);
        }
    }
    scanf("%d", &q);
    while (q-- > 0) {
        int tp, x, l, r;
        scanf("%d", &tp);
        if (tp == 1) {
            scanf("%d%s", &x, c);
            for (j = 1; j <= 10; ++j) {
                k = x % j;
                tree[j][k][getpos(st[x])].update(x, -1);
                // cout << "update dim= " << j << " pos= " << k << " letter= " << getpos(st[x]) << " idx= " << x << " by " << -1 << endl;
                tree[j][k][getpos(c[0])].update(x, 1);
                // cout << "update dim= " << j << " pos= " << k << " letter= " << getpos(c[0]) << " idx= " << x << " by " << 1 << endl;
            }   
            st[x] = c[0];
        } else {
            scanf("%d%d%s", &l, &r, c);
            int ans = 0, len = strlen(c);
            for (j = 0; j < len; ++j) {
                int idx = (l + j) % len;
                // cout << "get " << c[j] << " -> " << (tree[len][idx][getpos(c[j])].query(r) - tree[len][idx][getpos(c[j])].query(l - 1)) << endl;
                // cout << "dim= " << len << " pos= " << idx << " r= " << r << " l= " << l << endl;
                ans = ans + tree[len][idx][getpos(c[j])].query(r) - tree[len][idx][getpos(c[j])].query(l - 1);
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}