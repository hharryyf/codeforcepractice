#include <bits/stdc++.h>
#define MAX_SIZE (262144 + 11)
typedef long long ll;
using namespace std;

typedef struct segt {
	ll lazy, value;
} segmenttree;

segmenttree tree[MAX_SIZE][10];
ll arr[MAX_SIZE >> 1];
void build(int l, int r, int index);

int main(int argc, char *argv[]) {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &arr[i]);
	}
	
	build(1, n, 1);
	
	return 0;
}

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	
}

// set the dimension of dim to val
void update(int start, int end, int l, int r, int index, int dim, ll inc) {
	
}
