#include <bits/stdc++.h>
#define MAX_SIZE 524292
#define MOD 1000000007
typedef long long ll;
using namespace std;

struct qrs {
	int l, r, id;
};

// all of the trees are range product tree
// tree1 is for range product
ll tree1[MAX_SIZE];
// tree2 is for the product of all primes in the range
ll tree2[MAX_SIZE];
// tree3 is for the product of all primes-1 in the range
ll tree3[MAX_SIZE];
// pre records the last occurence of all primes
int pre[MAX_SIZE << 1];

int n, q;
// the prime factorization of all numbers [1, n]
set<ll> fac1[MAX_SIZE];
// the prime factorization of all numbers [1, n]
set<ll> fac2[MAX_SIZE];

// extract all primes below 1011
vector<ll> primes;
bool visited[MAX_SIZE << 1];

void build(ll tree[], int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index] = 1;
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(tree, l, mid, index * 2);
	build(tree, mid + 1, r, index * 2 + 1);
	tree[index] = 1;
}

void preprocess() {
	int i, j;
	for (i = 2; i <= 1011; i++) {
		if (!visited[i]) {
			primes.push_back((ll) i);
			visited[i] = true;
			for (j = 1; j * i <= 1011; j++) {
				visited[i * j] = true;
			}
		}
	}
}

void fac(int index, ll num) {
	 for (auto p : primes) {
	 	if (num <= 1) break;
	 	while (num % p == 0) {
	 		num = num / p;
	 		fac1[index].insert(p);
	 		fac2[index].insert(p-1);
		 }
	 }
	 
	 if (num > 1) {
	 	fac1[index].insert(num);
	 	fac2[index].insert(num - 1);
	 }	
}

ll getfac1(int index) {
	if (fac1[index].empty()) {
		return 1;
	}
	ll ret = 1;
	for (auto num : fac1[index]) {
		ret = ret * num;
	}
	return ret;
}

ll getfac2(int index) {
	if (fac2[index].empty()) {
		return 1;
	}
	ll ret = 1;
	for (auto num : fac2[index]) {
		ret = ret * num;
	}
	return ret;
}
// update the pt index of tree with the value val
void update(ll tree[], int pt, int l, int r, int index, ll val) {
	if (l > r || l > pt || pt > r) return;
	if (l == r && pt == l) {
		tree[index] = val;
		return;
	}
	
	int mid = l + (r - l) / 2;
	if (pt <= mid) {
		update(tree, pt, l, mid, index * 2, val);
	} else {
		update(tree, pt, mid + 1, r, index * 2 + 1, val);
	}
	
	tree[index] = (tree[index * 2] * tree[index * 2 + 1]) % MOD;
}

ll query(ll tree[], int start, int end, int l, int r, int index) {
	if (start > end || l > r || start > r || l > end) return 1;
	if (start <= l && r <= end) return tree[index];
	int mid = l + (r - l) / 2;
	if (end <= mid) {
		return query(tree, start, end, l, mid, index * 2);
	}
	
	if (start >= mid + 1) {
		return query(tree, start, end, mid + 1, r, index * 2 + 1);
	}
	
	return (query(tree, start, end, l, mid, index * 2) * query(tree, start, end, mid + 1, r, index * 2 + 1)) % MOD;
}

vector<qrs> qs;

ll ans[MAX_SIZE >> 1];

static bool cmp(const qrs &a, const qrs &b) {
	return a.r < b.r;
}

ll arr[MAX_SIZE >> 1];

ll ivt(ll num) {
	ll ret = 1;
	ll base = num, ep = MOD - 2;
	while (ep >= 1) {
		if (ep % 2 == 0) {
			base = (base * base) % MOD;
			ep /= 2;
		} else {
			ret = (ret * base) % MOD;
			ep--;
		}
	}
	return ret;
}

int main(int argc,char *argv[]){
	scanf("%d", &n);
	preprocess();
	build(tree1, 1, n, 1);
	build(tree2, 1, n, 1);
	build(tree3, 1, n, 1);
	int i, j;
	for (i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
	}
	scanf("%d", &q);
	for (i = 1; i <= q; i++) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		qs.push_back(qrs{v1, v2, i});
	}
	
	sort(qs.begin(), qs.end(), cmp);
	
	for (i = 0, j = 1; i < q; i++) {
		while (j <= n && qs[i].r >= j) {
			fac(j, arr[j]);
			update(tree1, j, 1, n, 1, arr[j]);
			//cout << "insert " << arr[j] << " index " << j << endl;
			for (auto fc : fac1[j]) {
				if (pre[fc] != 0) {
					fac1[pre[fc]].erase(fc);
					fac2[pre[fc]].erase(fc - 1);
					update(tree2, pre[fc], 1, n, 1, getfac1(pre[fc]));
					update(tree3, pre[fc], 1, n, 1, getfac2(pre[fc]));
					//cout << "wipe out" << fc << " at " << pre[fc] << endl;
				}
			}
			
			for (auto fc : fac1[j]) {
				pre[fc] = j;
			}
			
			update(tree2, j, 1, n, 1, getfac1(j));
			update(tree3, j, 1, n, 1, getfac2(j));
			j++;
		}
		
		ll nterm = query(tree1, qs[i].l, qs[i].r, 1, n, 1);
		ll numer = query(tree3, qs[i].l, qs[i].r, 1, n, 1);
		ll deno = query(tree2, qs[i].l, qs[i].r, 1, n, 1);
		ans[qs[i].id] = (((nterm * numer) % MOD) * ivt(deno)) % MOD;
	}
	
	for (i = 1; i <= q; i++) {
		printf("%lld\n", ans[i]);
	}
	return 0;
}
