#include <bits/stdc++.h>
#define MAX_SIZE 200111

typedef long long Long;

using namespace std;

int n, k;

typedef struct elect {
	Long a;
	Long b;
	Long minute;
} Charge;

struct cmp {
	bool operator()(Charge &a, Charge &b) {
		return a.minute > b.minute;
	}
};

Long a[MAX_SIZE], b[MAX_SIZE];

bool valid(Long pw);

int main(int argc, char *argv[]) {
	int i;
	scanf("%d%d", &n, &k);
	for (i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
	}
	
	for (i = 1; i <= n; i++) {
		scanf("%lld", &b[i]);
	}
	
	Long low = 0ll, high = 2000000000001ll;
	Long ans = high + 1;
	while (low <= high) {
		Long mid = low + (high - low) / 2;
		if (valid(mid)) {
			ans = min(ans, mid);
			high = mid - 1;	
		} else {
			low = mid + 1;
		}
	}
	
	if (ans >= 2000000000001ll) {
		printf("-1\n");
	} else {
		cout << ans << endl;
	}
	return 0;
}

// check whether the current power pw is valid
bool valid(Long pw) {
	priority_queue<Charge, vector<Charge>, cmp> q;
	int i;
	for (i = 1 ; i <= n; i++) {
		Charge ch = {a[i], b[i], a[i] / b[i]};
		q.push(ch);
	}
	
	for (i = 1; i <= k; i++) {
		Charge ch = q.top();
		q.pop();
		if ((ch.a / ch.b) + 1 < i) return false;
		if ((ch.a / ch.b) + 1 >= k) return true;
		ch = {ch.a + pw, ch.b, (ch.a + pw) / ch.b};
		q.push(ch);
	}
	
	return true;
}
