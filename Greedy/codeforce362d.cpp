#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 100011
typedef long long ll;
using namespace std;

int f[MAX_SIZE];
ll subsz[MAX_SIZE];

int find(int x) {
	if (f[x] == x) return x;
	return f[x] = find(f[x]);
}

int main() {
	priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > q;
	int n, m, p, qc;
	scanf("%d%d%d%d", &n, &m, &p, &qc);
	int i, v1 = -1, v2 = -1;
	for (i = 1; i <= n; i++) f[i] = i, subsz[i] = 0;
	for (i = 1; i <= m; i++) {
		ll w;
		scanf("%d%d%lld", &v1, &v2, &w);
		int a = find(v1), b = find(v2);
		if (a != b) {
		    f[a] = b;
		    subsz[b] += subsz[a] + w;
		} else {
		    subsz[a] += w;
		}
	}
	
	for (i = 1; i <= n; i++) {
		if (find(i) == i) q.push(make_pair(subsz[i], i));
	}
	
	// there are several invalid case
	int rem = q.size() - qc;
	// case 1, the totol number of components required is greater
	// than the total components
	// case 2, in order to make the total number of components equal
	// to qc, the number of edges should be added is greater than p
	if (rem < 0 || rem > p) {
	    printf("NO\n");
	    return 0;
	}
	
	vector<pair<int, int>> ret;
	while (!q.empty() && rem > 0) {
	    rem--;
	    p--;
	    int p1 = q.top().second;
	    q.pop();
	    int p2 = q.top().second;
	    q.pop();
	    v1 = find(p1), v2 = find(p2);
	    ret.emplace_back(v1, v2);
	    ll cst = min(1000000000ll, subsz[v1] + subsz[v2] + 1);
	    f[v1] = v2;
	    subsz[v2] += subsz[v1] + cst;
	    q.push(make_pair(subsz[v2], v2));
	}
	
	if (p > 0 && v1 == -1 && v2 == -1) {
	    printf("NO\n");
	    return 0;
	}
	
	while (p > 0) {
	    ret.emplace_back(v1, v2);
	    p--;
	}
	
	printf("YES\n");
	for (i = 0 ; i < ret.size(); i++) {
	    printf("%d %d\n", ret[i].first, ret[i].second);
	}
	return 0;
}

