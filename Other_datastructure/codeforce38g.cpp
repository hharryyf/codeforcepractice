#include <bits/stdc++.h>

using namespace std;

struct node {
	struct node *left, *right;
	int submax;
	int size;
	int height;
	int value;
	int ord;
	node(int value, int ord) {
		this->ord = ord;
		this->value = value;
		this->height = 0;
		this->size = 1;
		this->submax = value;
		this->left = this->right = NULL;
	}
};

int size(node *t) {
	if (t == NULL) return 0;
	return t->size;
}

int height(node *t) {
	if (t == NULL) return -1;
	return t->height;
}

int submax(node *t) {
	if (t == NULL) return -1;
	return t->submax;
}

node *leftR(node *t) {
	if (t == NULL || t->right == NULL) return t;
	node *tmp = t->right;
	t->right = tmp->left;
	t->submax = max(max(submax(t->left), submax(t->right)), t->value);
	t->size = 1 + size(t->left) + size(t->right);
	t->height = 1 + max(height(t->left), height(t->right));
	tmp->left = t;
	tmp->submax = max(max(submax(tmp->left), submax(tmp->right)), tmp->value);
	tmp->size = 1 + size(tmp->left) + size(tmp->right);
	tmp->height = 1 + max(height(tmp->left), height(tmp->right));
	return tmp;
}

node *rightR(node *t) {
	if (t == NULL || t->left == NULL) return t;
	node *tmp = t->left;
	t->left = tmp->right;
	t->submax = max(max(submax(t->left), submax(t->right)), t->value);
	t->size = 1 + size(t->left) + size(t->right);
	t->height = 1 + max(height(t->left), height(t->right));
	tmp->right = t;
	tmp->submax = max(max(submax(tmp->left), submax(tmp->right)), tmp->value);
	tmp->size = 1 + size(tmp->left) + size(tmp->right);
	tmp->height = 1 + max(height(tmp->left), height(tmp->right));
	return tmp;
}

node *balance(node *t) {
	if (t == NULL) return t;
	if (height(t->left) - height(t->right) > 1) {
		if (height(t->left->left) > height(t->left->right)) {
			t = rightR(t);
		} else {
			t->left = leftR(t->left);
			t = rightR(t);
		}
	} else if (height(t->right) - height(t->left) > 1) {
		if (height(t->right->right) > height(t->right->left)) {
			t = leftR(t);
		} else {
			t->right = rightR(t->right);
			t = leftR(t);
		}
	}
	return t;
}

node *insertion(node *t, int value, int ord, int maxskip) {
	if (t == NULL) {
		return new node(value, ord);
	}
	
	if (max(submax(t->right), t->value) < value && size(t->right) + 1 <= maxskip) {
		t->left = insertion(t->left, value, ord, maxskip - size(t->right) - 1);
	} else {
		t->right = insertion(t->right, value, ord, maxskip);
	}
	
	t->submax = max(max(submax(t->left), submax(t->right)), t->value);
	t->size = 1 + size(t->left) + size(t->right);
	t->height = 1 + max(height(t->left), height(t->right));
	return balance(t);
}

void inorder(node *t) {
	if (t != NULL) {
		inorder(t->left);
		printf("%d ", t->ord);
		inorder(t->right);
	}
}

int main() {
	node *root = NULL;
	int n;
	scanf("%d", &n);
	for (int i = 0 ; i < n; i++) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		root = insertion(root, v1, i + 1, v2);
	}	
	
	inorder(root);
	printf("\n");
	return 0;
}
