#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 300011
typedef long long ll;
using namespace std;

ll cost = 0; 
priority_queue<int, vector<int>, greater<int> > q;
int a[MAX_SIZE];

int main() {
	int i, n;
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	
	for (i = 1; i <= n; i++) {
		if (!q.empty() && q.top() < a[i]) {
		   cost = cost + a[i] - q.top();
		   q.pop();
		   q.push(a[i]);
		} 
		q.push(a[i]);
	}
	printf("%lld\n", cost);
	return 0;
}
 
