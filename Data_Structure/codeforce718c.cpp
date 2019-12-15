#include <bits/stdc++.h>
#define MAX_LEN 262160
#define MOD 1000000007

typedef long long Long;

using namespace std;

typedef struct matrix {
	Long arr[2][2];
} Matrix;

typedef struct segTree {
	// the value is set to the current sum of the matrices is that range
	Matrix value;
	// if no lazy update the lazy matrix is set to the identity matrix
	Matrix lazy;
} SegmentTree;

SegmentTree tree[MAX_LEN];

int n;
Matrix I, Z;
Matrix Base;
// calculate the fib(dim) using fast matrix multiplication
Matrix Fib(int dim);
// calculating matrix multiplication of 2 2*2 matrix
Matrix matrixmul(Matrix a, Matrix b);
// matrix sum operation
Matrix matrixsum(Matrix a, Matrix b);
// build the segment tree
void build(int l, int r, int index);
// lazy update matrix values from start to end
void update(int start, int end, int l, int r, int index, Matrix &mtr);
// query from start to end
Matrix query(int start, int end, int l, int r, int index);

bool matrixequal(Matrix &a, Matrix &b);
// debug function
void showMatrix(Matrix &a);

int main(int argc, char *argv[]) {
	Z.arr[0][0] = 0;
	Z.arr[0][1] = 0;
	Z.arr[1][0] = 0;
	Z.arr[1][1] = 0;
	
	I.arr[0][0] = 1;
	I.arr[0][1] = 0;
	I.arr[1][0] = 0;
	I.arr[1][1] = 1;
	Base.arr[0][0] = 1;
	Base.arr[0][1] = 1;
	Base.arr[1][0] = 1;
	Base.arr[1][1] = 0;
	int m;
	
	scanf("%d%d", &n, &m);
	int i;
	int t, l, r, inc;
	build(0, n - 1, 1);
	for (i = 0 ; i < m; i++) {
		scanf("%d", &t);
		if (t == 2) {
			scanf("%d%d", &l, &r);
			Matrix res = query(l - 1, r - 1, 0, n - 1, 1);
			cout << (res.arr[0][1] % MOD) << endl;
		} else if (t == 1) {
			scanf("%d%d%d", &l, &r, &inc);
			Matrix mtr = Fib(inc);
			update(l - 1, r - 1, 0, n - 1, 1, mtr);
		}
	}
	/*
	for (i = 1; i <= 5; i++) {
		cout << "Fib " << i << " looks like " << endl;
		Matrix mtr = Fib(i);
		showMatrix(mtr);
		cout << endl;
	}*/
	return 0;
}

void showMatrix(Matrix &a) {
	for (int i = 0 ; i < 2; i++) {
		for (int j = 0 ; j < 2; j++) {
			cout << a.arr[i][j] << " ";
		}
		cout << endl;
	}
}

Matrix query(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return Z;
	if (!matrixequal(tree[index].lazy, I)) {
		tree[index].value = matrixmul(tree[index].value, tree[index].lazy);
		if (l != r) {
			tree[index * 2].lazy = matrixmul(tree[index * 2].lazy, tree[index].lazy);
			tree[index * 2 + 1].lazy = matrixmul(tree[index * 2 + 1].lazy, tree[index].lazy);
		}
		tree[index].lazy = I;
	}
	
	if (start > r || end < l) return Z;
	if (start <= l && r <= end) {
		return tree[index].value;
	}
	
	int mid = l + (r - l) / 2;
	return matrixsum(query(start, end, l, mid, index * 2), query(start, end, mid + 1, r, index * 2 + 1));
}

void update(int start, int end, int l, int r, int index, Matrix &mtr) {
	if (start > end || l > r) return;
	if (!matrixequal(tree[index].lazy, I)) {
		tree[index].value = matrixmul(tree[index].value, tree[index].lazy);
		if (l != r) {
			tree[index * 2].lazy = matrixmul(tree[index * 2].lazy, tree[index].lazy);
			tree[index * 2 + 1].lazy = matrixmul(tree[index * 2 + 1].lazy, tree[index].lazy);
		}
		tree[index].lazy = I;
	}
	
	if (start > r || end < l) return;
	if (start <= l && r <= end) {
		tree[index].value = matrixmul(tree[index].value, mtr);
		if (l != r) {
			tree[index * 2].lazy = matrixmul(tree[index * 2].lazy, mtr);
			tree[index * 2 + 1].lazy = matrixmul(tree[index * 2 + 1].lazy, mtr);
		}
		return;
	}
	
	int mid = l + (r - l) / 2;
	update(start, end, l, mid, index * 2, mtr);
	update(start, end, mid + 1, r, index * 2 + 1, mtr);
	tree[index].value = matrixsum(tree[index * 2].value, tree[index * 2 + 1].value);
}

bool matrixequal(Matrix &a, Matrix &b) {
	for (int i = 0 ; i < 2; i++) {
		for (int j = 0 ; j < 2; j++) {
			if (a.arr[i][j] != b.arr[i][j]) {
				return false;
			}
		}
	}
	return true;
}

void build(int l, int r, int index) {
	if (r < l) return;
	if (l == r) {
		int dim;
		scanf("%d", &dim);
		tree[index].value = Fib(dim);
		tree[index].lazy = I;
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	tree[index].value = matrixsum(tree[index * 2].value, tree[index * 2 + 1].value);
	tree[index].lazy = I;
}

Matrix matrixsum(Matrix a, Matrix b) {
	Matrix res;
	for (int i = 0 ; i < 2; i++) {
		for (int j = 0 ; j < 2; j++) {
			res.arr[i][j] = (a.arr[i][j] + b.arr[i][j]) % MOD;
		}
	}
	return res;
}

Matrix Fib(int dim) {
	Matrix ans;
	Matrix currentBase = Base;
	ans = I;
	int exp = dim;
	while (exp > 0) {
		if (exp % 2 == 0) {
			currentBase = matrixmul(currentBase, currentBase);
			exp = exp >> 1;
		} else {
			ans = matrixmul(ans, currentBase);
			exp--;
		}
	}
	return ans;	
}

Matrix matrixmul(Matrix a, Matrix b) {
	Matrix res;
	res.arr[0][0] = ((a.arr[0][0] * b.arr[0][0]) % MOD + (a.arr[0][1] * b.arr[1][0]) % MOD) % MOD;
	res.arr[0][1] = ((a.arr[0][0] * b.arr[0][1]) % MOD + (a.arr[0][1] * b.arr[1][1]) % MOD) % MOD;
	res.arr[1][0] = ((a.arr[1][0] * b.arr[0][0]) % MOD + (a.arr[1][1] * b.arr[1][0]) % MOD) % MOD;
	res.arr[1][1] = ((a.arr[1][0] * b.arr[0][1]) % MOD + (a.arr[1][1] * b.arr[1][1]) % MOD) % MOD;
	return res;
}
