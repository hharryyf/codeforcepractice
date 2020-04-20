#include <bits/stdc++.h>
#define MAX_SIZE 1048593
#define LEFT (index << 1)
#define RIGHT (index << 1 | 1)
#define MID ((l+r) >> 1)
#define Pi acos(-1.0)
typedef double db;
using namespace std;

const double eps = 1e-9;

struct Matrix {
	db a[2][2];
	Matrix operator *(Matrix other) {
		Matrix ret;
		int i, j, k;
		for (i = 0 ; i < 2; ++i) {
			for (j = 0 ; j < 2; ++j) {
				ret.a[i][j] = 0;
				for (k = 0 ; k < 2; ++k) {
					ret.a[i][j] += a[i][k] * other.a[k][j];
				}
			}
		}
		
		return ret;
	}
	
	bool operator ==(Matrix mt) {
		int i, j;
		for (i = 0 ; i < 2; ++i) {
			for (j = 0 ; j < 2; ++j) {
				if (fabs(a[i][j] - mt.a[i][j]) > eps) return false; 
			}
		}
		return true;
	}
};

Matrix I;

struct Vector {
	db a[2];
	Vector operator *(Matrix other) {
		Vector ret;
		ret.a[0] = a[0] * other.a[0][0] + a[1] * other.a[0][1];
		ret.a[1] = a[0] * other.a[1][0] + a[1] * other.a[1][1];
		return ret;
	}
	
	Vector operator +(Vector vc) {
		Vector ret;
		ret.a[0] = vc.a[0] + a[0];
		ret.a[1] = vc.a[1] + a[1];
		return ret;
	}
};

struct segt {
	Vector value;
	Matrix lz;
};

segt tree[MAX_SIZE];

void pushdown(int l, int r, int index) {
	if (l > r) return;
	if (tree[index].lz == I) {
		// cout << l << " " << r << " pushdown ret" << endl;
		return;
	}
	if (l != r) {
		tree[LEFT].lz = tree[LEFT].lz * tree[index].lz;
		tree[RIGHT].lz = tree[RIGHT].lz * tree[index].lz;
		tree[LEFT].value = tree[LEFT].value * tree[index].lz;
		tree[RIGHT].value = tree[RIGHT].value * tree[index].lz;
	}
	tree[index].lz = I;
}

void pullup(int index) {
	tree[index].value = tree[LEFT].value + tree[RIGHT].value;
}

// increment the length of the pt interval
void change(int pt, int l, int r, int index, db len) {
	if (pt < l || pt > r || l > r) return;
	pushdown(l, r, index);
	if (pt == l && l == r) {
		double theta = atan2(tree[index].value.a[1], tree[index].value.a[0]);
		// cout << tree[index].value.a[0] << " " << tree[index].value.a[1] << endl;
		// cout << pt << " " << theta << endl;
		tree[index].value.a[1] += len * sin(theta);
		tree[index].value.a[0] += len * cos(theta);
		// cout << tree[index].value.a[0] << " " << tree[index].value.a[1] << endl;
		return;
	}
	
	if (pt <= MID) {
		change(pt, l, MID, LEFT, len);
	} else {
		change(pt, MID + 1, r, RIGHT, len);
	}
	pullup(index);
}

void update(int start, int end, int l, int r, int index, Matrix mt) {
	if (start > end || l > r || start > r || l > end) return;
	pushdown(l, r, index);
	if (start <= l && r <= end) {
		tree[index].value = tree[index].value * mt;
		tree[index].lz = tree[index].lz * mt;
		return;
	}
	
	if (end <= MID) {
		update(start, end, l, MID, LEFT, mt);
	} else if (start >= MID + 1) {
		update(start, end, MID + 1, r, RIGHT, mt);
	} else {
		update(start, end, l, MID, LEFT, mt);
		update(start, end, MID + 1, r, RIGHT, mt);
	}
	pullup(index);
}

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index].value.a[0] = 1.0;
		tree[index].lz = I;
		return;
	}
	tree[index].lz = I;
	build(l, MID, LEFT);
	build(MID + 1, r, RIGHT);
	pullup(index);
}

double cs[360];
double sn[360];

int main() {
	int i, n, q;
	for (i = 0 ; i < 360; ++i) {
		cs[i] = cos(Pi * i / 180.0);
		sn[i] = sin(Pi * i / 180.0);
	}
	
	I.a[0][0] = I.a[1][1] = 1.0;
	scanf("%d%d", &n, &q);
	build(1, n, 1);
	while (q > 0) {
		int tp, id, x;
		scanf("%d%d%d", &tp, &id, &x);
		// printf("%.9lf %.9lf\n", tree[1].value.a[0], tree[1].value.a[1]);
		if (tp == 1) {
			change(id, 1, n, 1, 1.0 * x);
		} else {
			Matrix ret;
			ret.a[0][0] = cs[x];
			ret.a[0][1] = sn[x];
			ret.a[1][0] = -sn[x];
			ret.a[1][1] = cs[x];
			update(id, n, 1, n, 1, ret);
		}
		printf("%.10lf %.10lf\n", tree[1].value.a[0], tree[1].value.a[1]);
		--q;
	}
	return 0;
}