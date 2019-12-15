#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE (1048576 + 11)

typedef long long ll;
using namespace std;

typedef struct segt {
	ll lazy, value;
} segmenttree;

int prime[63] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,
79,83,89,97,101,103,107,109, 113,127,131,137,139,149,151,157,163,167,173,179,
181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,
269,271,277,281,283,293};

vector<ll> actu;

char s[12];
unordered_map<int, int> h;

segmenttree tree1[MAX_SIZE], tree2[MAX_SIZE];


ll arr[MAX_SIZE >> 1];

void build(int l, int r, int index) {
	if (l > r) return;
	tree1[index].lazy = 1ll;
	if (l == r) {
		tree1[index].value = arr[l];
		
		ll curr = arr[l];
		int i = 0;
		while (curr > 1 && i < 62) {
			if (curr % prime[i] == 0) {
				tree2[index].value |= ((ll) (1ll << h[prime[i]]));
				curr = curr / prime[i];
			} else {
				i++;
			}
		}
		
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	tree1[index].value = (tree1[index * 2].value * tree1[index * 2 + 1].value) % MOD;
	
	tree2[index].value = tree2[index * 2].value | tree2[index * 2 + 1].value;
}

ll fastpower(ll num, int p) {
	ll ret = 1;
	if (num == 0) return 0ll;
	while (p > 0) {
		if (p % 2 == 0) {
			num = (num * num) % MOD;
			p = p / 2;
		} else {
			ret = (ret * num) % MOD;
			p = p - 1;
		}
	}
	return ret;
}

void updatemul(int start, int end, int l, int r, int index, ll val, ll bor) {
	if (start > end || l > r) return;
	if (tree1[index].lazy != 1) {
		tree1[index].value *= fastpower(tree1[index].lazy, r - l + 1);
		tree1[index].value %= MOD;
		if (l != r) {
			tree1[index * 2].lazy = (tree1[index * 2].lazy * tree1[index].lazy) % MOD;
			tree1[index * 2 + 1].lazy = (tree1[index * 2 + 1].lazy * tree1[index].lazy) % MOD;  
		}
		tree1[index].lazy = 1ll;
	}
	
	if (tree2[index].lazy != 0) {
		tree2[index].value |= tree2[index].lazy;
		if (l != r) {
			tree2[index * 2].lazy |= tree2[index].lazy;
			tree2[index * 2 + 1].lazy |= tree2[index].lazy;
		}
		tree2[index].lazy = 0ll;
	}
	
	if (start > r || l > end) return;
	if (start <= l && r <= end) {
		tree1[index].value = (fastpower(val, r - l + 1) * tree1[index].value) % MOD;
		tree2[index].value |= bor;
		tree1[index].value %= MOD;
		if (l != r) {
			tree1[index * 2].lazy = (tree1[index * 2].lazy * val) % MOD;
			tree1[index * 2 + 1].lazy = (tree1[index * 2 + 1].lazy * val) % MOD;  
			tree2[index * 2].lazy |= bor;
			tree2[index * 2 + 1].lazy |= bor;
		}
		return;
	}
	
	int mid = l + (r - l) / 2;
	updatemul(start, end, l, mid, index * 2, val, bor);
	updatemul(start, end, mid + 1, r, index * 2 + 1, val, bor);
	tree1[index].value = (tree1[index * 2].value * tree1[index * 2 + 1].value) % MOD;
	tree2[index].value = tree2[index * 2].value | tree2[index * 2 + 1].value;
	
}

pair<ll, ll> query(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return make_pair(1ll, 0ll);
	if (tree1[index].lazy != 1) {
		tree1[index].value *= fastpower(tree1[index].lazy, r - l + 1);
		tree1[index].value %= MOD;
		if (l != r) {
			tree1[index * 2].lazy = (tree1[index * 2].lazy * tree1[index].lazy) % MOD;
			tree1[index * 2 + 1].lazy = (tree1[index * 2 + 1].lazy * tree1[index].lazy) % MOD;  
		}
		tree1[index].lazy = 1ll;
	}
	
	if (tree2[index].lazy != 0) {
		tree2[index].value |= tree2[index].lazy;
		if (l != r) {
			tree2[index * 2].lazy |= tree2[index].lazy;
			tree2[index * 2 + 1].lazy |= tree2[index].lazy;
		}
		tree2[index].lazy = 0ll;
	}
	
	if (start > r || l > end) return make_pair(1ll, 0ll);
	if (start <= l && r <= end) return make_pair(tree1[index].value, tree2[index].value);
	int mid = l + (r - l) / 2;
	pair<ll, ll> qr1 = query(start, end, l, mid, index * 2);
	pair<ll, ll> qr2 = query(start, end, mid + 1, r, index * 2 + 1);
	// cout << qr1.second << "----" << qr2.second << endl;
	return make_pair((qr1.first * qr2.first) % MOD, qr1.second | qr2.second);
}

void printans(pair<ll, ll> t) {
	int i;
	ll d = 1ll;
	for (i = 0 ; i < 62; i++) { 
		if ((t.second & ((ll)(1ll << i))) != 0) {
			d = (((d * actu[i]) % MOD) * (prime[i] - 1)) % MOD;		
		}
	}
	printf("%lld\n", (ll) (t.first * d) % MOD);
}

int main() {
	int i, n, m;
	scanf("%d%d", &n, &m);
	for (i = 0 ; i < 62; i++) {
		h[prime[i]] = i;
		actu.push_back(fastpower((ll) prime[i], MOD - 2));
	}
	
	for (i = 1 ; i <= n; i++) {
		scanf("%lld", &arr[i]);
	}
	
	build(1, n, 1);
	
	for (i = 0 ; i < m; i++) {
		int l, r;
		ll val;
		scanf("%s %d%d", s, &l, &r);
		if (s[0] == 'M') {
			scanf("%lld", &val);
			if (val == 1) continue;
			ll curr = val;
			int j = 0;
			ll b = 0ll;
			while (curr > 1 && j < 62) {
				if (curr % prime[j] == 0) {
					curr = curr / prime[j];
					b = b | ((ll) (1ll << j));
				} else {
					j++;
				}
			}
			// cout << val << " " << b << endl;
			updatemul(l, r, 1, n, 1, val, b);
		} else {
			printans(query(l, r, 1, n, 1));
		}
	}
	return 0;
}


