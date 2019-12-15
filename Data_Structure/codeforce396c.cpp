#include <bits/stdc++.h>
#define MAX_SIZE 1048596
#define MAX_VERTEX 300001
#define MOD 1000000007

typedef long long Long;

using namespace std;

vector<int> graph[MAX_VERTEX];
// treesize start from 1, depth, start from depth=1
int treesize[MAX_VERTEX], depth[MAX_VERTEX];
// dfs order 1 indexed
int dfsorder[MAX_VERTEX];
int n;
// two segment trees
typedef struct segt {
	Long lazy, value;
} segmenttree;

segmenttree tree1[MAX_SIZE], tree2[MAX_SIZE];

int ord = 1;

void dfs(int v, int dep);

Long query(segmenttree tree[], int start, int end, int l, int r, int index);
void update(segmenttree tree[], int start, int end, int l, int r, int index, Long val);

int main(int argc, char *argv[]) {
	int i;
	scanf("%d", &n);
	for (i = 2 ; i <= n; i++) {
		int v;
		cin >> v;
		graph[v].push_back(i);
	}
	
	dfs(1, 1);
	
	
	int m;
	cin >> m;
	
	while (m > 0) {
		int t, v;
		Long k, x;
		scanf("%d%d", &t, &v);
		if (t == 1) {
			scanf("%lld%lld", &x, &k);
			update(tree1, dfsorder[v], dfsorder[v] + treesize[v] - 1, 1, n, 
										1, ((k * depth[v]) % MOD + x) % MOD);
			update(tree2, dfsorder[v], dfsorder[v] + treesize[v] - 1, 1, n, 
										1, k % MOD);
		} else {
			//TODO add code here for the query
			Long val1 = query(tree1, dfsorder[v], dfsorder[v], 1, n, 1);
			Long val2 = query(tree2, dfsorder[v], dfsorder[v], 1, n, 1);
			printf("%lld\n",((val1 - (val2 * depth[v]) % MOD) % MOD + MOD) % MOD);
		}
		
		m--;
	} 
	
	
	return 0;
}

void update(segmenttree tree[], int start, int end, int l, int r, int index, Long val) {
	if (start > end || l > r) return;
	if (tree[index].lazy) {
		tree[index].value += (((Long) (r - l + 1)) * tree[index].lazy) % MOD;
		tree[index].value %= MOD;
		if (l != r) {
			tree[index * 2].lazy = (tree[index * 2].lazy + tree[index].lazy) % MOD;
			tree[index * 2 + 1].lazy = (tree[index * 2 + 1].lazy + tree[index].lazy) % MOD;
		}
		tree[index].lazy = 0ll;
	}	
	
	if (start > r || end < l) return;
	if (start <= l && r <= end) {
		tree[index].value = (tree[index].value + (((Long) (r - l + 1)) * val) % MOD) % MOD;	
		if (l != r) {
			tree[index * 2].lazy = (tree[index * 2].lazy + val) % MOD;
			tree[index * 2 + 1].lazy = (tree[index * 2 + 1].lazy + val) % MOD;
		}
		
		return;
	}
	
	int mid = l + (r - l) / 2;
	update(tree, start, end, l, mid, index * 2, val);
	update(tree, start, end, mid + 1, r, index * 2 + 1, val);
	tree[index].value = tree[index * 2].value + tree[index * 2 + 1].value;
}

Long query(segmenttree tree[], int start, int end, int l, int r, int index) {
	if (start > end || l > r) return 0ll;
	if (tree[index].lazy) {
		tree[index].value += (((Long) (r - l + 1)) * tree[index].lazy) % MOD;
		tree[index].value %= MOD;
		if (l != r) {
			tree[index * 2].lazy = (tree[index * 2].lazy + tree[index].lazy) % MOD;
			tree[index * 2 + 1].lazy = (tree[index * 2 + 1].lazy + tree[index].lazy) % MOD;
		}
		tree[index].lazy = 0ll;
	}	
	
	if (start > r || end < l) return 0ll;
	if (start <= l && r <= end) return tree[index].value % MOD;
	int mid = l + (r - l) / 2;
	
	return (query(tree, start, end, l, mid, index * 2) 
		    + query(tree, start, end, mid + 1, r, index * 2 + 1)) % MOD;
}



void dfs(int v, int dep) {
	dfsorder[v] = ord++;
	depth[v] = dep;
	treesize[v] = 1;
	for (auto next : graph[v]) {
		dfs(next, dep + 1);
		treesize[v] += treesize[next];
	}
}
