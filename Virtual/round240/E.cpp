#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 1111111
using namespace std;
typedef long long ll;

int a[MAX_SIZE], tmp[MAX_SIZE], b[MAX_SIZE];
ll cost[22][2];
int curr[22];
int n;

void divc(int l, int r, int d) {
    if (l >= r) return;
    int mid = (l + r) / 2;
    divc(l, mid, d - 1);
    divc(mid + 1, r, d - 1);
    int i = l, j = mid + 1, k = l;
    i = l;
	while (i <= mid && j <= r) {
		if (a[i] <= a[j]) {
			tmp[k++] = a[i++];
		} else {
			tmp[k++] = a[j++];
			cost[d][0] += 1ll * (mid - i + 1);
        }
	}
	
	while (i <= mid) tmp[k++] = a[i++];
	while(j <= r) tmp[k++] = a[j++];
	for (i = l; i <= r; i++) {
        a[i] = tmp[i];
    }
}


void divc2(int l, int r, int d) {
    if (l >= r) return;
    int mid = (l + r) / 2;
    divc2(l, mid, d - 1);
    divc2(mid + 1, r, d - 1);
    int i = l, j = mid + 1, k = l;
    i = l;
	while (i <= mid && j <= r) {
		if (b[i] >= b[j]) {
			tmp[k++] = b[i++];
		} else {
			tmp[k++] = b[j++];
			cost[d][1] += 1ll * (mid - i + 1);
        }
	}
	
	while (i <= mid) tmp[k++] = b[i++];
	while(j <= r) tmp[k++] = b[j++];
	for (i = l; i <= r; i++) {
        b[i] = tmp[i];
    }
}

int main() {
    int i;
    scanf("%d", &n);
    for (i = 1; i <= (1 << n); ++i) {
        scanf("%d", &a[i]);
    
        b[i] = a[i];
    }

    divc(1, 1 << n, n);
    //reverse(b + 1, b + 1 + n);
    divc2(1, 1 << n, n);
    int q;
    scanf("%d", &q);
    while (q-- > 0) {
        int v;
        scanf("%d", &v);
        while (v >= 0) {
            curr[v] ^= 1;
            --v;
        }

        ll ans = 0;
        for (i = 0; i <= n; ++i) {
            ans += cost[i][curr[i]];
        }

        printf("%I64d\n", ans);
    }
    return 0;
}