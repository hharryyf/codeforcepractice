#include <bits/stdc++.h>
// #define SUBMIT
#define MAX_SIZE 100114
using namespace std;

bool visited[MAX_SIZE];

class Trie {
public:	
	Trie() {
		root = new node();
	}
	
	void add(int x) {
		vector<int> ret = parse(x);
		root = insert(root, x, ret, 0);
	}
	// return v such that xi + v <= si and xi ^ v is maximum
	int query(int xi, int si) {
		int i, v = 0;
		node *curr = root;
		vector<int> vc = parse(xi);
		for (i = 0; i < 17; i++) {
			if (curr == NULL || curr->value + xi > si) return -1;
			v = v << 1;
			if (vc[i] == 0) {
				if (curr->child[1] != NULL && curr->child[1]->value + xi <= si) {
					curr = curr->child[1];
					v += 1;
				} else {
					curr = curr->child[0];
				}
			} else {
				if (curr->child[0] != NULL && curr->child[0]->value + xi <= si) {
					curr = curr->child[0];
				} else {
					v += 1;
					curr = curr->child[1];
				}
			}
		}
		return v;
	}
	
private:
	struct node {
		// value represents the minimum number that is stored
		// in the subtree
		int value;
		node *child[2];
		node() {
			this->value = MAX_SIZE;
			this->child[0] = this->child[1] = NULL;
		}
	};
	
	node *root;
	
	int minn(node *t) {
		return t == NULL ? MAX_SIZE : t->value;
	}
	
	node *insert(node *rt, int v, vector<int> &a, int pos) {
		int sz = (int) a.size();
		if (rt == NULL || pos > sz) return rt;
		if (pos == sz) {
			rt->value = min(rt->value, v);
			return rt;
		}
		
		if (rt->child[a[pos]] == NULL) rt->child[a[pos]] = new node();
		rt->child[a[pos]] = insert(rt->child[a[pos]], v, a, pos + 1);
		rt->value = min(minn(rt->child[0]), minn(rt->child[1]));
		return rt;
	}
	
	vector<int> parse(int x) {
		vector<int> ret;
		int i;
		for (i = 16; i >= 0; i--) {
			ret.push_back((x >> i) & 1);
		}
		return ret;
	}
};

Trie tries[MAX_SIZE];
// fac[i] stores all the numbers that are factors of i
vector<int> fac[MAX_SIZE];

void preprocess() {
	int i, j;
	for (i = 1; i <= 100000; ++i) {
		for (j = 1; j * i <= 100000; j++) {
			fac[j * i].push_back(i);
		}
	}
}

int main() {
	#ifndef SUBMIT
	freopen("input.txt", "r", stdin);
	#endif
	preprocess();
	int q;
	scanf("%d", &q);
	while (q > 0) {
		int t;
		scanf("%d", &t);
		if (t == 1) {
			int v;
			scanf("%d", &v);
			if (!visited[v]) {
				for (auto p : fac[v]) {
					tries[p].add(v);
				}
				visited[v] = true;
			}
		} else {
			int xi, ki, si;
			scanf("%d%d%d", &xi, &ki, &si);
			int mx = -1;
			if (xi % ki == 0) {
				mx = tries[ki].query(xi, si);
			}
			printf("%d\n", mx);
		}
		
		q--;
	}
	return 0;
}