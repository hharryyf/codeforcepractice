#include <bits/stdc++.h>
typedef int ll;

using namespace std;

vector<int> primes;
bool visited[1012];

int c2[30] = {0,0,1,2,2,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,5,5,5,5};

void precompute() {
	int i;
		
	for (i = 2; i <= 1011; i++) {
		if (!visited[i]) {
			primes.push_back(i);
			visited[i] = 1;
			for (int j = 1; j * i <= 1011; j++) {
				visited[j * i] = 1;
			}	
		}	
	}
}

int main() {
	precompute();
	ll n;
	scanf("%d", &n);
	map<ll, int> fac;
	int i;
	ll m = n;
	for (i = 0 ; i < (int) primes.size(); i++) {
		while (m % primes[i] == 0) {
			m = m / primes[i];
			fac[primes[i]]++;
		}
	}
	
	if (m != 1) {
		fac[m] = 1;
	}
	
	map<ll, int> :: iterator iter = fac.begin();
	
	int flag = 0;
	int ff = 0;
	int mt = 0;
	ll ans = 1;
	while (iter != fac.end()) {
		if (iter->second != 1) {
			flag = 1;	
		} 
		ff = max(iter->second, ff);
		ans = ans * iter->first;
		iter++;
	}
	
	iter = fac.begin();
	while (iter != fac.end()) {
		if ((1 << c2[ff]) != iter->second) {
			mt = 1;	
		} 
		iter++;
	}
	
	if (!flag) {
		cout << n << " " << 0 << endl;
	} else {
		cout << ans << " " << mt + c2[ff] << endl;
	}
	return 0;
}
