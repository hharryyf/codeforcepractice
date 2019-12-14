#include <bits/stdc++.h>

using namespace std;

/* 
	This problem might be misunderstood, ti refers to the moment when the ith food
	can be eaten by the dog. Hence, we only need to maintain a set of food that 
	can be eaten at the same time.  
*/

int main() {
	int n, T;
	scanf("%d%d", &n, &T);
	int i, ans = 0;
	priority_queue<int> q;
	for (i = 1; i <= min(n, T-1); i++) {
		while (!q.empty() && q.top() >= T - i) {
			q.pop();
		}
		
		int fd;
		scanf("%d", &fd);
		if (fd < T) {
			q.push(fd - i);
		}
		
		ans = max(ans, (int) q.size());
	}
	
	cout << ans << endl;
	return 0;
}
