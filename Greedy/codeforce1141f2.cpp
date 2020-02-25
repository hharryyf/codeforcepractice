#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 1511
typedef long long ll;
using namespace std;
// map from sum[l, r] -> [l, r]
unordered_map<int, vector<pair<int, int> > > h;
int pref[MAX_SIZE];
int ans = 0, val = 0;

static bool cmp(const pair<int, int> &a, const pair<int, int> &b) {
	   return a.second < b.second;
}

int solve(vector<pair<int, int> > &arr) {
	 sort(arr.begin(), arr.end(), cmp);
	 int i, pd = -1, cnt = 0;
	 for (i = 0 ; i < (int) arr.size(); i++) {
	 	 if (pd == -1) {
		 	pd = i,cnt++; 
         } else if (arr[i].first > arr[pd].second) {
		    pd = i, cnt++;
		 }
	 }
	 return cnt;
}

int main() {
	int n, i, j;
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		scanf("%d", &pref[i]);
		pref[i] += pref[i-1];
	}
	
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= i; j++) {
			h[pref[i] - pref[j-1]].emplace_back(j, i);
		}
	}
	
	auto iter = h.begin();
	
	while (iter != h.end()) {
		  int ret = solve(iter->second);
		  if (ans <= ret) {
		  	 val = iter->first, ans = ret;
		  }
		  iter++; 
	}
	
	printf("%d\n", ans);
	int pd = -1;
	for (auto it : h[val]) {
		if (pd == -1) {
		   printf("%d %d\n", it.first, it.second);
		   pd = it.second;
		} else if (it.first > pd) {
		   printf("%d %d\n", it.first, it.second);
		   pd = it.second;
		}
	}
	return 0;
}

