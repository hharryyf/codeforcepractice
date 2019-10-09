#include <bits/stdc++.h>
#define MAX_SIZE 524312

using namespace std;


struct node {
	node *left, *right;
	int size;
	int height;
	int value;
	node(int value) {
		this->value = value;
		this->size = 1;
		this->height = 0;
		this->left = this->right = NULL;
	}
};

int arr[MAX_SIZE >> 1];
int dfsord[MAX_SIZE >> 1];
int sbz[MAX_SIZE];
node *tree[MAX_SIZE];
int k = 0;
vector<int> g[MAX_SIZE >> 1];
int n;

int size(node *t) {
	if (t == NULL) return 0;
	return t->size;
}

int height(node *t) {
	if (t == NULL) return 0;
	return t->height;
}

int searchT(node *t, int val) {
	if (t == NULL) return 0;
	if (val < t->value) {
		return searchT(t->left, val);
	}
	
	return 1 + size(t->left) + searchT(t->right, val);
}

node *leftR(node *t) {
	if (t == NULL || t->right == NULL) return t;
	node *tmp = t->right;
	t->right = tmp->left;
	t->size = 1 + size(t->left) + size(t->right);
	t->height = 1 + max(height(t->left), height(t->right));
	tmp->left = t;
	tmp->size = 1 + size(tmp->left) + size(tmp->right);
	tmp->height = 1 + max(height(tmp->left), height(tmp->right));
	return tmp;
}

node *rightR(node *t) {
	if (t == NULL || t->left == NULL) return t;
	node *tmp = t->left;
	t->left = tmp->right;
	t->size = 1 + size(t->left) + size(t->right);
	t->height = 1 + max(height(t->left), height(t->right));
	tmp->right = t;
	tmp->size = 1 + size(tmp->left) + size(tmp->right);
	tmp->height = 1 + max(height(tmp->left), height(tmp->right));
	return tmp;
}

node *balance(node *t) {
	if (t == NULL) return NULL;
	t->size = 1 + size(t->left) + size(t->right);
	t->height = 1 + max(height(t->left), height(t->right));
	if (height(t->left) - height(t->right) > 1) {
		if (height(t->left->left) < height(t->left->right)) {
			t->left = leftR(t->left);
		}
		t = rightR(t);
	} else if (height(t->left) - height(t->right) < -1) {
		if (height(t->right->right) < height(t->right->left)) {
			t->right = rightR(t->right);
		}
		t = leftR(t);
	}
	
	return t;
}

node *insert(node *t, int val) {
	if (t == NULL) {
		return new node(val);
	}
	
	if (t->value == val) return t;
	if (val < t->value) {
		t->left = insert(t->left, val);
	} else {
		t->right = insert(t->right, val);
	}
	
	return balance(t);
}

int query(int start, int end, int l, int r, int index, int val) {
	if (start > end || l > r) return 0;
	if (start > r || l > end) return 0;
	if (start <= l && r <= end) {
		return searchT(tree[index], val);
	}
	
	int mid = l + (r - l) / 2;
	return query(start, end, l, mid, index * 2, val) 
	     + query(start, end, mid + 1, r, index * 2 + 1, val); 
}

void update(int pt, int l, int r, int index, int val) {
	if (l > r) return;
	if (l <= pt && pt <= r) {
		tree[index] = insert(tree[index], val);	
	}
	
	if (l == r && pt == l) {
		return;
	}
	
	int mid = l + (r - l) / 2;
	if (pt <= mid) {
		update(pt, l, mid, index * 2, val);
	} else {
		update(pt, mid + 1, r, index * 2 + 1, val);
	}
}

void dfs(int v, int pre) {
	dfsord[v] = k++;
	sbz[v] = 1;
	for (auto nextv : g[v]) {
		if (nextv != pre) {
			dfs(nextv, v);
			sbz[v] += sbz[nextv];
		}
	}
}

int main() {
	int q, i;
	scanf("%d%d", &n, &q);
	for (i = 0 ; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	
	for (i = 1; i < n; i++) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		g[v1].push_back(v2);
		g[v2].push_back(v1);
	}
	
	dfs(0, -1);
	
	for (i = 0 ; i < n; i++) {
		update(dfsord[i], 0, n - 1, 1, arr[i]);
	}
	
	for (i = 0 ; i < q; i++) {
		int v, p;
		scanf("%d%d", &v, &p);
		// cout << v << " " << dfsord[v] << " " << dfsord[v] + sbz[v] - 1 << endl; 
		printf("%d\n", query(dfsord[v], dfsord[v] + sbz[v] - 1, 0, n - 1, 1, p));
		update(dfsord[v], 0, n - 1, 1, p);
	}
	return 0;
}
