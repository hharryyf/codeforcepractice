#include <bits/stdc++.h>
#define MAX_SIZE 101111
typedef long long ll;

using namespace std;

ll cnt = 0, k;

ll tree1[MAX_SIZE], tree2[MAX_SIZE];

int tmp[MAX_SIZE], arr[MAX_SIZE];
vector<int> disc;

int n, m;

int shift(int x) {
	return x & (-x);
}

void update(ll t[], int index, ll val) {
	while (index <= m) {
		t[index] += val;
		index = index + shift(index);
	}
}

ll query(ll t[], int index) {
	ll ret = 0;
	while (index > 0) {
		ret += t[index];
		index = index - shift(index);
	}
	
	return ret;
}

ll getans(ll t[], int start, int end) {
	if (start > end) return 0;
	return query(t, end) - query(t, start - 1);
}

void preprocess() {
	int i, index;
	sort(tmp, tmp + n);
	
	for (i = 0 ; i < n; i++) {
		if (i == 0 || tmp[i] != tmp[i-1]) {
			disc.push_back(tmp[i]);
		}
	}
	
	m = (int) disc.size();
	for (i = 0 ; i < n; i++) {
		index = lower_bound(disc.begin(), disc.end(), arr[i]) - disc.begin() + 1;
		update(tree2, index, 1);
		index = upper_bound(disc.begin(), disc.end(), arr[i]) - disc.begin() + 1;
		cnt += getans(tree2, index, m);
	}
	
	index = lower_bound(disc.begin(), disc.end(), arr[0]) - disc.begin() + 1;
	update(tree2, index, -1);
	update(tree1, index, 1);
}

int main() {
	int i, j;
	int index;
	ll ans = 0, curr = 0;
	scanf("%d%lld", &n, &k);
	for (i = 0; i < n; i++) {
		scanf("%d", &tmp[i]);
		arr[i] = tmp[i];
	}
	
	preprocess();
	for (i = 1, j = 1; i < n; i++) {
		while (j < i) {
			curr = 0;
			index = upper_bound(disc.begin(), disc.end(), arr[j]) - disc.begin();
			index++;
			curr = curr + getans(tree1, index, m);
			index = lower_bound(disc.begin(), disc.end(), arr[j]) - disc.begin();
			curr = curr + getans(tree2, 1, index); 
			//cout << "inner loop " << j << " " << cnt << " " << curr << endl;
			if (cnt + curr > k) {
				break;
			}
			
			update(tree1, index + 1, 1);
			cnt = cnt + curr;
			j++;
		}
		
		if (cnt <= k) {
			ans = ans + j;
			// cout << j << " " <<  i << " " << cnt << endl;
		}
		
		// we need to eliminate arr[i] from the right-window
		curr = 0;
		index = upper_bound(disc.begin(), disc.end(), arr[i]) - disc.begin() + 1;
		//cout << index << " !to! " << m << endl; 
		curr = curr + getans(tree1, index, m);
		index = lower_bound(disc.begin(), disc.end(), arr[i]) - disc.begin();
		curr = curr + getans(tree2, 1, index); 
		//cout << 1 << " -to- " << index << endl;
		update(tree2, index + 1, -1);
		cnt = cnt - curr;
		//cout << j << "---" << i << "---" << cnt << endl;
	}
	
	printf("%lld\n", ans);
	return 0;
}
