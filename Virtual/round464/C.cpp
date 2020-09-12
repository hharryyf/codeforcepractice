#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 100011
typedef long long ll;
using namespace std;
ll a[MAX_SIZE];
int N;

vector<int> add[MAX_SIZE];
vector<int> del[MAX_SIZE];

int main() {
	int i, s, f;
	scanf("%d", &N);
	for (i = 1; i <= N; ++i) scanf("%I64d", &a[i]);
	scanf("%d%d", &s, &f);
	for (i = 0; i < N; ++i) {
		
		// inverval [s + i, f + i - 1]
		if (s - i >= 1 && f - i - 1 >= 1) {
			add[s - i].push_back(a[i+1]);
			del[f - i - 1].push_back(a[i+1]);
			//cout << "Add " << s - i << " " << f - i - 1 << endl;
		} else if (s - i <= 0 && f - i - 1 <= 0) {
			add[s - i + N].push_back(a[i+1]);
			del[f - i - 1 + N].push_back(a[i+1]);
			//cout << "Add " << s - i + N << " " << f - i - 1 + N << endl;
		} else {
			add[1].push_back(a[i+1]);
			del[f - i - 1].push_back(a[i+1]);
			add[s - i + N].push_back(a[i+1]);
			del[N].push_back(a[i+1]);
			//cout << "add2 " << 1 << " " << f - i - 1 << endl;
			//cout << "add2 " << s - i + N << " " << N << endl;
		}
	}

	ll tm = 0, curr = 0;
	int ans = 0;
	for (i = 1; i <= N; ++i) {
		for (auto v : add[i]) {
			curr += v;
		}

		//cout << "i= " << i << " curr= " << curr << endl;
		if (curr > tm) {
			ans = i;
			tm = curr;
		}

		for (auto v : del[i]) {
			curr -= v;
		}
	}

	printf("%d\n", ans);
	return 0;
}
