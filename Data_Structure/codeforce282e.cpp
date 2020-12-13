#include <bits/stdc++.h>
#define MAX_SIZE 100011
typedef long long ll;
using namespace std;

class Trie {
public:
	Trie() {
		this->root = new node();
	}
	
	void add(ll x) {
		vector<int> vc = parse(x);
		root = insert(root, vc, 0);
	}
	
	void del(ll x) {
		vector<int> vc = parse(x);
		root = remove(root, vc, 0);
	}
	
	ll query(ll x) {
		ll ret = 0, i;
		vector<int> vc = parse(x);
		node *curr = root;
		for (i = 0 ; i < maxn; ++i) {
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
	const int maxn = 45;
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
	
	vector<int> parse(ll x) {
		vector<int> ret = vector<int>(maxn, 0);
		int idx = maxn - 1;
		while (x > 0) {
			ret[idx--] = x & 1ll;
			x >>= 1;
		}
		return ret;
	}
};

Trie t = Trie();
int N;
ll a[MAX_SIZE], suf[MAX_SIZE];

int main() {
    int i;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%I64d", &a[i]);
    }

    for (i = N; i >= 1; --i) {
        suf[i] = suf[i+1] ^ a[i];
    }

    for (i = 1; i <= N; ++i) {
        t.add(suf[i]);
    }
    t.add(0);
    ll pre = 0, ans = t.query(0);
    for (i = 1; i <= N - 1; ++i) {
        pre ^= a[i];
        t.del(suf[i]);
        ans = max(ans, t.query(pre));
    }

    printf("%I64d\n", ans);
    return 0;
}