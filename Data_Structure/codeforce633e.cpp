#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 1000011

typedef long long ll;
using namespace std;


int logs[MAX_SIZE];

class sparseTable {
public:
    sparseTable(int tp) {
        this->tp = tp;
        int i;
        logs[1] = 0;
        for (i = 2; i < MAX_SIZE; i++) {
            logs[i] = logs[i/2] + 1;
        }
    }
    
    void setsize(int n) {
        this->n = n;
    }
    // class invariant, calling this function, a size, must be the same as
    // the table size
    void build(int a[]) {
        int i, j;
        for (i = 1; i <= n; i++) {
            table[0][i] = a[i];
        }
        
        for (i = 1; i <= 19; i++) {
            int len = (1 << (i-1));
            for (j = 1; j <= n; j++) {
                int iend = j + len;
                if (iend <= n) {
                    table[i][j] = getmin(table[i-1][j], table[i-1][iend]);
                } else {
                    table[i][j] = table[i-1][j];
                }
            }
        }
    }
    
    int RMQ(int l, int r) {
    	if (l > r) return -1;
        int len = r - l + 1;
        return getmin(table[logs[len]][l], table[logs[len]][r - (1 << logs[len]) + 1]);
    }
    
private:
    int n;
    int tp;
    int table[20][MAX_SIZE];
    int getmin(int a, int b) {
        if (tp == 1) {
            return min(a, b);
        }
        return max(a, b);
    }
};

int P[MAX_SIZE];
int a[MAX_SIZE];
sparseTable minn = sparseTable(1), maxx = sparseTable(0);

int query(int l, int r) {
    int low = l, high = r;
    if (r - l + 1 <= 0) return -1;
    // return the maximum value of p(l, l..r)
    // we could observe maxx is non-decreasing while minn in non-increasing 
    int mx = maxx.RMQ(l, r), mn = minn.RMQ(l, r);
    // special case where no mx > mn ocurrs
    if (mx <= mn) {
	   return min(mx, mn);
	}
	// otherwise, we use binary search to find the leftmost index such that mx > mn
	int pos = r;
	while (low <= high) {
       int mid = low + (high - low) / 2;
       mx = maxx.RMQ(l, mid), mn = minn.RMQ(l, mid);
       if (mx > mn) {
	   	  pos = mid;
	   	  high = mid - 1;
	   } else {
	   	  low = mid + 1;
	   }
	}
	
	return max(min(maxx.RMQ(l, pos), minn.RMQ(l, pos)), min(maxx.RMQ(l, pos - 1), minn.RMQ(l, pos - 1)));
}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    minn.setsize(n), maxx.setsize(n);
    int i;
    for (i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        a[i] *= 100;
    }
    
    maxx.build(a);
    
    for (i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    minn.build(a);
    
    for (i = 1; i <= n; i++) {
        // use binary search to find the maximum number in a mountain array
        P[i] = query(i, n);
    }
    
    sort(P + 1, P + 1 + n);
    
    double ans = 0;
    double coeff = ((double) k * 1.0) / ((double) n * 1.0);
    for (i = 1; i <= n - k + 1; i++) {
	    ans += coeff * ((double) P[i] * 1.0);
        coeff = coeff * ((n - k - i + 1) * 1.0) / ((n - i) * 1.0);
    }
    printf("%.7lf\n", ans);
    return 0;
}
