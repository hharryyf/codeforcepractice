#include <bits/stdc++.h>
#pragma GCC optimize(2)
#define MOD 1000000007
#define MAX_SIZE 32772
#define MAXX 1000007
typedef long long ll;
using namespace std;

int visited[MAXX], block, ret = 0, ans[MAX_SIZE << 3], num[MAX_SIZE];

struct qrs {
    int l, r, id;
};

qrs q[MAX_SIZE << 3];

static bool cmp(const qrs &a, const qrs &b) {
    if ((a.l / block) != (b.l / block)) return (a.l / block) < (b.l / block);
    return a.r < b.r;
}

int n, m;

void add(int x) {
    visited[num[x]]++;
    if (visited[num[x]] == 1) ret++;
}

void del(int x) {
    visited[num[x]]--;
    if (visited[num[x]] == 0) ret--;
}

int main() {
    scanf("%d", &n);
    block = sqrt(n);
    int i, l = 1, r = 0;
    for (i = 1; i <= n; i++) {
        scanf("%d", &num[i]);
    }
    scanf("%d", &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &q[i].l, &q[i].r);
        q[i].id = i;
    }
    
    sort(q + 1, q + 1 + m, cmp);
    
    for (i = 1; i <= m; i++) {
        while (l < q[i].l) {
            del(l);
            l++;
        }
        
        while (r > q[i].r) {
            del(r);
            r--;
        }
        
        while (l > q[i].l) {
            add(--l);
        }
        
        while (r < q[i].r) {
            add(++r);
        }
        ans[q[i].id] = ret;
    }
    
    for (i = 1; i <= m; i++) {
        printf("%d\n", ans[i]);
    }
	return 0;
}

