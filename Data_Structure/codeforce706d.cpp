#include <bits/stdc++.h>
#define SUBMIT
using namespace std;

class Trie {
public:
	Trie() {
		this->root = new node();
		add(0);
	}
	
	void add(int x) {
		vector<int> vc = parse(x);
		root = insert(root, vc, 0);
	}
	
	void del(int x) {
		vector<int> vc = parse(x);
		root = remove(root, vc, 0);
	}
	
	int query(int x) {
		int ret = 0, i;
		vector<int> vc = parse(x);
		node *curr = root;
		for (i = 0 ; i < 31; ++i) {
			if (vc[i] == 0) {
				if (curr->child[1] != NULL) {
					ret = (ret << 1) + 1;
					curr = curr->child[1];
				} else {
					ret = ret << 1;
					curr = curr->child[0];
				}
			} else {
				if (curr->child[0] != NULL) {
					ret = (ret << 1) + 1;
					curr = curr->child[0];
				} else {
					ret = ret << 1;
					curr = curr->child[1];
				}
			}
		}
		return ret;
	}
	
private:
	struct node {
		int cnt;
		node *child[2];
		node() {
			this->child[0] = this->child[1] = NULL;
			this->cnt = 0;
		}
	};
	
	node *root;
	
	int size(node *rt) {
		return rt == NULL ? 0 : rt->cnt;
	}
	
	node *insert(node *rt, vector<int> &a, int pos) {
		int sz = a.size();
		if (pos > sz) return rt;
		if (pos == sz) {
			rt->cnt++;
			return rt;
		}
		
		if (rt->child[a[pos]] == NULL) {
			rt->child[a[pos]] = new node();
		}
		
		rt->child[a[pos]] = insert(rt->child[a[pos]], a, pos + 1);
		rt->cnt = size(rt->child[0]) + size(rt->child[1]);
		return rt;
	}
	
	node *remove(node *rt, vector<int> &a, int pos) {
		int sz = a.size();
		if (rt == NULL || pos > sz) return rt;
		if (pos == sz) {
			rt->cnt--;
			return rt;
		}
		
		rt->child[a[pos]] = remove(rt->child[a[pos]], a, pos + 1);
		if (!size(rt->child[a[pos]])) {
			delete rt->child[a[pos]];
			rt->child[a[pos]] = NULL;
		}
		
		rt->cnt = size(rt->child[0]) + size(rt->child[1]);
		return rt;
	}
	
	vector<int> parse(int x) {
		vector<int> ret = vector<int>(31, 0);
		int idx = 30;
		while (x > 0) {
			ret[idx--] = x & 1;
			x >>= 1;
		}
		return ret;
	}
};

Trie t = Trie();
char s[4];

int main() {
	int q;
	#ifndef SUBMIT
	freopen("input.txt", "r", stdin);
	#endif
	
	scanf("%d", &q);
	while (q > 0) {
		int x;
		scanf("%s%d", s, &x);
		if (s[0] == '+') {
			t.add(x);
		} else if (s[0] == '-') {
			t.del(x);
		} else {
			printf("%d\n", t.query(x));
		}
		q--;
	}
	return 0;
}