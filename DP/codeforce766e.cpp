#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 100011
typedef long long ll;
using namespace std;

vector<int> g[MAX_SIZE];
// ans is a cumultive sum that stores the answer for each bit
ll ans[20];
// cnt[v][i][0] refers to the number of nodes
// that are in the subtree of v which has value[v][i] = 0
// cnt[v][i][1] refers to the number of nodes that are
// in the subtree of v which has value[v][i] = 1
int cnt[MAX_SIZE][20][2];
bool value[MAX_SIZE][20];
int a[MAX_SIZE];
void dfs_1(int v, int pre) {
	 int i;
	 for (i = 0; i < 20; ++i) {
	 	 value[v][i] = value[pre][i] ^ ((a[v] >> i) & 1);
	 }
	 
	 for (auto nv : g[v]) {
	 	 if (nv != pre) {
		 	dfs_1(nv, v); 
         }
	 }
}

void dfs_2(int v, int pre) {
	 int i, j, k;
	 ll c[20][2];
	 for (i = 0 ; i < 20; ++i) {
	 	 cnt[v][i][value[v][i]] = c[i][value[v][i] ^ value[pre][i]]= 1;
	 	 c[i][value[v][i] ^ value[pre][i] ^ 1] = 0;
	 }	
	 
	 for (auto nv : g[v]) {
	 	 if (nv != pre) {
		  	dfs_2(nv, v);
         	for (i = 0; i < 20; ++i) {
				for (j = 0 ; j < 2; ++j) {
					for (k = 0; k < 2; ++k) {
						c[i][j ^ k ^ value[v][i] ^ value[pre][i]] += 1ll * cnt[v][i][j] * cnt[nv][i][k];
					}	
				}
				cnt[v][i][0] += cnt[nv][i][0];
				cnt[v][i][1] += cnt[nv][i][1]; 
            }
		 }
	 }
	 
	 for (i = 0 ; i < 20; ++i) ans[i] += c[i][1];
}

int main() {
	int i, n, v1, v2;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for (i = 1; i < n; ++i) {
		scanf("%d%d", &v1, &v2);
		g[v1].push_back(v2);
		g[v2].push_back(v1);
	}
	
	dfs_1(1, 0);
	dfs_2(1, 0);
	
	ll ret = 0;
	for (i = 0; i < 20; i++) {
		ret += 1ll * ans[i] * (1 << i);
		//cout << ans[i] << " "; 
	}
	// cout << endl;
	printf("%lld\n", ret);
	return 0;
}
