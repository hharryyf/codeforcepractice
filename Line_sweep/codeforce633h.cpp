#pragma GCC optimize(3)
#pragma GCC optimize(2)

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#define MAX_SIZE 65579
#define LEFT (index << 1)
#define RIGHT (index << 1 | 1)
#define shift(x)  (x & (-x))
using namespace std;



int mod;
int block_size = 1;
struct qrs {
	int l, r, id;
	bool operator < (qrs other) const {
		int b1 = l / block_size, b2 = other.l / block_size;
        return (b1 ^ b2) ? b1 < b2 : ((b1 & 1) ? r < other.r : r > other.r);
	}
};

struct BIT {
    int n;
    int tree[MAX_SIZE];
    
    void insert(int index) {
        for (;index <= n; index += shift(index)) {
            ++tree[index];
        }
    }
    
    void erase(int index) {
		for (;index<=n;index += shift(index)) {
            --tree[index];
        }
    }
    
    int query(int index) {
        int ret = 0;
		for (;index > 0; index -= shift(index)) {
            ret += tree[index];
		}
        return ret;
    }
};

BIT st;

inline int scale(int v) {
    if (v > mod || v < -mod) v %= mod;
    return v;
}

struct Matrix {
	int a[2][2];
	Matrix operator *(Matrix other) const {
		Matrix ret;
		int i, j, k;
		for (i = 0 ; i < 2; ++i) {
			for (j = 0 ; j < 2; ++j) {
				ret.a[i][j] = 0;
				for (k = 0 ; k < 2; ++k) {
					ret.a[i][j] += (a[i][k] * other.a[k][j]) % mod;
					ret.a[i][j] = scale(ret.a[i][j]);
				}
				ret.a[i][j] += (ret.a[i][j] < 0) * mod;
			}
		}
		return ret;
	}
	
	Matrix operator +(Matrix other) const {
		Matrix ret;
		int i, j;
		for (i = 0 ; i < 2; ++i) {
			for (j = 0 ; j < 2; ++j) {
				ret.a[i][j] = (other.a[i][j] + a[i][j]) % mod;
				if (ret.a[i][j] < 0) ret.a[i][j] += mod;
			}
		}
		return ret;
	}
	
	Matrix scalar_product(int v) {
		Matrix ret;
		int i, j;
		for (i = 0 ; i < 2; ++i) {
			for (j = 0 ; j < 2; ++j) {
				ret.a[i][j] = (a[i][j] * v) % mod;
				if (ret.a[i][j] < 0) ret.a[i][j] += mod;
			}
		}
		return ret;
	}
	
	bool operator != (Matrix other) const {
	    int i, j;
	    for (i = 0 ; i < 2; ++i) {
	        for (j = 0 ; j < 2; ++j) {
	            if (other.a[i][j] != a[i][j]) return true;
	        }
	    }
	    return false;
	}
};

struct segt {
	Matrix value, lz;
};

segt tre[MAX_SIZE];
Matrix zero;
Matrix matrix[MAX_SIZE], ivt[MAX_SIZE];
int tmp[MAX_SIZE];
int num[MAX_SIZE];
int disc[MAX_SIZE];
int n;
int id[MAX_SIZE];
qrs q[MAX_SIZE];
int h[MAX_SIZE];
int ans[MAX_SIZE];

void pushdown(int l, int r, int index) {
	if (l > r) return;
	if (tre[index].lz != matrix[0]) {
		if (l != r) {
			tre[LEFT].lz = tre[LEFT].lz * tre[index].lz;
			tre[LEFT].value = tre[LEFT].value * tre[index].lz;
			tre[RIGHT].value = tre[RIGHT].value * tre[index].lz;
			tre[RIGHT].lz = tre[RIGHT].lz * tre[index].lz;
		}
		tre[index].lz = matrix[0];
	}
}



void change(int pos, int l, int r, int index, int ord, int tp) {
	if (l > r || pos < l || pos > r) return;
	pushdown(l, r, index);
	if (l == r && pos == l) {
		if (tp == 1) {
			tre[index].value = matrix[ord].scalar_product(disc[pos]);
			// cout << "order of key " << ord << " v= " << disc[pos] << endl;
		} else { 
			tre[index].value = zero;
		}
		return;
	}
	
	int mid = (l + r) >> 1;
	if (pos <= mid) {
		change(pos, l, mid, LEFT, ord,tp);
	} else {
		change(pos, mid + 1, r, RIGHT,ord, tp);
	}
	
	tre[index].value = tre[LEFT].value + tre[RIGHT].value;
}

void update(int start, int end, int l, int r, int index, int tp) {
	if (start > end || l > r) return;
	pushdown(l, r, index);
	if (start > r || l > end) return;
	if (start <= l && r <= end) {
		if (tp == 1) {
			tre[index].value = tre[index].value * matrix[1];
			tre[index].lz = matrix[1];
		} else {
			tre[index].value = tre[index].value * ivt[1];
			tre[index].lz = ivt[1];
		}
		return;
	}
	
	int mid = (l + r) >> 1;
	if (end <= mid) {
		update(start, end, l, mid, LEFT, tp);
	} else if (start >= mid + 1) {
		update(start, end, mid + 1, r, RIGHT, tp);
	} else {
		update(start, end, l, mid, LEFT, tp);
		update(start, end, mid + 1, r, RIGHT, tp);
	}
	
	tre[index].value = tre[LEFT].value + tre[RIGHT].value;
	
}

void add(int idx) {
	h[id[idx]]++;
	if (h[id[idx]] == 1) {
		// 1 means multiply the matrix[1] to a range
		st.insert(id[idx] + 1);
		update(id[idx] + 1, n - 1, 0, n - 1, 1, 1);
	    change(id[idx], 0, n - 1, 1, st.query(id[idx] + 1), 1);
	}
}

void del(int idx) {
	h[id[idx]]--;
	if (h[id[idx]] == 0) {
		// -1 means multiply the ivt[1] to a range
		st.erase(id[idx] + 1);
		update(id[idx] + 1, n - 1, 0, n - 1, 1, -1);
	    change(id[idx], 0, n - 1, 1, 0, -1);
	}
}

int main() {
	int i, l = 1, r = 0, N;
	scanf("%d%d", &N, &mod);
	block_size = sqrt(N);
	Matrix fib, ifib;
	fib.a[0][0] = 1, fib.a[0][1] = 1, fib.a[1][0] = 1, fib.a[1][1] = 0;
	ifib.a[0][0] = 0, ifib.a[0][1] = 1, ifib.a[1][0] = 1, ifib.a[1][1] = -1;
	matrix[0].a[0][0] = 1, matrix[0].a[1][1] = 1, ivt[0].a[0][0] = 1, ivt[0].a[1][1] = 1;
	ivt[1] = ifib;
	for (i = 1; i <= N; ++i) {
		scanf("%d", &num[i]);
		tmp[i] = num[i];
		matrix[i] = matrix[i-1] * fib;
	}
	
	sort(tmp + 1, tmp + N + 1);
	for (i = 1; i < MAX_SIZE; ++i) tre[i].lz = matrix[0];
	
	for (i = 1; i <= N; ++i) {
		if (i == 1 || tmp[i] != tmp[i-1]) disc[n++] = tmp[i];
	}
	
	// find the order of each number
	for (i = 1; i <= N; ++i) {
		id[i] = lower_bound(disc, disc+n, num[i]) - disc;
		num[i] %= mod;
	}
	
	int qs;
	scanf("%d", &qs);
	for (i = 1; i <= qs; ++i) {
		scanf("%d%d", &q[i].l, &q[i].r);
		q[i].id = i;
	}
	sort(q + 1, q + qs + 1);
	st.n = n;
	for (i = 0 ; i < n; ++i) disc[i] %= mod;
	for (i = 1; i <= qs; ++i) {
	    // cout << q[i].l << " " << q[i].r << endl;
		while (r < q[i].r) add(++r);
		while (r > q[i].r) del(r--);
		while (l < q[i].l) del(l++);
		while (l > q[i].l) add(--l);
		ans[q[i].id] = tre[1].value.a[0][1];
	}
	
	for (i = 1; i <= qs; ++i) {
		printf("%d\n", ans[i]);
	}
	return 0;
}