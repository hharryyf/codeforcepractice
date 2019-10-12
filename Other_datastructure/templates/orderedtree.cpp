#include <bits/stdc++.h>

using namespace std;

struct node {
	struct node *left, *right;
	int value;
	int height;
	int size;
	node(int val) {
		this->left = this->right = NULL;
		this->value = val;
		this->height = 0;
		this->size = 1;
	}
};

int height(node *t) {
	if (t == NULL) return -1;
	return t->height;
}

int size(node *t) {
	if (t == NULL) return 0;
	return t->size;
}

node *leftrotate(node *t) {
	if (t == NULL || t->right == NULL) return t;
	node *tmp = t->right;
	t->right = tmp->left;
	t->height = 1 + max(height(t->left), height(t->right));
	t->size = 1 + size(t->left) + size(t->right);
	tmp->left = t;
	tmp->height = 1 + max(height(tmp->left), height(tmp->right));
	tmp->size = 1 + size(tmp->left) + size(tmp->right);
	return tmp;
}

node *rightrotate(node *t) {
	if (t == NULL || t->left == NULL) return t;
	node *tmp = t->left;
	t->left = tmp->right;
	t->height = 1 + max(height(t->left), height(t->right));
	t->size = 1 + size(t->left) + size(t->right);
	tmp->right = t;
	tmp->height = 1 + max(height(tmp->left), height(tmp->right));
	tmp->size = 1 + size(tmp->left) + size(tmp->right);
	return tmp;
}

node *balance(node *t) {
	if (t == NULL) return t;
	t->height = 1 + max(height(t->left), height(t->right));
	t->size = 1 + size(t->left) + size(t->right);
	int hl = height(t->left), hr = height(t->right);
	if (hl - hr > 1) {
		if (height(t->left->left) < height(t->left->right)) {
			t->left = leftrotate(t->left);
		}
		t = rightrotate(t);
	} else if (hr - hl > 1) {
		if (height(t->right->right) < height(t->right->left)) {
			t->right = rightrotate(t->right);
		}
		t = leftrotate(t);
	}
	return t;
}


node *getval(node *t, int val) {
	if (t == NULL) return NULL;
	if (t->value == val) return t;
	if (t->value < val) {
		return getval(t->right, val);
	}
	
	return getval(t->left, val);
}

node *insertion(node *t, int val) {
	if (t == NULL) return new node(val);
	if (t->value == val) return t;
	if (t->value < val) {
		t->right = insertion(t->right, val);
	} else {
		t->left = insertion(t->left, val);
	}
	
	t = balance(t);
	return t;	
}

node *deletion(node *t, int val) {
	if (t == NULL) return t;
	if (t->value == val) {
		node * tmp;
		if (t->left == NULL && t->right == NULL) {
			delete t;
			return NULL;
		} else if (t->left == NULL) {
			tmp = t->right;
			delete t;
			return tmp;	
		} else if (t->right == NULL) {
			tmp = t->left;
			delete t;
			return tmp;
		} else {
			tmp = t->left;
			while (tmp->right != NULL) {
				tmp = tmp->right;
			}
			t->value = tmp->value;
			t->left = deletion(t->left, tmp->value);
		}
	} else if (t->value < val) {
		t->right = deletion(t->right, val);
	} else {
		t->left = deletion(t->left, val);
	}
	t = balance(t);
	return t;
}

node *getkth(node *t, int k) {
	if (t == NULL) return NULL;
	if (size(t->left) + 1 == k) {
		return t;
	} else if (size(t->left) + 1 < k) {
		return getkth(t->right, k - size(t->left) - 1);
	}
	return getkth(t->left, k);
}

node *root = NULL;

////////////////////////////////////
// all the codes below are for debugging and testing


void drop(node *t) {
	if (t != NULL) {
		drop(t->left);
		drop(t->right);
		delete t;
	}
}

void print_struture(node *t, int depth) {
	if (t != NULL) {
		print_struture(t->right, depth + 1);
		for (int i = 0 ; i < depth; i++) {
			cout << "\t";
		}
		cout << "(" << t->value << ", " << t->size << ", " << t->height << ")" << endl;
		print_struture(t->left, depth + 1);
	}
}

set<int> st;
vector<int> vec;
int isvalid;

pair<int, int> inorder(node *t) {
	if (t == NULL) {
		return make_pair(0, -1);
	}
	
	pair<int, int> p1 = inorder(t->left);
	vec.push_back(t->value);
	pair<int, int> p2 = inorder(t->right);
	if (p1.first + p2.first + 1 != size(t) || 1 + max(p1.second, p2.second) != height(t)) {
		isvalid = 0;
	} 
	return make_pair(p1.first + p2.first + 1, max(p1.second, p2.second) + 1);
}

void checkinsertion() {
	cout << "++++++++++check insertion++++++++++" << endl;
	srand(time(NULL));
	int i, T = 1; 
	while (T <= 20) {
		root = NULL;
		st = set<int>();
		vec = vector<int>();
		isvalid = 1;
		int n = rand() % 150000 + 20;
		for (i = 0 ; i < n; i++) {
			int v;
			if (T < 18) {
				v = rand() % 50000;
			} else if (T == 19) {
				v = 100000 - i;
			} else {
				v = i;
			}
			root = insertion(root, v);
			st.insert(v);
		}
		inorder(root);
		i = 0;
		for (auto num : st) {
			if (vec[i++] != num) {
				isvalid = 0;
			}
		}
		
		if (isvalid && (int) st.size() == size(root) && st.size() == vec.size()) {
			cout << "test case " << T << " OK" << " n= " << n << endl;
		} else {
			cout << "test case " << T << " invalid insertion!" << " expected size " << st.size() << " found " << vec.size() << endl;
		}
		drop(root);
		T++;
	}
}

void checkdeletion() {
	cout << "++++++++++check deletion++++++++++" << endl;
	srand(time(NULL));
	int i, T = 1; 
	while (T <= 20) {
		root = NULL;
		st = set<int>();
		vec = vector<int>();
		isvalid = 1;
		int n = 20 + rand() % 150000;
		for (i = 0 ; i < n; i++) {
			int v;
			if (T < 18) {
				v = rand() % 100000;
			} else if (T == 19) {
				v = 100000 - i;
			} else {
				v = i;
			}
			root = insertion(root, v);
			st.insert(v);
		}
		
		for (i = 0 ; i < n; i++) {
			int v = rand() % 100000;
			st.erase(v);
			root = deletion(root, v);
		}
		inorder(root);
		i = 0;
		for (auto num : st) {
			if (vec[i++] != num) {
				isvalid = 0;
			}
		}
		
		if (isvalid && (int) st.size() == size(root) && st.size() == vec.size()) {
			cout << "test case " << T << " OK" << " n= " << n << endl;
		} else {
			cout << "test case " << T << " invalid deletion!" << " expected size " << st.size() << " found " << vec.size() << endl;
		}
		drop(root);
		T++;
	}
}

void checkkth() {
	cout << "++++++++++check kth element++++++++++" << endl;
	srand(time(NULL));
	int i, T = 1; 
	while (T <= 20) {
		root = NULL;
		st = set<int>();
		isvalid = 1;
		int n = 20 + rand() % 150000;
		for (i = 0 ; i < n; i++) {
			int v;
			if (T < 18) {
				v = -5000 + rand() % 100000;
			} else if (T == 19) {
				v = 100000 - i;
			} else {
				v = i;
			}
			root = insertion(root, v);
			st.insert(v);
		}
		
		i = 1;
		for (auto num : st) {
			node *tt = getkth(root, i);
			if (tt == NULL) {
				cout <<  "test case " << T << " fails get " << i 
				<< " expected " << num << " get null " << endl; 
				isvalid = 0;
				break;
			} else if (tt->value != num) {
				cout <<  "test case " << T << " fails get " << i 
				<< " expected " << num << " get "<< tt->value << endl; 
				isvalid = 0;			
				break;
			}
			i++;
		}
		
		if (isvalid) {
			cout << "test case " << T << " OK" << " n= " << n << endl;
		}
		drop(root);
		T++;
	}
}

int main() {
	checkinsertion();	
	checkdeletion();
	checkkth();
	return 0;
}
